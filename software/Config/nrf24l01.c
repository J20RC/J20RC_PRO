#include "nrf24l01.h"
#include "delay.h"
#include "spi.h"
#include "usart.h"
#include "adc.h"
	
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};

/*=======================================================
* ��  ����void NRF24L01_Init(void)
* ��  �ܣ�NRF24L01��ʼ��
* ��  ������
* ����ֵ����
* ��  ע����ӦGPIO����
=======================================================*/
void NRF24L01_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,G�˿�ʱ��
    	
	#ifdef NRF_PIN
	/*V2.0�汾PCB�Ľ���*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PB12����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	//��ʼ��PB12�������-NRF_CSN
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��PA8�������-NRF_CE
				
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA9 �ж���������-NRF_IRQ  
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	#else
	/*V1.0�汾PCB�Ľ���*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��PA8�������-NRF_CSN
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��PA9�������-NRF_CE
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB12 �ж���������-NRF_IRQ  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	#endif
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9);//PA8,9����	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12����
	
	SPI2_Init();    		//��ʼ��SPI	 
 
	SPI_Cmd(SPI2, DISABLE); // SPI���費ʹ�ܣ��ȹر�SPI���ٽ�������

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI����
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�0
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����0
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
			 
	NRF24L01_CE=0; 			//ʹ��24L01����CSNΪ�͵�����£�CEЭͬNRF24L01��CONFIG�Ĵ�����ͬ����NRF24L01��״̬
	NRF24L01_CSN=1;			//SPIƬѡȡ�����͵�ƽʱ���� 
	 		 	 
}
/*=======================================================
* ��  ����u8 NRF24L01_Check(void)
* ��  �ܣ����NRF24L01�Ƿ����
* ��  ������
* ����ֵ��0:�ɹ���1:ʧ��
* ��  ע����NRF24L01�ķ��͵�ַ�Ĵ���д��5�ֽ������ٶ�����,
		  �ж�24L01�Ƿ�����������
=======================================================*/	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ 
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}	 	 
/*=======================================================
* ��  ����u8 NRF24L01_Write_Reg(u8 reg,u8 value)
* ��  �ܣ���Ĵ���д��һ�ֽ�����
* ��  ����res:�Ĵ�����ַ;value:д���ֵ
* ����ֵ��status:��ȡ�ļĴ���״ֵ̬
=======================================================*/
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CSN=0;                 //ʹ��SPI����
  	status =SPI2_ReadWriteByte(reg);//���ͼĴ����� 
  	SPI2_ReadWriteByte(value);      //д��Ĵ�����ֵ
  	NRF24L01_CSN=1;                 //��ֹSPI����	   
  	return(status);       			//����״ֵ̬
}
/*=======================================================
* ��  ����u8 NRF24L01_Read_Reg(u8 reg)
* ��  �ܣ��ӼĴ�����ȡһ�ֽ�����
* ��  ����res:�Ĵ�����ַ
* ����ֵ��reg_val:��ȡ��ֵ
=======================================================*/
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����		
  	SPI2_ReadWriteByte(reg);   //���ͼĴ�����
  	reg_val=SPI2_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
  	NRF24L01_CSN = 1;          //��ֹSPI����		    
  	return(reg_val);           //����״ֵ̬
}	
/*=======================================================
* ��  ����u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
* ��  �ܣ���ָ��λ�ö�ȡһ�����ȵ�����
* ��  ����reg:ָ��λ��;*pBuf:ָ�����ݵ��׵�ַ;len:���ݳ���
* ����ֵ��status:�Ĵ�����״̬
=======================================================*/
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
  	NRF24L01_CSN = 0;           //ʹ��SPI����
  	status=SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI2_ReadWriteByte(0XFF);//��������
  	NRF24L01_CSN=1;       //�ر�SPI����
  	return status;        //���ض�����״ֵ̬
}
/*=======================================================
* ��  ����u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
* ��  �ܣ���ָ��λ��д��һ�����ȵ�����
* ��  ����reg:ָ��λ��;*pBuf:ָ�����ݵ��׵�ַ;len:���ݳ���
* ����ֵ��status:�Ĵ�����״̬
=======================================================*/
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����
  	status = SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); //д������	 
  	NRF24L01_CSN = 1;       //�ر�SPI����
  	return status;          //���ض�����״ֵ̬
}	
/*=======================================================
* ��  ����u8 NRF24L01_TxPacket(u8 *txbuf)
* ��  �ܣ�NRF24L01����һ������
* ��  ����*txbuf�����������ݵ��׵�ַ
* ����ֵ��MAX_TX:����ط�����;TX_OK:�������;0xFF:����ʧ��
=======================================================*/
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�����FIFO��������TXBUF 32���ֽ�
 	NRF24L01_CE=1;//��������	   
	//while(NRF24L01_IRQ!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	//return TX_OK;//���ܷ��ͳɹ����һֱ��������
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
/*=======================================================
* ��  ����u8 NRF24L01_RxPacket(u8 *rxbuf)
* ��  �ܣ�NRF24L01����һ������
* ��  ����*rxbuf���ȴ��������ݵ��׵�ַ
* ����ֵ��0:���ճɹ�;1:��������ʧ��
=======================================================*/
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}	
/*=======================================================
* ��  ����void NRF24L01_RX_Mode(void)
* ��  �ܣ�NRF24L01����ģʽ����
* ��  ������
* ����ֵ����
* ��  ע������RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
		  ��CE��ߺ�,������RXģʽ,�����Խ���������
=======================================================*/ 
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	  
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
}	
/*=======================================================
* ��  ����void NRF24L01_TX_Mode(void)
* ��  �ܣ�NRF24L01����ģʽ����
* ��  ����power:���书�� //0x0f=0dBm;0x0d=-6dBm;0xb=-12dBm;0x09=-18dBm;����Խ��dBmԽ��
* ����ֵ����
* ��  ע������TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,
		  ���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
		  PWR_UP,CRCʹ�ܣ�CEΪ�ߴ���10us,���������͡�
=======================================================*/ 
 
void NRF24L01_TX_Mode(u8 power)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,power);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
}

/*
  * ��������: NRF24L01����͹���ģʽ
*/
void NRF24L01_LowPower_Mode(void)
{
	NRF24L01_CE=0;//��ʹ��NRF
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0c);		//���ù���ģʽ:����ģʽ
}
	
u8 sendDataPacket(void)
{
	u8 chPacket[32];//���͵����ݰ�
	u16 t=0;
	u8 sendIsOK;//���ͳɹ����
	for(t=0;t<16;t++)
	{
		if(t==0)//��������ͷ00
		{
			chPacket[2*t]=0x00;
			chPacket[2*t+1]=0x00;
		}
		else if(t<=chNum)
		{
			chPacket[2*t] = (u8)(PWMvalue[t-1]>>8)&0xFF; //��8λ����u16��ֳ�����u8���д���
			chPacket[2*t+1] = (u8)PWMvalue[t-1]&0xFF; //��8λ
		}
		else
		{
			chPacket[2*t]=0xFF;
			chPacket[2*t+1]=0xFF;
		}
	} 
	sendIsOK = NRF24L01_TxPacket(chPacket);
	return sendIsOK;
}



