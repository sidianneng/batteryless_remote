/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-02 14:44:05
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-02 17:33:46
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
#include "stm32l011xx.h"

#define EEPROM_START_ADDR 0X08080000
#define EEPROM_END_ADDR   0X0808007c

#define FLASH_PEKEY1 0x89ABCDEF
#define FLASH_PEKEY2 0x02030405

int16_t eeprom_read(uint32_t *addr, uint32_t *buf, uint16_t size);
int16_t eeprom_write(uint32_t *addr, uint32_t *buf, uint16_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif