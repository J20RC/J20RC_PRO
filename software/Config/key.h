#ifndef __KEY_H
#define __KEY_H	 
/*EC11��ת�������汾*/
#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h" 

#define BM_CLK PBin(1)// ��ת������CLK����
#define BM_DT PBin(10)// ��ת������DT����

#define MENU_up 	0x06//�˵������¼���־
#define MENU_down	0x07//�˵������¼���־
#define MENU_enter	0x08//ȷ�������¼���־
#define MENU_esc	0x09//���ذ����¼���־
#define MENU_home	0x0A//�����水���¼���־
#define NUM_up 		0x0B//��ֵ+�����¼���־
#define NUM_down 	0x0C//��ֵ-�����¼���־

typedef struct // ���찴����ʼ����
{
	GPIOMode_TypeDef GPIO_Mode; // ��ʼ������ģʽ
	GPIO_TypeDef* GPIOx; // ��ʼ��������
	uint16_t GPIO_Pin_x; // ��ʼ���������ź�
	uint32_t RCC_APB2Periph_GPIOx; // ��ʼ��ʱ��
}Key_Init;

typedef enum _KEY_STATUS_LIST // ����״̬
{
	KEY_NULL = 0x00, // �޶���
	KEY_SURE = 0x01, // ȷ��״̬
	KEY_UP   = 0x02, // ����̧��
	KEY_DOWN = 0x03, // ��������
	KEY_LONG = 0x04, // ����
}KEY_STATUS_LIST;

typedef struct _KEY_COMPONENTS // ״̬����
{
    FunctionalState KEY_SHIELD; //�������Σ�DISABLE(0):���Σ�ENABLE(1):������
	uint8_t KEY_COUNT;        	//������������
    BitAction KEY_LEVEL;        //���հ���״̬������Bit_SET(1)��̧��Bit_RESET(0)
    BitAction KEY_DOWN_LEVEL;   //����ʱ������IOʵ�ʵĵ�ƽ
    KEY_STATUS_LIST KEY_STATUS;       //����״̬
    KEY_STATUS_LIST KEY_EVENT;        //�����¼�
    BitAction (*READ_PIN)(Key_Init Key);//��IO��ƽ����
}KEY_COMPONENTS;


typedef struct // ������
{
	Key_Init Key; // �̳г�ʼ������
	KEY_COMPONENTS Status; // �̳�״̬������
}Key_Config;

#ifdef EC11_VERSION
typedef enum // ����ע���
{
	CH1Left,
	CH1Right,
	CH2Down,
	CH2Up,
	CH4Left,
	CH4Right,// �û���ӵİ�ť����
	BM_SW,
	KEY_NUM, // ����Ҫ�еļ�¼��ť���������������
}KEY_LIST;
#else
typedef enum // ����ע���
{
	CH1Left,
	CH1Right,
	CH2Down,
	CH2Up,
	CH4Left,
	CH4Right,
	MENU,// �û���ӵİ�ť����
	KEY_NUM, // ����Ҫ�еļ�¼��ť���������������
}KEY_LIST;
#endif
extern volatile u16 menuEvent[4];
extern volatile u8 keyEvent;
extern volatile u8 menuMode;

void KEY_Init(void);//IO��ʼ��
void Creat_Key(Key_Init* Init); // ��ʼ����ť����
void ReadKeyStatus(void); // ״̬������
void TIM3_Init(u16 arr,u16 psc);
void encoder_Init(void);//IO��ʼ��
#endif
