#include "main.h"
#include "tim.h"

volatile u32 nowTime = 0;//程序运行时间，单位20ms，在key.c中更新
volatile u32 clockTime = 0;//闹钟定时时间，单位20ms，在key.c中更新
extern u8 timeStr[9];//时间字符串

void drawClockTime(void)
{
	u16 hour=0,min=0,sec=0;
	sec = nowTime/50;//系统计时，在key.c中的TIM3中断服务函数中更新
	hour = sec/3600;
	min = (sec%3600)/60;
	sec = sec%60;
	sprintf((char *)timeStr,"%02d:%02d:%02d",hour,min,sec);//组合时间字符串
	LCD_ShowString(95,0,timeStr,RED,WHITE,16,0);
}

