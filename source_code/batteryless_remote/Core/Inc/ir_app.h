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
#include "eeprom.h"

void Ir_Output(Button_Id_t button_id);
void Ir_Learn(Button_Id_t button_id);

#ifdef __cplusplus
}
#endif

#endif