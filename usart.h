#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
void USART1_Config(void);
void DMA_Config (void);
void Usart_SendString(USART_TypeDef* USARTx,char *str);
