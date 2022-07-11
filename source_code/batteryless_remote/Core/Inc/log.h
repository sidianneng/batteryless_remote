/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-06-10 00:28:15
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-12 00:25:45
 * @FilePath: \batteryless_remote\Core\Inc\log.h
 * @Description: 鏃ュ織绯荤粺澶存枃浠�
 */
#ifndef __LOG_H__
#define __LOG_H__

#include "usart.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void Log_Init(void);
int8_t Log_Printf(char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif