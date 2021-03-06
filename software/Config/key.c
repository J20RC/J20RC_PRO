#include "key.h"
#include "main.h"
/*
EC11��ת�������汾
�ο�����https://blog.csdn.net/qq_42679566/article/details/105892105��ԭ�Ĵ���������
*/
#define KEY_LONG_DOWN_DELAY 30 	// ����30��TIM3��ʱ���ж�=600ms�㳤��	
#define DBGMCU_CR  (*((volatile u32 *)0xE0042004))
	
Key_Config Key_Buf[KEY_NUM];	// ������������
volatile u16 menuEvent[4];
volatile u8 keyEvent = 0;
volatile u8 menuMode = 0;//�˵�ҳ���Ƿ�Ϊ�ɱ༭״̬��1Ϊ�ǣ�0Ϊ��

/*ͨ�ö�ʱ��3�жϳ�ʼ����ʹ��TIM3���ư�����ʱ���
  ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
* ������arr���Զ���װֵ��
		psc��ʱ��Ԥ��Ƶ��
*/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 		//ʱ��ʹ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; // ���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷָ�Ϊ0,��Ȼʹ��72MHz
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//��������ж�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)   //TIM3�жϷ�����
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		// �жϴ������
		ReadKeyStatus();  //����״̬��
		volatile u8 i,status,ch;
		for(i = 0;i < KEY_NUM;i++)
    	{
			status = Key_Buf[i].Status.KEY_EVENT;
			if(i<KEY_NUM-1 && status==KEY_DOWN && nowMenuIndex==home) //������ʱ���̰�
			{
				if(i==CH1Left | i==CH1Right) ch = (setData.throttlePreference? 0 : 3);
				if(i==CH2Down | i==CH2Up) ch = (setData.throttlePreference? 1 : 1);
				if(i==CH4Left | i==CH4Right) ch = (setData.throttlePreference? 3 : 0);//�ڼ���ͨ��
				if(setData.PWMadjustValue[ch]>300-setData.PWMadjustUnit) setData.PWMadjustValue[ch]=300-setData.PWMadjustUnit;//����΢����Χ
				if(setData.PWMadjustValue[ch]<setData.PWMadjustUnit-300) setData.PWMadjustValue[ch]=setData.PWMadjustUnit-300;//����΢����Χ
				if(i%2==0) setData.PWMadjustValue[ch] -= setData.PWMadjustUnit;//΢����
				else setData.PWMadjustValue[ch] += setData.PWMadjustUnit;//΢����
				keyEvent = i+1;//�а������±�־
			}
			if(i<KEY_NUM-1 && status==KEY_LONG && nowMenuIndex==home) //������ʱ������
			{
				Key_Buf[i].Status.KEY_COUNT = 29;//���ڼӼ��ٶȣ�ҪС��KEY_LONG_DOWN_DELAY
				if(i==CH1Left | i==CH1Right) ch = (setData.throttlePreference? 0 : 3);
				if(i==CH2Down | i==CH2Up) ch = (setData.throttlePreference? 1 : 1);
				if(i==CH4Left | i==CH4Right) ch = (setData.throttlePreference? 3 : 0);//�ڼ���ͨ��
				if(setData.PWMadjustValue[ch]>300-setData.PWMadjustUnit) setData.PWMadjustValue[ch]=300-setData.PWMadjustUnit;//����΢����Χ
				if(setData.PWMadjustValue[ch]<setData.PWMadjustUnit-300) setData.PWMadjustValue[ch]=setData.PWMadjustUnit-300;//����΢����Χ
				
				if(i%2==0) setData.PWMadjustValue[ch] -= setData.PWMadjustUnit;
				else setData.PWMadjustValue[ch] += setData.PWMadjustUnit;
				keyEvent = i+1;//�а������±�־
			}
			if(i==CH4Left && status==KEY_LONG){
				Key_Buf[i].Status.KEY_COUNT = 29;//���ڼӼ��ٶȣ�ҪС��KEY_LONG_DOWN_DELAY
				if(nowMenuIndex!=home)
				{	
					menuEvent[0]=1;//�˵��¼�
					menuEvent[1]=NUM_down; //����CH4Left	����ֵ-��
				}
			}
			if(i==CH4Right && status==KEY_LONG){
				Key_Buf[i].Status.KEY_COUNT = 29;//���ڼӼ��ٶȣ�ҪС��KEY_LONG_DOWN_DELAY
				if(nowMenuIndex!=home) 
				{	
					menuEvent[0]=1;//�˵��¼�
					menuEvent[1]=NUM_up; //����CH4Right		����ֵ+��
				}
			}
			#ifdef EC11_VERSION
			if(i==CH1Left && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_home; //����CH1Left	��home��
			}
			if(i==CH2Down && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_enter; //����CH2Down	��ȷ����
			}
			if(i==CH2Up && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_esc; //����CH2Up		�����ء�
			}
			if(i==CH4Left && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=NUM_down; //����CH4Left	����ֵ-��
			}
			if(i==CH4Right && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=NUM_up; //����CH4Right		����ֵ+��
			}
			if(i==BM_SW && status==KEY_DOWN)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_enter; //��ת�������̰�ȷ��
				
			}
			if(i==BM_SW && status==KEY_LONG)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_home; //��ת����������home
			}
			#else
			if(i==CH1Left && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_enter; //����CH1Left	��ȷ����
			}
			if(i==CH1Right && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_esc; //����CH1Right	�����ء�
			}
			if(i==CH2Down && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_down; //����CH2Down	���˵����¡�
			}
			if(i==CH2Up && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_up; //����CH2Up		���˵����ϡ�
			}
			if(i==CH2Down && status==KEY_LONG)
			{/*����*/
				Key_Buf[i].Status.KEY_COUNT = 29;//���ڼӼ��ٶȣ�ҪС��KEY_LONG_DOWN_DELAY
				if(nowMenuIndex!=home)
				{	
					menuEvent[0]=1;//�˵��¼�
					menuEvent[1]=MENU_down; //����CH2Down	���˵����¡�
				}
			}
			if(i==CH2Up && status==KEY_LONG)
			{/*����*/
				Key_Buf[i].Status.KEY_COUNT = 29;//���ڼӼ��ٶȣ�ҪС��KEY_LONG_DOWN_DELAY
				if(nowMenuIndex!=home) 
				{	
					menuEvent[0]=1;//�˵��¼�
					menuEvent[1]=MENU_up; //����CH2Up		���˵����ϡ�
				}
			}
			if(i==CH4Left && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=NUM_down; //����CH4Left	����ֵ-��
			}
			if(i==CH4Right && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=NUM_up; //����CH4Right		����ֵ+��
			}
			if(i==MENU && status==KEY_DOWN && nowMenuIndex==home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_enter; //����MENU		������˵���
				
			}
			if(i==MENU && status==KEY_DOWN && nowMenuIndex!=home)
			{
				menuEvent[0]=1;//�˵��¼�
				menuEvent[1]=MENU_home; //����MENU		���˳��˵���
			}
			#endif
