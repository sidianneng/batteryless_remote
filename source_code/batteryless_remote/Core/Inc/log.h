/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-06-10 00:28:15
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-06-10 01:19:02
 * @FilePath: \batteryless_remote\Core\Inc\log.h
 * @Description: 日志系统头文件
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