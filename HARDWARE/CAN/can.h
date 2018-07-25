/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/
#ifndef _BSP_CAN_H
#define _BSP_CAN_H	 

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Motor_Control.h"

void CAN1_Init(u8 tsjw, u8 tbs2, u8 tbs1, u16 brp);//CAN初始化
u8 CAN1_SendMsg(u8* msg, u8 len, u32 ID);//消息发送

#endif

