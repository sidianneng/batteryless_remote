/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-02 14:44:05
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:01:27
 * @FilePath: \batteryless_remote\Core\Inc\eeprom.h
 * @Description: internal eeprom read/write
 */
#ifndef EEPROM_H
#define EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "error_code.h"
#include "stdint.h"
#include "stm32g030xx.h"

#define IRDATA_START_ADDR 0x08007000
#define IRDATA_END_ADDR   0x08007fff

#define FLASH_PEKEY1 0x45670123
#define FLASH_PEKEY2 0xcdef89ab

int16_t eeprom_read(uint32_t *addr, uint8_t *buf, uint16_t size);
int16_t eeprom_write(uint32_t *addr, uint8_t *buf, uint16_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif