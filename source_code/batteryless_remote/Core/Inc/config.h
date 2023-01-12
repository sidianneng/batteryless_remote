/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-06-10 00:37:18
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-02 17:05:40
 * @FilePath: \batteryless_remote\Core\Inc\config.h
 * @Description: 工程配置文件
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAIN_VERSION 0x01
#define SUB_VERSION 0x01

#define DEBUG_LOG 0
#define MAX_LOG_BUF_LEN 64U

#define IR_RAW_DATA_DEBUG

/* according to different bom, we need to change this macro to match it */
#define IR_OUT_L_FACTOR (0.04)
#define IR_OUT_H_FACTOR (0.04)

#ifdef __cplusplus
}
#endif

#endif