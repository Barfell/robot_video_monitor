#include "sys.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "usart.h"
#include "dianji.h"
#include "key.h"
#include "PWM.h"
#include "timer.h"
#include "duoji.h"
#include "led.h"
#include "control.h"
#include "OLED.H"
#include "adc.h"

uint8_t key;                //按键
u16 adc0,adc1,adc2,adc3;
int temp0,temp1,temp2,temp3;
void Key_Function(void);


int main(void)
 {	
	  /*--延时函数初始化--*/
		 delay_init();
	 
	 /*--中断初始化--*/
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		 
	 /*--串口初始化--*/
		uart_init(9600);	 //串口初始化为9600
	 
	 
	 /*---按键初始化---*/
	  Key_init();
	 
	 	/*--led初始化---*/
		LED_Init();
	 
	 /*--OLED初始化---*/
	   OLED_Init();
	 
	 /*--电机PWM初始化--*/
   PWM_Init(7199, 0);          //PWM频率10K，不分频
	 
	 /*--电机初始化--*/
	 DC_Motor_Init();
	 
	 /*--电机控制按键初始化--*/
   Dianji_Control_Key_Init();
	 
	 /*---舵机初始化---*/
		TIM4_PWM_Init();           //PWM频率=72000000/((199+1)*(7199+1))=50hz  (  20ms )
	 
	 /*--舵机控制按键初始化--*/
    Motor_Contrl_Key_Init();

	 /*---定时器初始化---*/
   TIM3_Int_Init(7199,99);  //定时器中断初始化  10ms 
	 
	 /*--ADC初始化---*/
     	Adc_Init();		
			
//		LCD_P6x8Str(0,3,"com");
//    LCD_P6x8Str(0+24+18+18+24,4,"on");
		

	while(1)
	{
		//Key_Function();
    adc0=Get_Adc_Average(ADC_Channel_4,3);
		temp0=(int)adc0*(3.3/4096);
//	   LCD_P6X8Num(0+18,0,temp);
		
		adc1=Get_Adc_Average(ADC_Channel_5,3);
		temp1=(int)adc1*(3.3/4096);

		adc2=Get_Adc_Average(ADC_Channel_6,3);
		temp2=(int)adc2*(3.3/4096);
		
   	adc3=Get_Adc_Average(ADC_Channel_7,3);
		temp3=(int)adc3*(3.3/4096);
		
		if(temp0<1)
		{
				DC_Motor_forward(6000);
		}
		else if(temp0>1)
		{
		    DC_Motor_back(6000);
		}
		else
    {  
			LCD_P6X8Num(0+16,0,temp0);
		}
		
	if(temp1<1)
		{
			   DC_Motor_Left(1000);
		}
		else if(temp1>1)
		{
		     DC_Motor_Right(1000);
		} 
		else
    {  
			LCD_P6X8Num(0+17,0,temp1);
		}
		
	if(temp2<1)
		{
			 Motor_Left();
		}
		else if(temp2>1)
		{
		   Motor_Right();
		}
		else
    {  
			LCD_P6X8Num(0+18,0,temp2);
		}
			
		if(temp3>1)
		{
			Motor_Up();	
		}
		else if(temp3<1)
		{
		  Motor_Down();
		}
		else
    {  
			LCD_P6X8Num(0+19,0,temp3);
		}
		

//  // Dianji_Action();
  // Duoji_Action();

	}
	
 }

 
//按键功能选择
void Key_Function(void)
{
    key = Key_Scan(0);
    switch(key)
    {
        case Key1_Press: //
         DC_Motor_forward(1000);
				 Motor_Left();
             break;
				
        case Key2_Press: //
				DC_Motor_back(1000);
				Motor_Right();
             break;
				
        case Key3_Press:
        DC_Motor_Left(1000);	
        Motor_Up();				
             break;
				
        case Key4_Press: 
				DC_Motor_Right(1000);
				Motor_Down();
             break;
        default: break;
    }
}
