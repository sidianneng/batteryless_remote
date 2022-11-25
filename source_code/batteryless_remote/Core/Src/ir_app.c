/*
 * @Author: bbear2 bbear_mail@163.com
 * @Date: 2022-07-13 00:30:30
 * @LastEditors: bbear2 bbear_mail@163.com
 * @LastEditTime: 2022-07-13 01:03:51
 * @FilePath: \batteryless_remote\Core\Src\ir_app.c
 * @Description: implementation for IR output and IR learn
 */
#include "ir_app.h"

int16_t Ir_Output(uint8_t button_id)
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
    LL_TIM_CC_EnableChannel(TIM14, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableIT_UPDATE(TIM16);
    LL_TIM_EnableCounter(TIM16);

    //delay to wait for the IR waveform output finish
    LL_mDelay(200000);
exit:
    return result;
}
int16_t Ir_Learn(uint8_t button_id, uint32_t timeout_ms)
{
    int16_t result = IR_OK;
    uint32_t time_cnt = 0;
    uint8_t press_time_needed = 0;//we need to press the button for this times before we use it.
    uint32_t ir_output_l = 0;
    uint32_t ir_output_h = 0;
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
    if(result != sizeof(Ir_Decode_t)) {
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_2);
        LL_mDelay(2000000);
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_2);
        result = -IR_FLASH_W_ERR;
        goto exit;
    }

    // calculate the time we need to press before use it
    for(uint32_t i = 1;i < ir_decode.data_len; ++i){
        if(i % 2)
            ir_output_l += ir_decode.ir_data[i];
        else
            ir_output_h += ir_decode.ir_data[i];
    }
    /* 
    How we get the press time for button?
    1 We test the waveform with logic analyzer to get the raw data with different press times.
    2 Counting the time for high and low levels in ms
    3 We get the IR_OUT_L_FACTOR and IR_OUT_H_FACTOR by calculating the binary linear equation
    4 Calculate the press_time_needed with ir_decode.ir_data(in us)
    5 Add 1 to the result based on experience
    */
    press_time_needed = (uint8_t)(ir_output_l / 1000.0 * IR_OUT_L_FACTOR + ir_output_h / 1000.0 * IR_OUT_H_FACTOR) + 1;

    //4 light user led to notify the use
    for(uint8_t i = 0;i < press_time_needed * 2; ++i){
        LL_mDelay(200000);
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_2);
    }

exit:
    return result;
}
