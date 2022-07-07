#ifndef _HXD019_H_
#define _HXD019_H_

#include "log.h"
#include "main.h"

/******************************************************************************
*  i2c引脚定义
*/
#define SCL_PIN_MUX		0
#define SCL_PIN_FUNC	GPIOC
#define SCL_PIN			LL_GPIO_PIN_15
#define SDA_PIN_MUX		0
#define SDA_PIN_FUNC	GPIOA
#define SDA_PIN			LL_GPIO_PIN_13

#define SDA_IN()  	LL_GPIO_SetPinMode(SDA_PIN_FUNC, SDA_PIN, LL_GPIO_MODE_INPUT)
#define SDA_OUT()	LL_GPIO_SetPinMode(SDA_PIN_FUNC, SDA_PIN, LL_GPIO_MODE_OUTPUT)

#define SDA_H		LL_GPIO_WriteOutputPort(SDA_PIN_FUNC, SDA_PIN)
#define SDA_L		do \
					{\
						LL_GPIO_WriteOutputPort(SDA_PIN_FUNC, LL_GPIO_ReadOutputPort(SDA_PIN_FUNC) & (~SDA_PIN));\
					}while(0)
#define SDA_is_H	LL_GPIO_IsInputPinSet(SDA_PIN_FUNC, SDA_PIN)

#define SCL_H		LL_GPIO_WriteOutputPort(SCL_PIN_FUNC, SCL_PIN)
#define SCL_L		do \
					{\
						LL_GPIO_WriteOutputPort(SCL_PIN_FUNC, LL_GPIO_ReadOutputPort(SCL_PIN_FUNC) & (~SCL_PIN));\
					}while(0)

#define os_delay_us LL_mDelay

#define NOP5us		os_delay_us(30)	// 25us~35us之间可行


/******************************************************************************
* hxd019
*/
#define HXD019_TEST
#define HXD019_DEBUG

#ifdef HXD019_DEBUG
#define HXD019_PRINTF(fmt,...)  Log_Printf(fmt, ##__VA_ARGS__)
#else
#define HXD019_PRINTF(fmt,...)
#endif

#define BUSY_PIN_MUX	0
#define BUSY_PIN_FUNC	GPIOA
#define BUSY_PIN		LL_GPIO_PIN_9

#define HXD019_BUSY_is_H	LL_GPIO_IsInputPinSet(BUSY_PIN_FUNC, BUSY_PIN)

//typedef void (*hxd019_learn_callback_t)(uint8_t *data, int length, uint8_t status);

enum
{
	HXD019_OK = 0,
	HXD019_FAILED,
	HXD019_TIMEOUT,
};

void hxd019_init(void);
void hxd019_write(uint8_t *buf, int n);
uint8_t hxd019_read(uint8_t *buf);
void hxd019_learn(uint8_t method/*, hxd019_learn_callback_t func*/);

#ifdef HXD019_TEST
// 测试函数
void hxd019_noarc_write_test(int n);
void hxd019_arc_write_test(int n);
void hxd019_learn_test(uint8_t method);
void hxd019_print_learn(void);
void hxd019_learn_write_test(uint8_t *buf, int n);
#endif

#endif

