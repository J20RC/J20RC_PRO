/*
J20��ģң�������װ�(ң������)
	΢��������STM32F103RCT6
	�汾��J20RC_PRO_V1.0.0
	����˵����Doc/ReadMe.txt
	�ֿ⣺https://github.com/J20RC/J20RC_PRO
*/
#include "main.h"
#include "pic.h"

/*����Ԥ����*/
void keyEventHandle(void);
void menuEventHandle(void);

/*��������*/
u16 loca;//�������
u16 thrNum;//���Ż����Ĵ�С
extern u8 batVoltStr[8];//��ص�ѹ�ַ���
extern u8 timeStr[9];//ʱ���ַ���
u16 loopCount = 0;//ѭ����������
u16 clockCount = 0;

float t = 0.0;
/*ֻ�ڳ���ʼʱ����һ�εĴ���*/
void setup(void)
{
	delay_init();//��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2��2λ��ռ���ȼ���2λ�����ȼ�
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,160,20,J20RC_BG);//�ϰ벿�����
	LCD_ShowPicture(0,20,160,80,J20RC_LOGO);
	LCD_Fill(0,100,160,128,J20RC_BG);//�°벿�����
	LCD_BLK_Set();//�򿪱���
	delay_ms(10);
//	usart_init(115200);//��ʼ������1��������Ϊ115200
//	TIM2_Init(1999,71);//1MHz��ÿ10ms����ADC����һ��
	TIM3_Init(19999,71);//1MHz��ÿ20ms��ⰴ��һ�Σ�
//	DMA1_Init();	//DMA��ʼ��
//	ADC_Pin_Init();		//ADC��ʼ��
//	SET_Init();	//��ȡ�û�����
//	BEEPER_Init();	//BEEPER��ʼ��
//	KEY_Init();		//KEY��ʼ��
//	NRF24L01_Init();//NRF24L01��ʼ��
//	PPM_Init();//PPM���ų�ʼ��
	
//	beeperOnce(20);//��������һ��
//	while(NRF24L01_Check())
//	{
// 		delay_ms(100);
//		Beeper = !Beeper;//������5Hz��������ʾ����ģ�����
//	}
//	Beeper = 0;//������ֹͣ��
//	delay_ms(1000);
//	
//	if(setData.clockCheck == ON)//���ſ����Լ�
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
//	if(setData.NRF_Mode == ON)  NRF24L01_TX_Mode(setData.NRF_Power);//����ģʽ
//	else NRF24L01_LowPower_Mode();//����ģʽ
}

/*����ѭ��ִ�еĴ���*/
void loop(void)
{
//	drawClockTime();
}

/*������*/
int main()
{
	setup();
	while(1)
	{
		loop();
	}
}


