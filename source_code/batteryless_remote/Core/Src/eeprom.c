/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-02 14:46:52
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:02:07
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

    //Unlock the internal flash
    while ((FLASH->SR & 0x00010000) != 0)
    {
        if(timeout == 0 || time_cnt >= timeout)
        {
            result = -IR_TIMEOUT;
            goto exit;
        }
        time_cnt++;
        LL_mDelay(1000);
    }    
    if(FLASH->CR & 0x80000000)
    {
        FLASH->KEYR = FLASH_PEKEY1;
        FLASH->KEYR = FLASH_PEKEY2;
        if(FLASH->CR & 0x80000000)
        {
            Log_Printf("Unlock flash error\n");
            return -IR_ERROR;
        }
    }

    //Clear the error bit
    FLASH->SR |= 0x000083FB;

    //Write data to eeprom
    FLASH->CR |= 0x00000001;
    while(i < size)
    {
        if(addr + i > EEPROM_END_ADDR)
            break;
        *(addr + i) = buf[i];
        *(addr + i + 1) = buf[i + 1];
        i += 2;
    }
    result = i;

    //Wait for flash write finish
    while ((FLASH->SR & 0x00010000) != 0)
    {
        if(timeout == 0 || time_cnt >= timeout)
        {
            result = -IR_TIMEOUT;
            goto exit;
        }
        time_cnt++;
        LL_mDelay(1000);
    }

    //Clear EOP bit in SR
    if(FLASH->SR & 0x00000001)
    {
        FLASH->SR |= 0x00000001;
    }

    //Clear PG bit in CR
    FLASH->CR &= ~0x00000001;

    //Lock the internal flash
    FLASH->CR |= 0x80000000;
    if(FLASH->CR & 0x80000000 == 0x00000000)
    {
        Log_Printf("Lock flash error\n");
        return -IR_ERROR;
    }

exit:
    return result;
}