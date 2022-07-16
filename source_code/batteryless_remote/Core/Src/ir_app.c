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
    IR_Data_Flash_t stored_ir_data;

    //1 read data from flash
    flash_read(IRDATA_START_ADDR + button_id * sizeof(IR_Data_Flash_t), \
        stored_ir_data.IR_Data, sizeof(stored_ir_data.IR_Data));

    //2 write data to hxd019
    hxd019_write((uint8_t *)stored_ir_data.IR_Data, sizeof(stored_ir_data.IR_Data));

    //delay to wait for the IR waveform output finish
    LL_mDelay(200000);
}
void Ir_Learn(Button_Id_t button_id)
{
    IR_Data_Flash_t learn_data;
    int16_t result = IR_OK;

    memset(&learn_data.Data_reserved, 0xff, sizeof(learn_data.Data_reserved));

    //1 learn the IR waveform
    hxd019_learn(2, &learn_data.IR_Data, sizeof(learn_data.IR_Data));

    //2 save data to flash
    result = flash_write(IRDATA_START_ADDR + button_id * sizeof(IR_Data_Flash_t), \
        learn_data.IR_Data, sizeof(learn_data.IR_Data), 100);
    Log_Printf("flash write ret:%d\n", result);

}
