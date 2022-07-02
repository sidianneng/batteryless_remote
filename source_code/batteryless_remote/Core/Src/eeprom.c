/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-02 14:46:52
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-02 18:10:14
 * @FilePath: \batteryless_remote\Core\Src\eeprom.c
 * @Description: internal eeprom read/write implementation
 */
#include "eeprom.h"
#include "log.h"

/**
 * @description: eeprom read
 * @param {uin32_t} *addr
 * @param {uint8_t} *buf
 * @param {uint16_t} size
 * @param {uint32_t} timeout unit:ms
 * @return {*}
 */
int16_t eeprom_read(uint32_t *addr, uint32_t *buf, uint16_t size)
{
    uint32_t result = IR_OK;
    uint16_t i = 0;
    uint32_t temp = addr;

    if ((temp % 4) || addr > EEPROM_END_ADDR || \
        addr < EEPROM_START_ADDR || !buf || !size)
        return -IR_INVAL;

    //read data from eeprom
    while(i < size)
    {
        if(addr + i > EEPROM_END_ADDR)
            break;
        buf[i] = *(addr + i);
        i++;
    }
    result = i;

    return result;
}

/**
 * @description: eeprom write
 * @param {uin32_t} *addr
 * @param {uint8_t} *buf
 * @param {uint16_t} size
 * @param {uint32_t} timeout unit:ms
 * @return {*}
 */
int16_t eeprom_write(uint32_t *addr, uint32_t *buf, uint16_t size, uint32_t timeout)
{
    uint32_t time_cnt = 0;//ms
    uint32_t result = IR_OK;
    uint16_t i = 0;
    uint32_t temp = addr;

    if ((temp % 4) || addr > EEPROM_END_ADDR || \
        addr < EEPROM_START_ADDR || !buf || !size)
        return -IR_INVAL;

    //unlock the eeprom
    while ((FLASH->SR & FLASH_SR_BSY) != 0)
    {
        if(timeout == 0 || time_cnt >= timeout)
        {
            result = -IR_TIMEOUT;
            goto exit;
        }
        time_cnt++;
        LL_mDelay(1);
    }    
    if ((FLASH->PECR & FLASH_PECR_PELOCK) != 0)
    {
        FLASH->PEKEYR = FLASH_PEKEY1;
        FLASH->PEKEYR = FLASH_PEKEY2;
    }
    
    //write data to eeprom
    while(i < size)
    {
        if(addr + i > EEPROM_END_ADDR)
            break;
        *(addr + i) = buf[i];
        i++;
    }
    result = i;

    //lock the eeprom again
    while ((FLASH->SR & FLASH_SR_BSY) != 0)
    {
        if(timeout == 0 || time_cnt >= timeout)
        {
            result = -IR_TIMEOUT;
            goto exit;
        }
        time_cnt++;
        LL_mDelay(1);
    }
    FLASH->PECR |= FLASH_PECR_PELOCK;

exit:
    return result;
}