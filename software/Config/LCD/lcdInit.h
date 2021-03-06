#ifndef __LCDINIT_H
#define __LCDINIT_H

#include "sys.h"

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ����(0������ʾ��1������ʾ) 2��3Ϊ����(2������ʾ��3������ʾ)


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif


/*
TFTLCD���Ŷ���
LCD_LED -> PC13
LCD_RST -> PB6
LCD_A0	-> PB5
LCD_SDA -> PB4
LCD_SCK -> PB3
LCD_CS	-> PD2
*/
//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//SCK=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_4)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_6)//RES
#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_5)//A0=DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_5)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOD,GPIO_Pin_2)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOD,GPIO_Pin_2)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOC,GPIO_Pin_13)//LED=BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOC,GPIO_Pin_13)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




