#include "main.h"
#include "tim.h"

volatile u32 nowTime = 0;//��������ʱ�䣬��λ20ms����key.c�и���
volatile u32 clockTime = 0;//���Ӷ�ʱʱ�䣬��λ20ms����key.c�и���
extern u8 timeStr[9];//ʱ���ַ���

void drawClockTime(void)
{
	u16 hour=0,min=0,sec=0;
	sec = nowTime/50;//ϵͳ��ʱ����key.c�е�TIM3�жϷ������и���
	hour = sec/3600;
	min = (sec%3600)/60;
	sec = sec%60;
	sprintf((char *)timeStr,"%02d:%02d:%02d",hour,min,sec);//���ʱ���ַ���
	LCD_ShowString(95,0,timeStr,RED,WHITE,16,0);
}

