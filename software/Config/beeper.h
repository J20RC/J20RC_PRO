#ifndef __BEEPER_H
#define __BEEPER_H	 
#include "main.h"

#define Beeper PAout(10)	//PA10

void BEEPER_Init(void);//��ʼ��
void beeperOnce(u16 nms);//����������һ��
void keyDownSound(void);
#endif
