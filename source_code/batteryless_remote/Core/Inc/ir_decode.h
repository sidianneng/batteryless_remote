/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-03 00:08:51
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-03 18:08:56
 * @FilePath: \batteryless_remote\Core\Inc\ir_decode.h
 * @Description: 普通遥控器的红外数据解析与存储头文件
 */
#ifndef IR_DECODE_H
#define IR_DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define IR_DATA_MAX_LEN 128

extern uint16_t origin_ir_data[IR_DATA_MAX_LEN];
extern uint16_t origin_ir_data_cnt;

extern uint16_t low_level_max_time;
extern uint16_t high_level_max_time;

extern uint8_t ir_origin_data_ready;

int8_t ir_decode_init();

#ifdef __cplusplus
}
#endif

#endif