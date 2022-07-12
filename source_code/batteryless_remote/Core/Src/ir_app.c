/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-13 00:30:30
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:03:51
 * @FilePath: \batteryless_remote\Core\Src\ir_app.c
 * @Description: implementation for IR output and IR learn
 */
#include "ir_app.h"

void Ir_Output(Button_Id_t button_id)
{
    uint8_t output_data[232] = { 0 };
    //1 read data from flash
    eeprom_read(0x08000000, output_data, sizeof(eeprom_write));

    //2 write data to hxd019
    hxd019_write(output_data, sizeof(output_data));

    //delay to wait for the IR waveform output finish
    LL_mDelay(200000);
}
void Ir_Learn(Button_Id_t button_id)
{
    uint8_t learn_data[232] = { 0 };

    //1 learn the IR waveform
    hxd019_learn(2, learn_data, sizeof(learn_data));

    //2 save data to flash
    eeprom_write(0x08000000, learn_data, sizeof(learn_data), 100);
}
