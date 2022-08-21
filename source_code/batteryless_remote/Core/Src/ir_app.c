/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-13 00:30:30
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:03:51
 * @FilePath: \batteryless_remote\Core\Src\ir_app.c
 * @Description: implementation for IR output and IR learn
 */
#include "ir_app.h"

int16_t Ir_Output(Button_Id_t button_id)
{
    uint16_t temp = 0x0000;
    int16_t result = IR_OK;
    //1 read data from flash
    result = flash_read(IRDATA_START_ADDR + button_id * sizeof(Ir_Decode_t), \
        &ir_decode, sizeof(ir_decode));
    if(result != sizeof(ir_decode))
    {
        result = -IR_ERROR;
        goto exit;
    }

    //2 write data to hxd019
    if(ir_decode.data_len > IR_DATA_MAX_LEN)
    {
        Log_Printf("Error ir data len:%d\n", ir_decode.data_len);
        result = -IR_ERROR;
        goto exit;
    }
    for(uint32_t i = 1;i < ir_decode.data_len; ++i)
    {
        temp += ir_decode.ir_data[i];
    }
    
    if(temp == ir_decode.check_value && ir_decode.start_tag == START_TAG \
        && ir_decode.end_tag == END_TAG)
    {
#ifdef IR_RAW_DATA_DEBUG
    Log_Printf("output len:%d chk_val:0x%04x\n", ir_decode.data_len - 1, ir_decode.check_value);
        for(uint16_t i = 1;i < ir_decode.data_len; ++i)
            Log_Printf("%d ", ir_decode.ir_data[i]);
        Log_Printf("\n");
#endif
    }
    else
    {
        Log_Printf("flash data error\n");
        result = -IR_ERROR;
        goto exit;
    }

    //LL_TIM_EnableCounter(TIM16);
    Log_Printf("data cnt:%d\n", ir_decode.data_len);
    LL_TIM_EnableIT_UPDATE(TIM16);
    LL_TIM_EnableCounter(TIM16);

    //delay to wait for the IR waveform output finish
    LL_mDelay(200000);
exit:
    return result;
}
int16_t Ir_Learn(Button_Id_t button_id, uint32_t timeout_ms)
{
    int16_t result = IR_OK;
    uint32_t time_cnt = 0;
    //1 learn the IR waveform
    while(1)
    {
        if(ir_get_state() == IR_READY && ir_decode.data_len > 1)
        {
            ir_decode.start_tag = START_TAG;
            ir_decode.end_tag = END_TAG;
            for(uint16_t i = 1;i < ir_decode.data_len; ++i)
                ir_decode.check_value += ir_decode.ir_data[i];
            break;
        }
        if(time_cnt++ >= timeout_ms || !timeout_ms)
        {
            result = -IR_TIMEOUT;
            goto exit;
        }
        LL_mDelay(1000000);
    }
#ifdef IR_RAW_DATA_DEBUG
    Log_Printf("learn len:%d chk_val:0x%04x\n", ir_decode.data_len - 1, ir_decode.check_value);
    for(uint16_t i = 1; i < ir_decode.data_len; ++i)
        Log_Printf("%d ", ir_decode.ir_data[i]);
    Log_Printf("\n");
#endif

    //2 save data to flash
    result = flash_write(IRDATA_START_ADDR + button_id * sizeof(Ir_Decode_t), \
        &ir_decode, sizeof(Ir_Decode_t), 100);

    //light user led to notify the use
    for(uint8_t i = 0;i < 10; ++i){
        LL_mDelay(100000);
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_2);
    }

exit:
    return result;
}
