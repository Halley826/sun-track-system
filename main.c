#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "sport.h"//控制信号
#include "key.h"//追踪到达极限信号
#include "timer.h"//pwm输出
#include "light.h"//光强信号
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "usart.h"//gprs通信（与lcd通信还没有完成）
#include "stdio.h"//相关c库
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "exit.h"//中断
#include <string.h>//字符串
#include "delay.h"//延时
uint16_t temp=0;
char 	arr[]="check1\0";
char 	arro[]="start1\0";
char 	arrwc[]="windcl\0";
char 	arrsc[]="snowcl\0";//定义的字符串
char 	received[6]="";//收到的字符串
char *p=received;
char 	state_l[]="track system works properly!";
char 	state_d[]="there are something wrong with track system";
int t=0;
char flag=1;//追踪状态标志位
char Gstate=1;//追踪标志位
//char send[];
int main()
{
	
//DMA_Config ();
	NVIC_Config( );
Stop();
Sport_Init();
Key_Init();
TIM4_Int_Init();  //500ms
Light_Init();//初始化
TIM4_OC4Structure (900);//5000  PB.9   ENA34  UP&&DOWN
TIM4_OC3Structure (900);//5000  PB.8    ENA12   LEFT&&RIGHT
USART1_Config();
	printf("track system has started,instruction:\nstart1\ncheck1\nwindcl\nsnowcl\n");
	while(1){
	while(Gstate)//追踪
	{

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)//左面光强
	{
		temp++;
 Left ();
		flag=0;

	}
	Stop();
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)//右面光强
	{	temp++;
 Right ();
		flag=0;

	
	}
	Stop();

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)	//上面光强并且没有到达追踪极限
	{
	temp++;
		Up();
		flag=0;

	
} Stop();


			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)//下面光强并且没有到达极限
			{ 
					temp++;
				Down ();
				flag=0;


	}
		Stop();
flag=1;



	
}
}

}


void USART1_IRQHandler()//GPRS串口中断服务程序
{

if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
{

	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET) 
		{
			if(t==5)
			{
				*p=USART_ReceiveData(USART1);
			p=received;
		
				t=0;
				
				if(strncmp(arr,received,6)==0)//判断是不是查询状态
				{
					if(flag==1)//正常追踪
					printf("Result:\nID:0001\nRete of work:20.123w\nstate:%s",state_l);//
					else  //追踪不正常
						printf("Result:\nID:0001\nRete of work:20.134w\nstate:%s",state_d);
			delay_nms(100);
				
				}
				
			else 
				if (strncmp(arrwc,received,6)==0)//大风关闭
				{  	Gstate=0;
					
							while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
			{ 
					
				Up();
				flag=0;
	}Stop();
		
							        printf("closed\n");
				}
else 
				if (strncmp(arrsc,received,6)==0)
				{   
					Gstate=0;
					while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)
			{ 
			
				Down ();
				flag=0;
	}
			Stop();
			
						printf("closed\n");
				}
else
 	if (strncmp(arro,received,6)==0)
	
	{
		Gstate=1;
	 printf("track system has started,instruction:\nstart1\ncheck1\nwindcl\nsnowcl\n");
	
	}
       
else
	printf("non-existent!\n");
							
			}
else 
{

	*p=USART_ReceiveData(USART1);
			p++;
t++;
}
			USART_ClearFlag(USART1,USART_FLAG_RXNE);
			
	}
		
	

}

USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}





