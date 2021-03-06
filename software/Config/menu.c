#include "main.h"

u16 homeGoIndex = tdwt;//home的快速跳转菜单页
u8 volatile nowMenuIndex = 0;
u8 volatile lastMenuIndex = 0;
extern unsigned char logo[];
extern unsigned char logoR[];
char batVoltStr[8];
char timeStr[9];

