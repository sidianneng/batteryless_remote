#ifndef _HXD019_H_
#define _HXD019_H_

#include "esp_common.h"

#include "gpio.h"
#include "gpio16.h"



/******************************************************************************
*  i2c引脚定义
*/
#define SCL_PIN_MUX		PERIPHS_IO_MUX_MTMS_U
#define SCL_PIN_FUNC	FUNC_GPIO14
#define SCL_PIN			14
//#define SDA_PIN_MUX		PERIPHS_IO_MUX_GPIO5_U
//#define SDA_PIN_FUNC	FUNC_GPIO5
//#define SDA_PIN			5

#define SDA_IN()  	gpio16_input_conf()
#define SDA_OUT()	gpio16_output_conf()

#define SDA_H		gpio16_output_set(1)
#define SDA_L		gpio16_output_set(0)
#define SDA_is_H	gpio16_input_get()

#define SCL_H		GPIO_OUTPUT_SET(SCL_PIN,1)
#define SCL_L		GPIO_OUTPUT_SET(SCL_PIN,0)

#define NOP5us		os_delay_us(30)	// 25us~35us之间可行


/******************************************************************************
* hxd019
*/
#define HXD019_TEST
#define HXD019_DEBUG

#ifdef HXD019_DEBUG
#define HXD019_PRINTF(fmt,...)  os_printf(fmt, ##__VA_ARGS__)
#else
#define HXD019_PRINTF(fmt,...)
#endif

#define BUSY_PIN_MUX	PERIPHS_IO_MUX_GPIO5_U
#define BUSY_PIN_FUNC	FUNC_GPIO5
#define BUSY_PIN		5

#define HXD019_BUSY_is_H	GPIO_INPUT_GET(BUSY_PIN)

typedef void (*hxd019_learn_callback_t)(uint8_t *data, int length, uint8 status);

enum
{
	HXD019_OK = 0,
	HXD019_FAILED,
	HXD019_TIMEOUT,
};

void hxd019_init(void);
void hxd019_write(uint8_t *buf, int n);
uint8_t hxd019_read(uint8_t *buf);
void hxd019_learn(uint8_t method, hxd019_learn_callback_t func);

#ifdef HXD019_TEST
// 测试函数
void hxd019_noarc_write_test(int n);
void hxd019_arc_write_test(int n);
void hxd019_learn_test(uint8_t method);
void hxd019_print_learn(void);
void hxd019_learn_write_test(uint8_t *buf, int n);
#endif

#endif

