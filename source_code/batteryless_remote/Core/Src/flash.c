/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-02 14:46:52
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:02:07
 * @FilePath: \batteryless_remote\Core\Src\flash.c
 * @Description: internal flash read/write implementation
 */
#include "flash.h"
#include "log.h"

/**
 * @description: flash read
 * @param {uin32_t} *addr
 * @param {uint8_t} *buf
 * @param {uint16_t} size
 * @return {*}
 */
int16_t flash_read(uint32_t *addr, uint8_t *buf, uint16_t size)
{
    uint32_t result = IR_OK;
    uint16_t i = 0, j = 0;
    uint32_t temp = addr;
    uint32_t read_data = 0x00;

    if ((temp % 8) || addr > IRDATA_END_ADDR || \
        addr < IRDATA_START_ADDR || !buf || !size)
        return -IR_INVAL;

    //read data from flash
    while(i < size / 4)
    {
        if(addr + i * 4 > IRDATA_END_ADDR)
        {
            Log_Printf("read addr overflow\n");
            result = i * 4;
            goto exit;
        }
        read_data = *(addr + i);
        buf[j + 0] = read_data >> 24 & 0xff;
        buf[j + 1] = read_data >> 16 & 0xff;
        buf[j + 2] = read_data >> 8 & 0xff;
        buf[j + 3] = read_data >> 0 & 0xff;
        j += 4;
        i += 1;
    }
    if(size % 4)
    {
        read_data = *(addr + (size / 4));
        for(i = 0;i < size - j; ++i)
        {
            buf[j + i] = (read_data >> ((4 - 1 - i) * 8)) & 0xff;
        }
    }
    result = size;

exit:
    return result;
}

/**
 * @description: flash write
 * @param {uin32_t} *addr
 * @param {uint8_t} *buf
 * @param {uint16_t} size
 * @param {uint32_t} timeout unit:ms
 * @return {*}
 */
int16_t flash_write(uint32_t *addr, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    uint32_t time_cnt = 0;//ms
    uint32_t result = IR_OK;
    uint16_t i = 0,j = 0;
    uint32_t temp = addr;
    uint32_t write_data1 = 0x00;
    uint32_t write_data2 = 0x00;
    uint16_t size_of_uint32 = 0;
    uint32_t temp_uint32_buf[2] = { 0 };

    if ((temp % 8) || addr > IRDATA_END_ADDR || \
        addr < IRDATA_START_ADDR || !buf || !size)
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

    //Write data to flash
    FLASH->CR |= 0x00000001;
    size_of_uint32 = size / 4;
    while(i < size_of_uint32)
    {
        if(addr + i * 4 > IRDATA_END_ADDR)
        {
            Log_Printf("write addr overflow\n");
            result = i * 4;
            goto exit;
        }
        *(addr + i) = buf[j] << 24 | buf[j+1] << 16 | buf[j+2] << 8 | buf[j+3];
        *(addr + i + 1) = buf[j+4] << 24 | buf[j+5] << 16 | buf[j+6] << 8 | buf[j+7];
        i += 2;
        j += 8;
    }
    if(size % 8 != 0)
    {
        if(addr + i * 4 > IRDATA_END_ADDR)
        {
            Log_Printf("write addr overflow\n");
            result = i * 4;
            goto exit;
        }
        for(i = 0;i < size - (size / 8) * 8; ++i)
        {
            if(i < 4)
                temp_uint32_buf[0] |= buf[(size / 8) * 8 + i] << ((4 - 1 - i) * 8);
            else
                temp_uint32_buf[1] |= buf[(size / 8) * 8 + i] << ((8 - 1 - i) * 8);
        }

        *(addr + (size / 8) * 2) = temp_uint32_buf[0];
        *(addr + (size / 8) * 2 + 1) = temp_uint32_buf[1];
    }
    result = size;

exit:
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

    return result;
}