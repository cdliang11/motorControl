/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/

#include "tim.h"


/**************************************************************************
函数功能：定时器3初始化
入口参数：arr:重装载值 , psc: 预分频值
返回  值：无
**************************************************************************/

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}


/**************************************************************************
函数功能：定时器3中断服务函数
入口参数：无
返回  值：无
**************************************************************************/

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			static u8 i=0;
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			
			//电位器的限位
//			get_pot_adc();
//			adc_angle_transform();
//			
//			if(angle[0]>233) M3508[2].PID.Goal_Speed = 0;
//			if(angle[1]>233) M3508[3].PID.Goal_Speed = 0;
//			if(angle[2]>233) M3508[4].PID.Goal_Speed = 0;
//			if(angle[3]>233) M3508[5].PID.Goal_Speed = 0;
			
			Motor_Speed_Control(M3508[0].PID.Goal_Speed, 0);
			Motor_Speed_Control(M3508[1].PID.Goal_Speed, 1);
			Motor_Speed_Control(M3508[2].PID.Goal_Speed, 2);
			Motor_Speed_Control(M3508[3].PID.Goal_Speed, 3);
			Motor_Speed_Control(M3508[4].PID.Goal_Speed, 4);
			Motor_Speed_Control(M3508[5].PID.Goal_Speed, 5);
			//printf("M1_Goal_Speed:%d\r\n",M3508[0].PID.Goal_Speed);
			//printf("M2_Goal_Speed:%d\r\n",M3508[1].PID.Goal_Speed);
			
			CAN_Send_Control_Value();
			printf("%d,%d,%d,%d\n",M3508[0].PID.Goal_Speed,M3508[0].Speed,M3508[1].PID.Goal_Speed,M3508[1].Speed);
//			if(i>9) 
//			{
//				printf("M1_Speed:%d\r\n",M3508[0].Speed);
//				printf("M1_Goal_Speed:%d\r\n",M3508[0].PID.Goal_Speed);
//				i=0;
//			}
//			else i++;
			//Motor_Info_Send();
			
//		send_can_data(angle[0],angle[1],(0x11e0>>5));
//		delay_ms(10);  //以前：3   现在：10    必须加延时，CAN通信才稳定
//		send_can_data(angle[2],angle[3],(0x12e0>>5));
		  // LED1=!LED1;
			//Motor_Info_Send();//
		}
}

