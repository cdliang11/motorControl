/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/
#ifndef _POT_H
#define _POT_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "math.h"
#include "Motor_Control.h"

extern float angle[4];

void get_pot_adc(void);//电位器电压采集
void adc_angle_transform(void);//电位器角度转换
void angle_speed_transform(void);//副履带复位

#endif
