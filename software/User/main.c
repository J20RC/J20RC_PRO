/*
J20航模遥控器进阶版(遥控器端)
	微控制器：STM32F103RCT6
	版本：J20RC_PRO_V1.0.0
	具体说明见Doc/ReadMe.txt
	仓库：https://github.com/J20RC/J20RC_PRO
*/
#include "main.h"
#include "pic.h"

/*函数预定义*/
void keyEventHandle(void);
void menuEventHandle(void);

/*变量定义*/
u16 loca;//存放坐标
u16 thrNum;//油门换算后的大小
extern u8 batVoltStr[8];//电池电压字符串
extern u8 timeStr[9];//时间字符串
u16 loopCount = 0;//循环次数计数
u16 clockCount = 0;

float t = 0.0;
/*只在程序开始时运行一次的代码*/
void setup(void)
{
	delay_init();//初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2，2位抢占优先级和2位子优先级
	LCD_Init();//LCD初始化
	LCD_Fill(0,0,160,20,J20RC_BG);//上半部分填充
	LCD_ShowPicture(0,20,160,80,J20RC_LOGO);
	LCD_Fill(0,100,160,128,J20RC_BG);//下半部分填充
	LCD_BLK_Set();//打开背光
	delay_ms(10);
//	usart_init(115200);//初始化串口1，波特率为115200
//	TIM2_Init(1999,71);//1MHz，每10ms进行ADC采样一次
	TIM3_Init(19999,71);//1MHz，每20ms检测按键一次；
//	DMA1_Init();	//DMA初始化
//	ADC_Pin_Init();		//ADC初始化
//	SET_Init();	//读取用户数据
//	BEEPER_Init();	//BEEPER初始化
//	KEY_Init();		//KEY初始化
//	NRF24L01_Init();//NRF24L01初始化
//	PPM_Init();//PPM引脚初始化
	
//	beeperOnce(20);//蜂鸣器响一下
//	while(NRF24L01_Check())
//	{
// 		delay_ms(100);
//		Beeper = !Beeper;//蜂鸣器5Hz报警，表示无线模块故障
//	}
//	Beeper = 0;//蜂鸣器停止响
//	delay_ms(1000);
//	
//	if(setData.clockCheck == ON)//油门开机自检
//	{
//		if(PWMvalue[2]>1200)
//		{
//		}
//		while(PWMvalue[2]>1200)
//		{
//			if(menuEvent[0])
//			{
//				menuEvent[0] = 0;
//				break;
//			}
//			delay_ms(50);
//		}
//	}
//	if(setData.NRF_Mode == ON)  NRF24L01_TX_Mode(setData.NRF_Power);//发射模式
//	else NRF24L01_LowPower_Mode();//掉电模式
}

/*不断循环执行的代码*/
void loop(void)
{
//	drawClockTime();
}

/*主函数*/
int main()
{
	setup();
	while(1)
	{
		loop();
	}
}


