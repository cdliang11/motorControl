/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/
#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "delay.h"
#include "usart.h"
														   
void  Adc_Init(void);//ADC初始化
u16 Get_Adc_Average(u8 ch,u8 times); //获取多次ADC采集的平均值


#endif

