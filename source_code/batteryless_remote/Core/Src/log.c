/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-06-10 00:27:52
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-06-10 01:40:28
 * @FilePath: \batteryless_remote\Core\Src\log.c
 * @Description: 日志系统实现
 */
#include "log.h"
#include <stdarg.h>

void Log_Init(void)
{
#if DEBUG_LOG
    MX_USART2_UART_Init();
#endif
}

int8_t Log_Printf(char *fmt, ...)
{
#if DEBUG_LOG
    char log_buf[MAX_LOG_BUF_LEN] = { 0 };
    uint32_t i = 0;
    uint32_t length = 0;
    uint8_t time_cnt = 0;

    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    length = vsnprintf(log_buf, MAX_LOG_BUF_LEN, fmt, arg_ptr);
    if(length > sizeof(log_buf) - 1) {
        length = sizeof(log_buf) - 1;
        log_buf[length] = '\0';
    }
    va_end(arg_ptr);

    while(i < length) {
        LL_USART_TransmitData8(USART2, log_buf[i++]);
        while(LL_USART_IsActiveFlag_TC(USART2) == 0){
            LL_mDelay(1);
            if(time_cnt++ > 1000)
                return -1;
        }
    }
#endif
    return 0;
}