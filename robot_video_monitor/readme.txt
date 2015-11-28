#开发日志

##2015.11.14

#############################按键
PC.4
PC.5
PC.6
PC.7



##############################电机

//INA
#define INA1 PCout(0)
#define INA2 PCout(1)

//INB
#define INB2 PCout(2)
#define INB1 PCout(3)

#define STBY PCout(8)

//电机PWM
定时器2 
PA.2 
PA.3

###############################LED 
PB.0

################################舵机
pwm

PC.8
PC.9



##2015.11.17
#############################按键
PC.4
PC.5
PC.6
PC.7



##############################电机

//INA
#define INA1 PCout(0)
#define INA2 PCout(1)

//INB
#define INB2 PCout(2)
#define INB1 PCout(3)

#define STBY PCout(8)

//电机PWM
定时器2 
PA.2 
PA.3

###############################LED 
PB.0

################################舵机
pwm
定时器4
PB.8  下舵机
PB.9  上舵机


##2015.11.15
#############################按键
PC.4
PC.5
PC.6
PC.7



##############################电机

//INA
#define INA1 PCout(0)
#define INA2 PCout(1)

//INB
#define INB2 PCout(2)
#define INB1 PCout(3)

#define STBY PCout(8)

//电机PWM
定时器2 
PA.2 
PA.3

###############################LED 
PB.0

################################舵机
pwm
定时器4
PB.8  下舵机
PB.9  上舵机


/**************ADC***********/
//PF6.7.8.9 作为模拟通道输入引脚

PF6 电机前后
PF7 电机左右
PF8 下舵机左右
PF.9 上舵机左右

2015.11.18

/********从机NRF24L01************/
PB14 SPI2_MOS0
PB15 SPI2_MOSI

/*****************/