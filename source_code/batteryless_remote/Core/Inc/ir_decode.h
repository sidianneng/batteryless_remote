#ifndef IR_DECODE_H
#define IR_DECODE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"

/*
Why we use size 256 - 4 but not just 256?
Because we want the total size of struct
Ir_Decode_t is 256.So we need to decrease
the size of ir_data for start_tag,data_len
...
*/
#define IR_DATA_MAX_LEN (256 - 4)

#define START_TAG 0x89ab
#define END_TAG 0xef01

    typedef enum
    {
        IR_INIT = 0,
        IR_READY,
        IR_BUSY
    } Ir_state_t;

    typedef struct
    {
        uint16_t start_tag;
        uint16_t data_len;
        uint16_t ir_data[IR_DATA_MAX_LEN];
        uint16_t check_value;
        uint16_t end_tag;
    } Ir_Decode_t;

    int8_t ir_set_state(Ir_state_t state);
    Ir_state_t ir_get_state(void);
    int8_t ir_decode_init();

    extern Ir_Decode_t ir_decode;

#ifdef __cplusplus
}
#endif

#endif