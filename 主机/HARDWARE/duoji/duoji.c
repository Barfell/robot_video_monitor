#include "duoji.h"
#include "timer.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "sys.h"
#include "delay.h"


//舵机左转

void Motor_Left(void)
{
	  Motor_Pulse1+=1;
	  if(Motor_Pulse1>=20)
		{
			Motor_Pulse1=20;
		}
		delay_ms(1000);
}

//舵机右转
void Motor_Right(void)
{
	  Motor_Pulse1-=1;
	  if(Motor_Pulse1<=5)
		{
			Motor_Pulse1=5;
		}
		delay_ms(1000);
}


//舵机上转
void Motor_Up(void)
{
	  Motor_Pulse2-=1;
	  if(Motor_Pulse2<=5)
		{
			Motor_Pulse2=5;
		}
		delay_ms(1000);
}



//舵机下转

void Motor_Down(void)
{
	  Motor_Pulse2+=1;
	  if(Motor_Pulse2>=20)
		{
			Motor_Pulse2=20;
		}
		delay_ms(1000);
}

