#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "math.h"
#include "Motor_Control.h"
#include <string.h>
#include "stmflash.h"



#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);

#endif


