#ifndef __SETTING_H
#define __SETTING_H			  	 
#include "sys.h"
#include "flash.h"
#include "adc.h"

#pragma pack(1)//���ֽڶ��룬����Ҫ��
//��Ҫ����127��16λ��
//������1+8*3+8*2+8+1+2+1+1
typedef struct _set_Config// �û����ýṹ��
{
	u16 writeFlag;//�Ƿ��һ��д��=2�ֽ�16λ
	u16 chLower[chNum];//ң�˵���Сֵ=2*chNum
	u16 chMiddle[chNum];//ң�˵���ֵ
	u16 chUpper[chNum];//ң�˵����ֵ
	int PWMadjustValue[chNum];//΢��PWMռ�ձ�=4�ֽ�*chNum
	u8 chReverse[chNum];//ͨ����������1Ϊ������0Ϊ��ת
	u8 PWMadjustUnit;//΢����λ
	float warnBatVolt;//������ѹ=4���ֽ�32λ
	u8 throttlePreference;//���������ţ�1Ϊ��������
	u16 batVoltAdjust;//��ص�ѹУ׼ֵ
	u8 modelType;//ģ������
	u8 NRF_Mode;//�Ƿ��������߷���
	u8 keySound;//�Ƿ��а�����Ч
	u8 onImage;//��������0,1
	float RecWarnBatVolt;//���ջ��ı�����ѹ
	u8 clockMode;//�����Ƿ񱨾�
	u8 clockTime;//����ʱ��5min
	u8 clockCheck;//�����Ƿ��Լ�һ������
	u8 throttleProtect;//���ű���ֵ0%
	u8 PPM_Out;//�Ƿ�PPM���
	u8 NRF_Power;//NRF���书�� 
}set_Config;
#pragma pack()


extern volatile set_Config setData;
extern volatile u32 setDataSize;
void SET_Init(void);
void resetData(void);

#endif
