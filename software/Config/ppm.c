#include "ppm.h"

u16 PPM_Array[PPM_NUM] = {MS05, 1000,MS05,1000,MS05,500,MS05,1000,MS05, 1000,MS05,1000,MS05,1000,MS05,1000,MS05,8000};
u16 PPM_Index = 0;//PPM����������
	
/*TIM4���жϳ�ʼ��*/ 
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //TIM4���жϺ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ������������Ϊ������ȼ����ͻ�����
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

/*PPM���ų�ʼ��*/ 
static void PPM_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO����ʱ��
    //����PPM����Ϊ�����������,������岨��
    GPIO_InitStructure.GPIO_Pin = PPM_Pin; //PPM���ź�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
    GPIO_Init(PPM_GPIO_Port, &GPIO_InitStructure);//��ʼ��PPM�˿�
}
/*TIM4��ʼ��*/ 
void PPM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //ʹ��TIM4ʱ��
     
    TIM_TimeBaseStructure.TIM_Period = 500; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//���� ���� �����ж�
    
    PPM_GPIO_Configuration(); //GPIO��ʼ��
    NVIC_Configuration(); //�жϳ�ʼ��
	if(setData.PPM_Out == ON) TIM_Cmd(TIM4, ENABLE); //ʹ��TIM4
	else TIM_Cmd(TIM4, DISABLE); //��ʹ��TIM4
    PPM = 0;//ǰ500us����͵�ƽ
}

/*TIM4�жϷ����ӳ���*/
void TIM4_IRQHandler(void)
{  
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {   
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // �����־λ
        TIM4->ARR = PPM_Array[PPM_Index]-1;//����TIM4���Զ���װ��ֵ����1�Ǹ����г�����ʱ��
        PPM = !PPM;//���ĵ�ƽ
        PPM_Index++;
        if(PPM_Index>=PPM_NUM)
        {
            PPM_Index = 0;
        }
    }
}