//			if(status!=KEY_NULL) printf("%d,%d\r\n",i,status);
		}
		nowTime++;//20ms����һ��ϵͳ�δ�ʱ��
		clockTime++;//���Ӹ���
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
	}
}

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
	#ifdef EC11_VERSION
	encoder_Init();//���������ų�ʼ��
	#endif
	
	Key_Init KeyInit[KEY_NUM]=
	{ 
		{GPIO_Mode_IPU, GPIOB, GPIO_Pin_5, RCC_APB2Periph_GPIOB}, 	// ��ʼ������CH1Left	��home��
		{GPIO_Mode_IPU, GPIOB, GPIO_Pin_4, RCC_APB2Periph_GPIOB}, 	// ��ʼ������CH1Right
		{GPIO_Mode_IPU, GPIOB, GPIO_Pin_3, RCC_APB2Periph_GPIOB}, 	// ��ʼ������CH2Down	��ȷ����
		{GPIO_Mode_IPU, GPIOA, GPIO_Pin_15, RCC_APB2Periph_GPIOA}, 	// ��ʼ������CH2Up		�����ء�
		{GPIO_Mode_IPU, GPIOA, GPIO_Pin_12, RCC_APB2Periph_GPIOA}, 	// ��ʼ������CH4Left	����ֵ-��
		{GPIO_Mode_IPU, GPIOA, GPIO_Pin_11, RCC_APB2Periph_GPIOA}, 	// ��ʼ������CH4Right	����ֵ+��
		{GPIO_Mode_IPU, GPIOB, GPIO_Pin_11, RCC_APB2Periph_GPIOB}, 	// ��ʼ����ת������SW
	};
	Creat_Key(KeyInit); // ���ð�����ʼ������
	
	//STM32û�г����ͷ�PB3��Ϊ��ͨIO��ʹ�ã��л���SW���Կ��ͷ�PB3��PB4��PA15
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	DBGMCU_CR &=0xFFFFFFDF;  //���û����δ��룬PB3�ͻ�һֱ�ǵ͵�ƽ
}

static BitAction KEY_ReadPin(Key_Init Key) //������ȡ����
{
  return (BitAction)GPIO_ReadInputDataBit(Key.GPIOx,Key.GPIO_Pin_x);
}

