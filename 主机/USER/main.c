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
#include "bsp_spi_nrf.h"
#include "stm32f10x_spi.h"


uint8_t key;                //按键
u16 adc0,adc1,adc2,adc3;
int temp0,temp1,temp2,temp3;
void Key_Function(void);

//24L01
u8 status;	//用于判断接收/发送状态
u8 txbuf[1];	 //发送缓冲
u8 rxbuf[4];			 //接收缓冲
int i=0;

int main(void)
 {	
	 
	 /*--延时函数初始化--*/
		 delay_init();
	 
	 /*--中断初始化--*/
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		 
	 /*--串口初始化--*/
		uart_init(115200);	 //串口初始化为115200
	 
	 /*SPI 24l01初始化*/
	 SPI_NRF_Init();
	 
	 /*检测NRF模块与MCU的连接*/
   status = NRF_Check(); 
	 
	 while(status  != SUCCESS)
	 {
	 printf("\r\n     NRF与MCU连接失败，请重新检查接线！\r\n");

	 }
	 
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
		
//	  printf("\r\n 主机端 进入自应答发送模式\r\n"); 
    NRF_TX_Mode();
		
    adc0=Get_Adc_Average(ADC_Channel_4,3);
		temp0=(int)adc0*(3.3/4096);

		adc1=Get_Adc_Average(ADC_Channel_5,3);
		temp1=(int)adc1*(3.3/4096);

		adc2=Get_Adc_Average(ADC_Channel_6,3);
		temp2=(int)adc2*(3.3/4096);
		
   	adc3=Get_Adc_Average(ADC_Channel_7,3);
		temp3=(int)adc3*(3.3/4096);
		
		if(temp0<1)
		{
//				DC_Motor_forward(6000);
			  txbuf[0]=1;
					
		   /*开始发送数据*/	
       status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			  printf("前前前前前 %d",*txbuf);
        
		}
		else if(temp0>1)
		{
//		    DC_Motor_back(6000);
				txbuf[0]=2;
					
		   /*开始发送数据*/	
        status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			  printf("后后后后后 %d",*txbuf);

		}
		else
    {  
			LCD_P6X8Num(0+16,0,temp0);
		}
		
	if(temp1<1)
		{
//			   DC_Motor_Left(1000);
			   txbuf[0]=3;
					
		   /*开始发送数据*/	
       status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
				 printf("左左左左左 %d",*txbuf);
			  
		}
		else if(temp1>1)
		{
//		     DC_Motor_Right(1000);
			   txbuf[0]=4;
					
		    /*开始发送数据*/	
        status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			   printf("右右右右右右 %d",*txbuf);
		} 
		else
    {  
			LCD_P6X8Num(0+17,0,temp1);
		}
		
	if(temp2<1)
		{
//			 Motor_Left();
			 txbuf[0]=5;
			 		
		 /*开始发送数据*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			 printf("1_Duoji_左左左左左 %d",*txbuf);
		}
		else if(temp2>1)
		{
//		   Motor_Right();
			 txbuf[0]=6;
					
		 /*开始发送数据*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			 printf("1_Duoji_右右右右 %d",*txbuf);
		}
		else
    {  
			LCD_P6X8Num(0+18,0,temp2);
		}
			
		if(temp3>1)
		{
//			Motor_Up();	
			txbuf[0]=7;
					
		 /*开始发送数据*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			printf("2_duoji_上上上上 %d",*txbuf);
		}
		else if(temp3<1)
		{
//		  Motor_Down();
			txbuf[0]=8; 
					
		 /*开始发送数据*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			printf("2_duoji_下下下下 %d",*txbuf);
		}
		else
    {  
			LCD_P6X8Num(0+19,0,temp3);
		}

		
		/*判断发送状态*/
//    switch(status)
//    {
//      case MAX_RT:
//        printf("\r\n 主机端 没接收到应答信号，发送次数超过限定值，发送失败。 \r\n");
//      break;

//      case ERROR:
//        printf("\r\n 未知原因导致发送失败。 \r\n");
//      break;

//      case TX_DS:
//        printf("\r\n 主机端 接收到 从机端 的应答信号，发送成功！ \r\n");	 		
//      break;  								
//    }	

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
