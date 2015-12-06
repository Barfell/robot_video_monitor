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


uint8_t key;                //����
u16 adc0,adc1,adc2,adc3;
int temp0,temp1,temp2,temp3;
void Key_Function(void);

//24L01
u8 status;	//�����жϽ���/����״̬
u8 txbuf[1];	 //���ͻ���
u8 rxbuf[4];			 //���ջ���
int i=0;

int main(void)
 {	
	 
	 /*--��ʱ������ʼ��--*/
		 delay_init();
	 
	 /*--�жϳ�ʼ��--*/
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		 
	 /*--���ڳ�ʼ��--*/
		uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	 
	 /*SPI 24l01��ʼ��*/
	 SPI_NRF_Init();
	 
	 /*���NRFģ����MCU������*/
   status = NRF_Check(); 
	 
	 while(status  != SUCCESS)
	 {
	 printf("\r\n     NRF��MCU����ʧ�ܣ������¼����ߣ�\r\n");

	 }
	 
	 /*---������ʼ��---*/
	  Key_init();
	 
	 /*--led��ʼ��---*/
		LED_Init();
	 
	 /*--OLED��ʼ��---*/
	  OLED_Init();
	 
	 /*--���PWM��ʼ��--*/
   PWM_Init(7199, 0);          //PWMƵ��10K������Ƶ
	 
	 /*--�����ʼ��--*/
	 DC_Motor_Init();
	 
	 /*--������ư�����ʼ��--*/
   Dianji_Control_Key_Init();
	 
	 /*---�����ʼ��---*/
	 TIM4_PWM_Init();           //PWMƵ��=72000000/((199+1)*(7199+1))=50hz  (  20ms )
	 
	 /*--������ư�����ʼ��--*/
    Motor_Contrl_Key_Init();

	 /*---��ʱ����ʼ��---*/
   TIM3_Int_Init(7199,99);  //��ʱ���жϳ�ʼ��  10ms 
	 
	 /*--ADC��ʼ��---*/
     	Adc_Init();		
			
//		LCD_P6x8Str(0,3,"com");
//    LCD_P6x8Str(0+24+18+18+24,4,"on");
		

	while(1)
	{
		
//	  printf("\r\n ������ ������Ӧ����ģʽ\r\n"); 
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
					
		   /*��ʼ��������*/	
       status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			  printf("ǰǰǰǰǰ %d",*txbuf);
        
		}
		else if(temp0>1)
		{
//		    DC_Motor_back(6000);
				txbuf[0]=2;
					
		   /*��ʼ��������*/	
        status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			  printf("������ %d",*txbuf);

		}
		else
    {  
			LCD_P6X8Num(0+16,0,temp0);
		}
		
	if(temp1<1)
		{
//			   DC_Motor_Left(1000);
			   txbuf[0]=3;
					
		   /*��ʼ��������*/	
       status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
				 printf("���������� %d",*txbuf);
			  
		}
		else if(temp1>1)
		{
//		     DC_Motor_Right(1000);
			   txbuf[0]=4;
					
		    /*��ʼ��������*/	
        status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			   printf("������������ %d",*txbuf);
		} 
		else
    {  
			LCD_P6X8Num(0+17,0,temp1);
		}
		
	if(temp2<1)
		{
//			 Motor_Left();
			 txbuf[0]=5;
			 		
		 /*��ʼ��������*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			 printf("1_Duoji_���������� %d",*txbuf);
		}
		else if(temp2>1)
		{
//		   Motor_Right();
			 txbuf[0]=6;
					
		 /*��ʼ��������*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			 printf("1_Duoji_�������� %d",*txbuf);
		}
		else
    {  
			LCD_P6X8Num(0+18,0,temp2);
		}
			
		if(temp3>1)
		{
//			Motor_Up();	
			txbuf[0]=7;
					
		 /*��ʼ��������*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			printf("2_duoji_�������� %d",*txbuf);
		}
		else if(temp3<1)
		{
//		  Motor_Down();
			txbuf[0]=8; 
					
		 /*��ʼ��������*/	
    status = NRF_Tx_Dat(txbuf);
			txbuf[0]=0;
			printf("2_duoji_�������� %d",*txbuf);
		}
		else
    {  
			LCD_P6X8Num(0+19,0,temp3);
		}

		
		/*�жϷ���״̬*/
//    switch(status)
//    {
//      case MAX_RT:
//        printf("\r\n ������ û���յ�Ӧ���źţ����ʹ��������޶�ֵ������ʧ�ܡ� \r\n");
//      break;

//      case ERROR:
//        printf("\r\n δ֪ԭ���·���ʧ�ܡ� \r\n");
//      break;

//      case TX_DS:
//        printf("\r\n ������ ���յ� �ӻ��� ��Ӧ���źţ����ͳɹ��� \r\n");	 		
//      break;  								
//    }	

//  // Dianji_Action();
  // Duoji_Action();
	}
	
 }

 
//��������ѡ��
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
