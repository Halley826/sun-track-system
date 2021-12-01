#include "usart.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stdio.h"
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stdio.h"
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
extern char arr[];
void USART1_Config(void)
{
	
GPIO_InitTypeDef GPIO_InitStructure ;
	USART_InitTypeDef USART_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

USART_InitStructure.USART_BaudRate=115200;
USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART1,&USART_InitStructure);
	//USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//交代USART用DMA传送
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//中断没有开启！！！
USART_Cmd(USART1,ENABLE);
}

int fputc(int ch,FILE *f)
{
	while (!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
USART_SendData(USART1,(unsigned char) ch);
	//while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	return (ch);

}




void DMA_Config ()
{
	
DMA_InitTypeDef DMA_InitSructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  DMA_InitSructure.DMA_BufferSize=10;
	DMA_InitSructure.DMA_DIR=DMA_DIR_PeripheralDST;
	DMA_InitSructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitSructure.DMA_MemoryBaseAddr=(uint32_t)arr;
	DMA_InitSructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitSructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitSructure.DMA_Mode=DMA_Mode_Normal;
	DMA_InitSructure.DMA_PeripheralBaseAddr=(uint32_t)USART1->DR;
  DMA_InitSructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitSructure.DMA_PeripheralInc=DMA_MemoryInc_Enable;
	DMA_InitSructure.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel5,&DMA_InitSructure);
	DMA_Cmd(DMA1_Channel5,ENABLE);

}



void Usart_SendString(USART_TypeDef* USARTx,char *str)

{

while(*str)

{

 while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE)) {}; //判断是否可以发送

      USART_SendData(USARTx,*str);

      while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)){}; //判断是否发送完成，此句必须有，否则会造成只发送最后一个字符（覆盖）

 str++;           

  }

}





