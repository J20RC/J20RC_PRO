#include "beeper.h"

//������IO��ʼ��
void BEEPER_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PC�˿�ʱ��
	
	//��ʼ�� ����������PA10	  �������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA10
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);//����͵�ƽ
}
//����������һ��
//freq��Ƶ��1~50000
//void beeperOnce(u16 freq)
//{
//	for (u16 i=0; i<(u16)freq/20; i++) {
//		Beeper = 1;
//		delay_us((u16)50000/freq);
//		Beeper = 0;
//		delay_us((u16)50000/freq);
//	}
//}
void beeperOnce(u16 nms)
{
	Beeper = 1;
	delay_ms(nms);
	Beeper = 0;
}
//��������ģʽ������
void keyDownSound(void)
{
	if (setData.keySound==ON) {
		beeperOnce(6);
	}
}
