#include "timer.h"
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void TIM4_Int_Init()
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=5000;//all
	TIM_TimeBaseStructure.TIM_Prescaler=0x0090;//分频   0.01s 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
}

void  TIM4_OC3Structure (uint16_t part)
{
TIM_OCInitTypeDef  TIM_OCStructure;

TIM_OCStructure.TIM_OCIdleState=0;
	TIM_OCStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCNIdleState=0;
	TIM_OCStructure.TIM_OCNPolarity=0;
	TIM_OCStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputNState=0;
	TIM_OCStructure.TIM_OutputState=TIM_OutputState_Enable;
TIM_OCStructure.TIM_Pulse=part;//1250====all is 5000
TIM_OC3Init(TIM4,&TIM_OCStructure);//通道3
TIM_Cmd(TIM4, ENABLE);
}

void  TIM4_OC4Structure (uint16_t part)
{
TIM_OCInitTypeDef  TIM_OCStructure;
TIM_OCStructure.TIM_OCIdleState=0;
	TIM_OCStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCNIdleState=0;
	TIM_OCStructure.TIM_OCNPolarity=0;
	TIM_OCStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputNState=0;
	TIM_OCStructure.TIM_OutputState=TIM_OutputState_Enable;
TIM_OCStructure.TIM_Pulse=part;//====all is 5000
TIM_OC4Init(TIM4,&TIM_OCStructure);//通道4
TIM_Cmd(TIM4, ENABLE);
}



