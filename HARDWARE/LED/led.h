/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/
#ifndef _LED_H_
#define _LED_H_
#include "sys.h"

#define LED1 PBout(12) //D2
#define LED2 PBout(13) //D3
#define LED3 PBout(14) //D4


void LED_Init(void);  //led接地 led初始化函数



#endif
