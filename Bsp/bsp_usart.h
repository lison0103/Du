
#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h" 

void BSP_USART_Init(USART_TypeDef* USARTx, uint32_t baud, uint16_t Parity); //, FunctionalState DMAState

void USART1_Init(void);
void USART2_Init(u32 mbaud);
void USART3_Init(void);

void BSP_USART_Send(USART_TypeDef* USARTx,uint8_t *buff,uint32_t len);
uint32_t BSP_USART_Receive(USART_TypeDef* USARTx,uint8_t *buff,uint32_t mlen);

#endif 

