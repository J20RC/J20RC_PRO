#ifndef __MAIN_H
#define __MAIN_H
#ifdef __cplusplus
extern "C" {
#endif

/*main.h统一定义引脚，便于移植*/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "adc.h"
#include "nrf24l01.h"
#include "beeper.h"
#include "key.h"
#include "flash.h"
#include "ppm.h"
#include "tim.h"
#include "setting.h"
#include "lcd.h"
#include "lcdInit.h"
#include "menu.h"

#define ON			1
#define OFF			0
#define FM_VERSION	"J20RC_PRO_V1.0.0"
#define FM_TIME		"2020.12.20"

#define PPM_Pin         GPIO_Pin_13 //PPM输出脚
#define PPM_GPIO_Port   GPIOC        
#define PPM             PCout(13)

#define LED				PCout(13)	// LCD背光灯

#ifdef __cplusplus
}
#endif
#endif
