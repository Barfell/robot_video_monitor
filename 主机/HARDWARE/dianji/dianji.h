#ifndef __DIANJI_H
#define __DIANJI_H 
#include "sys.h"

extern int Motor1,Motor2;                //电机PWM变量

//INA
#define INA1 PCout(0)
#define INA2 PCout(1)

//INB
#define INB2 PCout(2)
#define INB1 PCout(3)

#define STBY PCout(8)


//Speed
#define Speed_1 50
#define Speed_2 100
#define Speed_3 150
#define Speed_4 200
#define Speed_5 250
#define Speed_6 300
#define Speed_7 350
#define Speed_8 400
#define Speed_9 450
#define Speed_10 500
#define Speed_11 550
#define Speed_12 600
#define Speed_13 650
#define Speed_14 700
#define Speed_15 750
#define Speed_16 800


void DC_Motor_Init(void);

void DC_Motor_forward(u16 Pwm_Val);

void DC_Motor_back(u16 Pwm_Val);

void DC_Motor_Left(u16 Pwm_Val);
	
void DC_Motor_Right(u16 Pwm_Val);
#endif
