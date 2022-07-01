#include "exit.h"
#include "stm32f10x_exti.h"	 // Keil::Device:StdPeriph Drivers:EXTI
#include "misc.h"			 // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_usart.h" // Keil::Device:StdPeriph Drivers:USART

// gpio->exit->nvic->cpu

void NVIC_Config(void) //���� NVIC �ж����ȼ�
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // 4RRE    0 SUB ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}
