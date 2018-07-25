#include "sys.h"
#include "usart.h"	  


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/**************************************************************************
函数功能：USART1初始化函数
入口参数：bound: 波特率
返回  值：无
**************************************************************************/	

void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

/**************************************************************************
函数功能：USART1 中断服务函数
入口参数：无
返回  值：无
**************************************************************************/	
u16 PID_Buffer[3];
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	static u8 Flag_PID,Receive[50],i,j;
	static	u8 uart_receive=0;//
	static float Data;
	if(uart_receive=='a') Flag_PID=1;//PID参数写入起始位
	if(uart_receive=='b') Flag_PID=2;// PID 参数写入停止位
	
	if(Flag_PID==1)//采集数据
	{
		Receive[i]=uart_receive;
		i++;
	}
	/*
	a w P/I/D ... b
	*/
	if(Flag_PID==2)//分析数据
	{
		if(Receive[1]=='w')
		{
			for(j = i;j >= 4; j--)
			{
				Data+=(Receive[j-1]-'0')*pow(10,i-j);
			}
			switch(Receive[2])
			{
				case 'P': 
					M3508[0].PID.Kp=Data/100;
					M3508[1].PID.Kp=Data/100;
				  PID_Buffer[0]=Data;
					break;
				case 'I':
					M3508[0].PID.Ki=Data/100;
				  M3508[1].PID.Ki=Data/100;
				  PID_Buffer[1]=Data;
					break;
				case 'D':
					M3508[0].PID.Kd=Data/100;
				  M3508[1].PID.Kd=Data/100;
				  PID_Buffer[2]=Data;
					break;
			}
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)PID_Buffer,sizeof(PID_Buffer));
		}
		Flag_PID=0;
		i=0;
		j=0;
		Data=0;
		memset(Receive,0,sizeof(u8)*50);//数组清零
	}
} 

