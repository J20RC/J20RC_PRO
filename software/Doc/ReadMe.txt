J20进阶版遥控器

1. TFTLCD显示屏：
标准14PIN，驱动芯片ST7735S，分辨率128x160，16位真彩色

2. 引脚定义：
Pin Nb	PINs		FUNCTIONs	LABELs
2	PC13-TAMPER-RTC	GPIO_Output	LCD_LED
3	PC14-OSC32_IN	GPIO_Output	BEEPER
4	PC15-OSC32_OUT	GPIO_Input	CH16
5	PD0-OSC_IN	RCC_OSC_IN	
6	PD1-OSC_OUT	RCC_OSC_OUT	
8	PC0		ADC1_IN10	CH11
9	PC1		ADC1_IN11	CH12
10	PC2		ADC1_IN12	CH13
11	PC3		ADC1_IN13	CH14
14	PA0-WKUP	ADC1_IN0		CH1
15	PA1		ADC1_IN1		CH2
16	PA2		ADC1_IN2		CH3
17	PA3		ADC1_IN3		CH4
20	PA4		ADC1_IN4		CH5
21	PA5		ADC1_IN5		CH6
22	PA6		ADC1_IN6		CH7
23	PA7		ADC1_IN7		CH8
24	PC4		ADC1_IN14	CH15
25	PC5		ADC1_IN15	Vm
26	PB0		ADC1_IN8		CH9
27	PB1		ADC1_IN9		CH10
28	PB2		GPIO_Input	BOOT1
29	PB10		GPIO_Output	NRF_CE
30	PB11		GPIO_EXTI11	NRF_IRQ
33	PB12		SPI2_NSS		NRF_CSN
34	PB13		SPI2_SCK		NRF_SCK
35	PB14		SPI2_MISO	NRF_MISO
36	PB15		SPI2_MOSI	NRF_MOSI
37	PC6		GPIO_Input	CH1_LEFT
38	PC7		GPIO_Input	CH1_RIGHT
39	PC8		GPIO_Input	CH2_DOWN
40	PC9		GPIO_Input	CH2_UP
41	PA8		GPIO_Output	PPM
42	PA9		USART1_TX	TX_BM_DT
43	PA10		USART1_RX	RX_BM_SW
44	PA11		USB_DM	
45	PA12		USB_DP	
46	PA13		SYS_JTMS-SWDIO	SWDIO
49	PA14		SYS_JTCK-SWCLK	SWCLK
50	PA15		GPIO_Input	CH3_DOWN
51	PC10		GPIO_Input	CH3_UP
52	PC11		GPIO_Input	CH4_LEFT
53	PC12		GPIO_Input	CH4_RIGHT
54	PD2		GPIO_Output	LCD_CS
55	PB3		SPI1_SCK		LCD_SCK
56	PB4		SPI1_MISO	LCD_SDA
57	PB5		SPI1_MOSI	LCD_A0
58	PB6		GPIO_Output	LCD_RST
59	PB7		GPIO_Output	BM_SCK
61	PB8	I2C1_SCL	EEPROM_SCL
62	PB9	I2C1_SDA	EEPROM_SDA


3.关于EC11旋转编码器版本、按键版本之间的兼容

	本工程默认适配EC11旋转编码器版本，如果您想使用按键版本：
	请在Keil5中打开工程后，点击魔法棒(Options for Target...)
	点击选项栏 C/C++ >> Preprocessor Symbols 的define文本框中删除 EC11_VERSION 即可。
	
	===================EC11旋转编码器版本===================
	六个按键：
	1	CH1Left		接PB5	【home】
	2	CH1Right		接PB4
	3	CH2Down		接PB3	【确定】
	4	CH2Up		接PA15	【返回】
	5	CH4Left		接PA12	【数值-】
	6	CH4Right		接PA11	【数值+】
	7 	旋转编码器模块：
		GND	电源地
		VCC	接3.3V电源
		SW	接PB11
		DT	接PB10
		CLK	接PB1
	短按旋转编码器进入菜单，长按旋转编码器/短按CH1Left键退出菜单。

	按键布局建议：
                                                    4
                                                    |
                                                    3                        
                5-------6                           1-------2
	 
                                   -----------------
                               4 |        屏幕          |  7
                                   -----------------

	========================按键版本========================
	七个按键定义：
	1	CH1Left    接PB5	【确定】
	2	CH1Right  接PB4	【返回】
	3	CH2Down 接PB3	【菜单向下】
	4	CH2Up      接PA15	【菜单向上】
	5	CH4Left    接PA12	【数值-】
	6	CH4Right  接PA11	【数值+】
	7	MENU      接PB11	【菜单】
	短按MENU键进入/退出菜单，CH2Down键和CH2Up键轮询菜单。

	按键布局建议：

                       4                        1
	5---+---6                   2
                       3                         7