void Creat_Key(Key_Init* Init)
{
	uint8_t i; 
	GPIO_InitTypeDef  GPIO_InitStructure[KEY_NUM];
  	for(i = 0;i < KEY_NUM;i++)
	{
		Key_Buf[i].Key = Init[i]; // ��ť����ĳ�ʼ�����Ը�ֵ
		RCC_APB2PeriphClockCmd(Key_Buf[i].Key.RCC_APB2Periph_GPIOx, ENABLE);//ʹ����Ӧʱ��
		GPIO_InitStructure[i].GPIO_Pin = Key_Buf[i].Key.GPIO_Pin_x;	//�趨����			
		GPIO_InitStructure[i].GPIO_Mode = Key_Buf[i].Key.GPIO_Mode; 	//�趨ģʽ		
		GPIO_Init(Key_Buf[i].Key.GPIOx, &GPIO_InitStructure[i]);       //��ʼ������
		// ��ʼ����ť�����״̬������
		Key_Buf[i].Status.KEY_SHIELD = ENABLE;
		Key_Buf[i].Status.KEY_COUNT = 0;
		Key_Buf[i].Status.KEY_LEVEL = Bit_RESET;
		if(Key_Buf[i].Key.GPIO_Mode == GPIO_Mode_IPU) // ����ģʽ���и�ֵ
			Key_Buf[i].Status.KEY_DOWN_LEVEL = Bit_RESET;
		else
			Key_Buf[i].Status.KEY_DOWN_LEVEL = Bit_SET;
		Key_Buf[i].Status.KEY_STATUS = KEY_NULL;
		Key_Buf[i].Status.KEY_EVENT = KEY_NULL;
		Key_Buf[i].Status.READ_PIN = KEY_ReadPin;	//��ֵ������ȡ����
	}
}

static void Get_Key_Level(void) // ����ʵ�ʰ��°�ť�ĵ�ƽȥ�������������Ľ��
{
    uint8_t i;
    
    for(i = 0;i < KEY_NUM;i++)
    {
        if(Key_Buf[i].Status.KEY_SHIELD == DISABLE)
            continue;
        if(Key_Buf[i].Status.READ_PIN(Key_Buf[i].Key) == Key_Buf[i].Status.KEY_DOWN_LEVEL)
            Key_Buf[i].Status.KEY_LEVEL = Bit_SET;
        else
            Key_Buf[i].Status.KEY_LEVEL = Bit_RESET;
    }
}

void ReadKeyStatus(void)
{
    uint8_t i;
	
    Get_Key_Level();
	
    for(i = 0;i < KEY_NUM;i++)
    {
        switch(Key_Buf[i].Status.KEY_STATUS)
        {
            //״̬0��û�а�������
            case KEY_NULL:
                if(Key_Buf[i].Status.KEY_LEVEL == Bit_SET)//�а�������
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_SURE;//ת��״̬1
					Key_Buf[i].Status.KEY_EVENT = KEY_NULL;//���¼�
                }
                else
                {
                    Key_Buf[i].Status.KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬1����������ȷ��
            case KEY_SURE:
                if(Key_Buf[i].Status.KEY_LEVEL == Bit_SET)//ȷ�Ϻ��ϴ���ͬ
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_DOWN;//ת��״̬2
					Key_Buf[i].Status.KEY_EVENT = KEY_DOWN;//�����¼�
                    Key_Buf[i].Status.KEY_COUNT = 0;//����������
                }
                else
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_NULL;//ת��״̬0
                    Key_Buf[i].Status.KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬2����������
            case KEY_DOWN:
                if(Key_Buf[i].Status.KEY_LEVEL != Bit_SET)//�����ͷţ��˿ڸߵ�ƽ
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_NULL;//ת��״̬0
                    Key_Buf[i].Status.KEY_EVENT = KEY_UP;//�ɿ��¼�
                }
                else if((Key_Buf[i].Status.KEY_LEVEL == Bit_SET)
					&& (++Key_Buf[i].Status.KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_LONG;//ת��״̬3
                    Key_Buf[i].Status.KEY_EVENT = KEY_LONG;//�����¼�
					Key_Buf[i].Status.KEY_COUNT = 0;//����������
                }
                else
                {
                    Key_Buf[i].Status.KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬3��������������
            case KEY_LONG:
                if(Key_Buf[i].Status.KEY_LEVEL != Bit_SET)//�����ͷţ��˿ڸߵ�ƽ
                {
                    Key_Buf[i].Status.KEY_STATUS = KEY_NULL;//ת��״̬0
                    Key_Buf[i].Status.KEY_EVENT = KEY_UP;//�ɿ��¼�
                }
                else if((Key_Buf[i].Status.KEY_LEVEL == Bit_SET) 
                && (++Key_Buf[i].Status.KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
                {
                    Key_Buf[i].Status.KEY_EVENT = KEY_LONG;//�����¼�
                    Key_Buf[i].Status.KEY_COUNT = 0;//����������
                }
                else
                {
                    Key_Buf[i].Status.KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
			default:
				break;
        }
	}
}
//��ת������CLK,DT���ų�ʼ��
void encoder_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_10; //PB1��PB10����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIOB
	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	//GPIOB1 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}

//�жϷ������������ת����������ת����
void EXTI1_IRQHandler(void)
{
	delay_ms(1);	//����������Ҫ
	menuEvent[0]=1;//�˵��¼�
	if(BM_CLK==BM_DT) //˳ʱ����ת
	{
		if(menuMode == 1) menuEvent[1] = NUM_up; //���ּ�
		else menuEvent[1]=MENU_up; //�˵���
	}
	else //��ʱ����ת
	{
		if(menuMode == 1) menuEvent[1] = NUM_down; //���ּ�
		else menuEvent[1]=MENU_down; //�˵���
	}
 	EXTI_ClearITPendingBit(EXTI_Line1);    //���LINE1�ϵ��жϱ�־λ 
}

