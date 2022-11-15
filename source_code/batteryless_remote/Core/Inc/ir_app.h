/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-13 00:30:24
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:02:57
 * @FilePath: \batteryless_remote\Core\Inc\ir_app.h
 * @Description: hearder file for IR output and IR learn
 */
#ifndef IR_APP_H
#define IR_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "hxd019.h"
#include "flash.h"
#include "ir_decode.h"

#define IR_DATA_LEN 232
typedef struct{
    uint8_t IR_Data[IR_DATA_LEN];
    uint8_t Data_reserved[256 - IR_DATA_LEN];
} IR_Data_Flash_t;

int16_t Ir_Output(uint8_t button_id);
int16_t Ir_Learn(uint8_t button_id, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif