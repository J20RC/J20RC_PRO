#ifndef __TIM_H
#define __TIM_H
#include "stm32f10x.h"
#include "sys.h"

extern volatile u32 nowTime;//��������ʱ�䣬��λ10us
extern volatile u32 clockTime;//���Ӷ�ʱʱ�䣬��λ10us
void TIM4_Counter_Init(u16 arr,u16 psc);
void drawClockTime(void);
#endif
