/**************************************************************************
作者：栋次大次
没有特别幸运，请先特别努力
**************************************************************************/

#ifndef __MOTOR_CONTROL__
#define __MOTOR_CONTROL__
#include "sys.h"
#include <math.h>
#include "can.h"

struct PID_T{
	double Kp;
	double Ki;
	double Kd;
	double Last_Error;
	double Error_Sum;
	// 电机目标速度
	int32_t Goal_Speed;
};
struct M3508_T{
	// 机械角度
	int32_t Angle;
	// 电机速度
	int32_t Speed;
	// 电机力矩
	int32_t Moment;
	// 原始速度
	u8 Original_Data[8];
	// 电机控制电流
	int16_t Control_Current;
	// 电机停止开启
	u8 Stop_On;
	// 电机停止标志
	u8 Stop_Flag;
	// 电流限幅
	int16_t Current_Limit;
	// 电机路程:由角度乘以系数获得
	float Round;
	float Motor_Length;
	// 电机上一次角度
	int32_t Last_Angle;
	// PID
	struct PID_T PID;
};
extern struct M3508_T M3508[6];

extern void CAN_Send_Control_Value(void);//发送控制消息
extern void Data_Convert(u8 Motor_ID); //数据转化
extern void Motor_Speed_Control(int32_t Goal_Speed, u8 Motor_ID); //PID控制
extern void Control_Initialize(void); //电机结构体初始化
extern void Motor_Length_Calc(void);  //电机路程计算
extern u8 Motor_Position_Control(float Goal_Position, int16_t Speed);  //电机位置控制
extern void Motor_Length_Calc_2(void); //
extern u8 Motor_Protect(void);  //电机保护
#endif


