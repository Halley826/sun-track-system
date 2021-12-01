#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "sport.h"//�����ź�
#include "key.h"//׷�ٵ��Ｋ���ź�
#include "timer.h"//pwm���
#include "light.h"//��ǿ�ź�
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "usart.h"//gprsͨ�ţ���lcdͨ�Ż�û����ɣ�
#include "stdio.h"//���c��
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "exit.h"//�ж�
#include <string.h>//�ַ���
#include "delay.h"//��ʱ
uint16_t temp=0;
char 	arr[]="check1\0";
char 	arro[]="start1\0";
char 	arrwc[]="windcl\0";
char 	arrsc[]="snowcl\0";//������ַ���
char 	received[6]="";//�յ����ַ���
char *p=received;
char 	state_l[]="track system works properly!";
char 	state_d[]="there are something wrong with track system";
int t=0;
char flag=1;//׷��״̬��־λ
char Gstate=1;//׷�ٱ�־λ
//char send[];
int main()
{
	
//DMA_Config ();
	NVIC_Config( );
Stop();
Sport_Init();
Key_Init();
TIM4_Int_Init();  //500ms
Light_Init();//��ʼ��
TIM4_OC4Structure (900);//5000  PB.9   ENA34  UP&&DOWN
TIM4_OC3Structure (900);//5000  PB.8    ENA12   LEFT&&RIGHT
USART1_Config();
	printf("track system has started,instruction:\nstart1\ncheck1\nwindcl\nsnowcl\n");
	while(1){
	while(Gstate)//׷��
	{

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)//�����ǿ
	{
		temp++;
 Left ();
		flag=0;

	}
	Stop();
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)//�����ǿ
	{	temp++;
 Right ();
		flag=0;

	
	}
	Stop();

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)	//�����ǿ����û�е���׷�ټ���
	{
	temp++;
		Up();
		flag=0;

	
} Stop();


			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)//�����ǿ����û�е��Ｋ��
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


void USART1_IRQHandler()//GPRS�����жϷ������
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
				
				if(strncmp(arr,received,6)==0)//�ж��ǲ��ǲ�ѯ״̬
				{
					if(flag==1)//����׷��
					printf("Result:\nID:0001\nRete of work:20.123w\nstate:%s",state_l);//
					else  //׷�ٲ�����
						printf("Result:\nID:0001\nRete of work:20.134w\nstate:%s",state_d);
			delay_nms(100);
				
				}
				
			else 
				if (strncmp(arrwc,received,6)==0)//���ر�
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





