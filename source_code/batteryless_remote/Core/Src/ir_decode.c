#include "ir_decode.h"
#include "error_code.h"

Ir_Decode_t ir_decode = {0};

static Ir_state_t ir_decode_state = IR_INIT;

int8_t ir_set_state(Ir_state_t state)
{
    ir_decode_state = state;
    return IR_OK;
}

Ir_state_t ir_get_state(void)
{
    return ir_decode_state;
}

int8_t ir_decode_init()
{
    ir_set_state(IR_INIT);
    ir_decode.start_tag = START_TAG;
    ir_decode.end_tag = END_TAG;
    ir_decode.data_len = 0;
    return IR_OK;
}
