#include "control.h"
#include "sys.h"
#include "PWM.h"
#include "dianji.h"
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "delay.h"
#include "duoji.h"
#include "timer.h"
#include "led.h"

int Dianji_Center_Flag ;
int Dianji_Forward_Back_Flag;
int Dianji_Left_Right_Flag;
//电机控制按键初始化
void Dianji_Control_Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(Dianji_RCC_CLK , ENABLE);//使能外设时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 |  GPIO_Pin_15;//GPIO
                                    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//设置为下拉输入
    GPIO_Init(Dianji_GPIO, &GPIO_InitStructure);//初始化

}
//电机动作
void Dianji_Action(void)
{
	//中间key 
//	if(1==Dianji_Center_Key_Value)
//	{
//			Dianji_Center_Flag=1;
//	}
//	else
//	{
//	    Dianji_Center_Flag=0;
//	}
	
    //前进
//	 if(1==Dianji_Forward_Back_Value) 
//	 {
//	  	LED0=!LED0;
//	  DC_Motor_forward(1000);
//; 
//	 }
	 
	 //后退
	 if(0==Dianji_Forward_Back_Value)
	 {
		LED0=!LED0;
		DC_Motor_back(1000);
	 }
	 //左转
//	 if(1==Dianji_Left_Right_Value)
//	 {
//	   DC_Motor_Left(1000);
//	 }
	 //右转
	 if(0==Dianji_Left_Right_Value)
	 {
		LED0=!LED0;
	  DC_Motor_Right(1000);
	 }
}




//舵机控制按键初始化
void Motor_Contrl_Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(Duoji_RCC_CLK , ENABLE);//使能外设时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | 
                                     GPIO_Pin_5;//GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置为上拉输入
    GPIO_Init(Duoji_GPIO, &GPIO_InitStructure);//初始化
}

//舵机动作
void Duoji_Action(void)
{
	//下舵机左转
	if(1==Motor_Left_Right_Value)
  {
		LED0=!LED0;
	 Motor_Left();
	}
	//下舵机右转
	if(0==Motor_Left_Right_Value)
	{
			LED0=!LED0;
	  Motor_Right();
	}
	
	//上舵机上转
	if(1==Motor_Up_Down_Value)
	{
			LED0=!LED0;
	  Motor_Up();
	}
	//上舵机下转
	if(0==Motor_Up_Down_Value)
	{
			LED0=!LED0;
	   Motor_Down();
	}
}

