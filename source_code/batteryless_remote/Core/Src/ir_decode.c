/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-03 00:08:43
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-03 11:16:57
 * @FilePath: \batteryless_remote\Core\Src\ir_decode.c
 * @Description: 普通遥控器的红外数据解析与存储功能实现
 */
#include "ir_decode.h"
#include "error_code.h"

uint16_t origin_ir_data[IR_DATA_MAX_LEN] = { 0 };
uint16_t origin_ir_data_cnt = 0;

uint16_t low_level_max_time = 0;
uint16_t high_level_max_time = 0;

uint8_t ir_origin_data_ready = 0;

int8_t ir_decode_init()
{
    ir_origin_data_ready = 0;
    origin_ir_data_cnt = 0;

    low_level_max_time = 0;
    high_level_max_time = 0;
    memset(origin_ir_data, 0x0000, IR_DATA_MAX_LEN*sizeof(uint16_t));

    return IR_OK;
}


