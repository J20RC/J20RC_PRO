#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h" //�ǵ���Ӵ�ͷ�ļ�����Ϊconfig.c�õ�GPIO��غ�����
#include "sys.h"

#define adcNum 9		//����ͨ����
#define chNum 8	//ң��ͨ����
#define sampleNum 10 //ÿ��ͨ����������

extern volatile u16 chValue[adcNum*sampleNum];//ADC����ֵ
extern volatile u16 chResult[chNum];//�˲����ADC����ֵ
extern volatile u16 PWMvalue[chNum];//����PWMռ�ձ�
extern volatile float batVolt;//��ص�ѹ
extern volatile u8 batVoltSignal;//�Ƿ񱨾�

void TIM2_Init(u16 arr,u16 psc);//TIM2��ʱ����ʼ��
void DMA1_Init(void);
void GPIOA_Init(void);
void ADC_Pin_Init(void);//ADC1��ʼ��
u16 Get_Adc(u8 ch); //��ȡһ��ADC��ֵ
u16 Get_Adc_Average(u8 ch,u8 times);//ADC����ֵ���о�ֵ�˲�
float map(float value,float fromLow,float fromHigh,float toLow,float toHigh);//ӳ�亯��
int mapChValue(int val, int lower, int middle, int upper, int reverse);//ͨ������ӳ�亯��
int GetMedianNum(volatile u16 * bArray, int ch);//��ֵ�˲�
#endif
