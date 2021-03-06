#include "setting.h"
#include "main.h"

volatile set_Config setData;
volatile u32 setDataSize=sizeof(setData)/2;
//�ָ�Ĭ������
void resetData(void)
{
	for(int i=0;i<chNum;i++)
	{
		setData.chLower[i] 	= 0;	//ң�˵���Сֵ
		setData.chMiddle[i] = 2047;	//ң�˵���ֵ
		setData.chUpper[i] 	= 4095;	//ң�˵����ֵ
		setData.PWMadjustValue[i]=0;//΢��ֵ
		setData.chReverse[i] = OFF;	//ͨ����������1Ϊ������0Ϊ��ת
	}
	setData.PWMadjustUnit = 2;//΢����λ
	setData.warnBatVolt = 3.7;//������ѹ
	setData.throttlePreference = ON;//��������
	setData.batVoltAdjust = 1000;//��ص�ѹУ׼ֵ
	setData.modelType = 0;//ģ�����ͣ���0����1����2
	setData.NRF_Mode = ON;//���߷��䣬Ĭ������
	setData.keySound = ON;//����������Ĭ������
	setData.onImage = 1;//�������棬0����,1����
	setData.RecWarnBatVolt = 11.8;//���ջ��ı�����ѹ
	setData.clockMode = OFF;//�����Ƿ񱨾�
	setData.clockTime = 5;//����ʱ��5min
	setData.clockCheck = OFF;//�����Ƿ��Լ�һ������
	setData.throttleProtect = 0;//���ű���ֵ0%
	setData.PPM_Out = OFF;//�Ƿ�PPM���
	setData.NRF_Power = 0x0f;//0x0f=0dBm;0x0d=-6dBm;0xb=-12dBm;0x09=-18dBm;����Խ��dBmԽ��
}
void SET_Init(void)
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16 *)&setData,setDataSize);//��FLASH�ж�ȡ�ṹ��
	if(setData.writeFlag!=0x1111){
		setData.writeFlag=0x1111;//�Ƿ��һ��д��
		resetData();
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16 *)&setData,setDataSize);//д��FLASH
	}
}

