
#include "bsp_usart.h" 

#define USART1_EN     	          1
#define USART2_EN    			        1
#define USART3_EN                 1
//#define USART3_REMAP_EN	        1		

/***************************************************************************************************
***************************************************************************************************/
//#define USART1_REMAP_EN					1
//#define USART1_TRX_EN         	1

//#ifdef USART1_EN
//#ifdef USART1_TRX_EN
//#define USART1_TRX_GPIO        	GPIOB
//#define USART1_TRX_RCC         	RCC_APB2Periph_GPIOB
//#define USART1_TRX_PIN        	GPIO_Pin_5																													
//#endif
//#endif

/***************************************************************************************************
***************************************************************************************************/

#define USART1_DR_Base    0x40013804
#define USART2_DR_Base    0x40004404
#define USART3_DR_Base    0x40004804

#define UART_TX_TRING_EN            0X0100
#define UART_TX_RUN                 0X0200
#define UART_TX_COMP                0X0400

//
#define USART1_TX_DMA_CHANNEL       DMA1_Channel4
#define USART1_RX_DMA_CHANNEL       DMA1_Channel5

#define USART2_TX_DMA_CHANNEL       DMA1_Channel7
#define USART2_RX_DMA_CHANNEL       DMA1_Channel6

#define USART3_TX_DMA_CHANNEL       DMA1_Channel2
#define USART3_RX_DMA_CHANNEL       DMA1_Channel3

//条件选择  
#ifdef USART1_EN 
u8 uart1_rx_buff[300],uart1_rx_data[300],uart1_tx_buff[300];
u16 uart1_rx_number=0,uart1_tx_number=0; 	//,uart1_rx_counter
#endif

#ifdef USART2_EN
u8 uart2SendBuff[1200],uart2SendBuffNumber=0,uart2SendingFalg=0;
u8 uart2_rx_buff[1200],uart2_rx_data[1200],uart2_tx_buff[1200];
u16 uart2_rx_number=0,uart2_tx_number=0;	//,uart2_rx_counter
#endif

#ifdef USART3_EN
u8 uart3_rx_buff[1200],uart3_rx_data[1200],uart3_tx_buff[1200];
u16 uart3_rx_number=0,uart3_tx_number=0;	//,uart3_rx_counter
#endif

/******************************************************************************* 
*******************************************************************************/ //收发控制
//DMA设置
void DMA_Configuration_USART(DMA_Channel_TypeDef* DMA_Chx,uint32_t DB,uint8_t *buff,uint32_t dir,uint32_t len)
{
  DMA_InitTypeDef     DMA_InitStructure;

  DMA_DeInit(DMA_Chx);
  DMA_InitStructure.DMA_PeripheralBaseAddr = DB;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)buff;
  DMA_InitStructure.DMA_DIR = dir; //目的
  DMA_InitStructure.DMA_BufferSize = len; //缓存长度
  
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//一个外设
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//缓存地址增加
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //字节传输
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //
  DMA_Init(DMA_Chx, &DMA_InitStructure);  //
}

void BSP_USART_DMA_Init(USART_TypeDef* USARTx, uint8_t *txBuff, uint8_t *rxBuff) // 
{
  switch (*(uint32_t*)&USARTx)
  {
    case USART1_BASE:
      DMA_Configuration_USART(USART1_TX_DMA_CHANNEL,USART1_DR_Base,txBuff,DMA_DIR_PeripheralDST,1200);
      DMA_Configuration_USART(USART1_RX_DMA_CHANNEL,USART1_DR_Base,rxBuff,DMA_DIR_PeripheralSRC,1200);
      break;
    case USART2_BASE:
      DMA_Configuration_USART(USART2_TX_DMA_CHANNEL,USART2_DR_Base,txBuff,DMA_DIR_PeripheralDST,1200);
      DMA_Configuration_USART(USART2_RX_DMA_CHANNEL,USART2_DR_Base,rxBuff,DMA_DIR_PeripheralSRC,1200);
      break;
    case USART3_BASE:
      DMA_Configuration_USART(USART3_TX_DMA_CHANNEL,USART3_DR_Base,txBuff,DMA_DIR_PeripheralDST,1200);
      DMA_Configuration_USART(USART3_RX_DMA_CHANNEL,USART3_DR_Base,rxBuff,DMA_DIR_PeripheralSRC,1200);
      break;
  }
  
  USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);
  USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);
  
  switch (*(uint32_t*)&USARTx)
  {
    case USART1_BASE:
      DMA_Cmd(USART1_TX_DMA_CHANNEL, ENABLE);
      DMA_Cmd(USART1_RX_DMA_CHANNEL, ENABLE);
      break;
    case USART2_BASE:
      DMA_Cmd(USART2_TX_DMA_CHANNEL, ENABLE);
      DMA_Cmd(USART2_RX_DMA_CHANNEL, ENABLE);
      break;
    case USART3_BASE:
      DMA_Cmd(USART3_TX_DMA_CHANNEL, ENABLE);
      DMA_Cmd(USART3_RX_DMA_CHANNEL, ENABLE);
      break;
  }      
}

void BSP_USART_Init(USART_TypeDef* USARTx, uint32_t baud, uint16_t Parity) //, FunctionalState DMAState
{
  USART_InitTypeDef   USART_InitStruct;

  switch (*(uint32_t*)&USARTx)
  {
    case USART1_BASE:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); //USART1 时钟使能
  		break;
    case USART2_BASE:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); //USART2 时钟使能
  		break;
    case USART3_BASE:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); //USART3 时钟使能
  		break;
  }

  USART_StructInit(&USART_InitStruct); //结构体参数初始化，默认值9600
  USART_InitStruct.USART_BaudRate = baud;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = Parity;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl =USART_HardwareFlowControl_None; 
  USART_Init(USARTx , &USART_InitStruct); //USART1初始化
  
  
  //USART_Cmd(USARTx , ENABLE); //USART 使能
} 

/*************************************************************************************************** 
***************************************************************************************************/  
void DMA1_irq( void )
{
  
}

void DMA1_Channel2_IRQHandler(void)
{
  
}

void DMA1_Channel3_IRQHandler(void)
{
  
}

void DMA1_Channel4_IRQHandler(void)
{
  
}

void DMA1_Channel5_IRQHandler(void)
{
  
}

void DMA1_Channel6_IRQHandler(void)
{
  
}

void DMA1_Channel7_IRQHandler(void)
{
  
}

/*************************************************************************************************** 
***************************************************************************************************/  
void USART1_IRQHandler(void)
{
#ifdef USART1_EN 
	uint32_t i=0;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
	{
		//接收空闲中断
		//禁止再次接受
		DMA_Cmd(USART1_RX_DMA_CHANNEL, DISABLE);

		uart1_rx_number = 1200-USART1_RX_DMA_CHANNEL->CNDTR;
		for(i=0;i<uart1_rx_number;i++)
		{			 
			uart1_rx_data[i] = uart1_rx_buff[i];
		}																										 

		//DMA_ClearFlag(DMA1_FLAG_GL4|DMA1_FLAG_TC4|DMA1_FLAG_HT4|DMA1_FLAG_TE4);
		USART1_RX_DMA_CHANNEL->CNDTR = 1200;		
		DMA_Cmd(USART1_RX_DMA_CHANNEL, ENABLE);
		
		//清除标志
		i = USART1->SR;
		i = USART1->DR;
	}		

	if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
	{
		USART1->SR &= ~0x00000040;
		#ifdef USART1_TRX_EN
		USART1_TRX_GPIO->BRR |= (u32)USART1_TRX_PIN;	
		#endif
	}		
#endif	
}

void USART2_IRQHandler(void)
{
#ifdef USART2_EN 
	u8 cTmp=0,x=0;
  uint32_t i=0;
	
	if(USART_GetITStatus(USART2, USART_IT_IDLE) == SET)
	{
		//接收空闲中断
		//禁止再次接受
		DMA_Cmd(USART2_RX_DMA_CHANNEL, DISABLE);
		
		uart2_rx_number = 1200-USART2_RX_DMA_CHANNEL->CNDTR;
		for(i=0;i<uart2_rx_number;i++)
		{			 
			uart2_rx_data[i] = uart2_rx_buff[i];
		}																										 

		USART2_RX_DMA_CHANNEL->CNDTR = 1200;		
		DMA_Cmd(USART2_RX_DMA_CHANNEL, ENABLE);
		
		//清除标志
		i = USART2->SR;
		i = USART2->DR;
    
    x = 1;
	}		
  else if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
  {
    cTmp = USART_ReceiveData(USART2);
    
    USART_SendData(USART3, cTmp);
    
  }
  
	if(USART_GetITStatus(USART2, USART_IT_TC) == SET)
	{
		USART2->SR &= ~0x00000040;
		//清除标志
    
    if(uart2SendingFalg==2)
    {
      uart2SendingFalg = 3;
    }  
    else if(uart2SendBuffNumber)
    {  
      for(i=0;i<uart2SendBuffNumber;i++)
      {
        uart2_tx_buff[i] = uart2SendBuff[i]; 	
      }		
           
      DMA_Cmd(USART2_TX_DMA_CHANNEL, DISABLE);
      DMA_ClearFlag(DMA1_FLAG_GL7|DMA1_FLAG_TC7|DMA1_FLAG_HT7|DMA1_FLAG_TE7);
      USART2_TX_DMA_CHANNEL->CNDTR = uart2SendBuffNumber;		
      DMA_Cmd(USART2_TX_DMA_CHANNEL, ENABLE);
      uart2SendBuffNumber = 0;
    } 
    else
    {
      uart2SendingFalg = 0;
    }  
	}		
  
  if(x!=1) 
  {  
//    while(1);
  }  
#endif			
}

void USART3_IRQHandler(void)
{
#ifdef USART3_EN 
//  u8 cTmp=0,x=0;
  
	uint32_t i=0;
	if(USART_GetITStatus(USART3, USART_IT_TXE) == SET)
  {
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    /*
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
    {   
      // Write one byte to the transmit data register 
      USART_SendData(USART1, TxBuffer1[TxCounter1++]);

      if(TxCounter1 == NbrOfDataToTransfer1)
      {
        // Disable the USART1 Transmit interrupt  
        USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      }    
    }  
   */
  }  
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) == SET)
	{
				
		uart3_rx_number = 1200-USART3_RX_DMA_CHANNEL->CNDTR;
    if((uart3_rx_buff[0]!=0xAA) || ((uart3_rx_buff[uart3_rx_number-2]==0xc3) && (uart3_rx_buff[uart3_rx_number-1]==0x3C)) || (uart3_rx_number>1050))
		{
		//禁止再次接受
      DMA_Cmd(USART3_RX_DMA_CHANNEL, DISABLE);
      for(i=0;i<uart3_rx_number;i++)
      {			 
        uart3_rx_data[i] = uart3_rx_buff[i];
      }																										 

		//接收空闲中断
      USART3_RX_DMA_CHANNEL->CNDTR = 1200;		
      DMA_Cmd(USART3_RX_DMA_CHANNEL, ENABLE);
		}
    else
    {
      uart3_rx_number = 0;
    }  
    
    //清除标志
    i = USART3->SR;
		i = USART3->DR;
    
	}		
  else if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
  {
//    cTmp = USART_ReceiveData(USART3); 
    //USART_SendData(USART2, cTmp);    CC 33 C3 3C  
  }
  
	if(USART_GetITStatus(USART3, USART_IT_TC) == SET)
	{
		//USART_ClearFlag(USART3,USART_FLAG_RXNE);
    USART3->SR &= ~0x00000040;
    
		//清除标志
		i = USART3->SR;
		i = USART3->DR;
	}		
  
//  if(x!=1) 
//  {  
//    while(1);
//  }  
#endif	
}

void NVIC_Configuration_Usart(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
 
/*************************************************************************************************** 
***************************************************************************************************/  
void USART1_Init(void)
{
  NVIC_Configuration_Usart();       
  
#ifdef USART1_EN
	GPIO_InitTypeDef GPIO_InitStruct;

	#ifdef USART1_REMAP_EN		
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
	#else					
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
	#endif
	
	///////////////////////////////////////////////////////////////////
  #ifdef USART1_TRX_EN
	RCC_APB2PeriphClockCmd(USART1_TRX_RCC, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = USART1_TRX_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART1_TRX_GPIO , &GPIO_InitStruct);
	#endif
	
	///////////////////////////////////////////////////////////////////
	BSP_USART_Init(USART1, 19200, USART_Parity_No);//, ENABLE
	
  //if(DMAState==ENABLE)       
	BSP_USART_DMA_Init(USART1,uart1_tx_buff,uart1_rx_buff);

	//中断 
	///////////////////////////////////////////////////////////////////  
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	//NVIC_Configuration_Usart();       	
	
	USART_Cmd(USART1 , ENABLE); //USART1 使能
				
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void USART2_Init(u32 mbaud)
{
#ifdef USART2_EN
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);

	BSP_USART_Init(USART2, mbaud, USART_Parity_No);//, ENABLE
	
  //if(DMAState==ENABLE)       
	BSP_USART_DMA_Init(USART2,uart2_tx_buff,uart2_rx_buff);
     
	//中断 
	///////////////////////////////////////////////////////////////////  
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
  
  //DMA_ITConfig(USART2_RX_DMA_CHANNEL,DMA_IT_TC,ENABLE);
  //DMA_ITConfig(USART2_TX_DMA_CHANNEL,DMA_IT_TC,ENABLE);
	//NVIC_Configuration_Usart();       	
	
	USART_Cmd(USART2 , ENABLE);  
				
#endif
}

/////////////////////////////////////////////////////////////	//////////////////////////////////////
void USART3_Init(void)
{
#ifdef USART3_EN
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef USART3_REMAP_EN		
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
	#else					
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
	#endif
	
	BSP_USART_Init(USART3, 115200, USART_Parity_No);//, ENABLE
	
  //if(DMAState==ENABLE)       
	BSP_USART_DMA_Init(USART3,uart3_tx_buff,uart3_rx_buff);

	//中断 
	///////////////////////////////////////////////////////////////////  
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);
  //USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
  //DMA_ITConfig(USART3_RX_DMA_CHANNEL,DMA_IT_TC,ENABLE);
  //DMA_ITConfig(USART3_TX_DMA_CHANNEL,DMA_IT_TC,ENABLE);
	//NVIC_Configuration_Usart();       	
	
	USART_Cmd(USART3 , ENABLE);  
				
#endif
}

/*************************************************************************************************** 
***************************************************************************************************/  
void BSP_USART_Send(USART_TypeDef* USARTx,uint8_t *buff,uint32_t len)
{
	u32 i,j;
	
  switch (*(uint32_t*)&USARTx)
  {
    case USART1_BASE:
			#ifdef USART1_EN 
				for(i=0;i<len;i++)
				{
					uart1_tx_buff[i] = buff[i]; 	
				}		
				
				#ifdef USART1_TRX_EN
				USART1_TRX_GPIO->BSRR |= (u32)USART1_TRX_PIN;	
				#endif	
				USART1->SR &= ~0x00000040;
				
				DMA_Cmd(USART1_TX_DMA_CHANNEL, DISABLE);
				DMA_ClearFlag(DMA1_FLAG_GL4|DMA1_FLAG_TC4|DMA1_FLAG_HT4|DMA1_FLAG_TE4);
				USART1_TX_DMA_CHANNEL->CNDTR = len;		
				DMA_Cmd(USART1_TX_DMA_CHANNEL, ENABLE);
			#endif
			break;	
    case USART2_BASE:
			#ifdef USART2_EN 
        if(uart2SendingFalg==0)
        {  
          for(i=0;i<len;i++)
          {
            uart2_tx_buff[i] = buff[i]; 	
          }		

          USART2->SR &= ~0x00000040;
				 
          DMA_Cmd(USART2_TX_DMA_CHANNEL, DISABLE);
          DMA_ClearFlag(DMA1_FLAG_GL7|DMA1_FLAG_TC7|DMA1_FLAG_HT7|DMA1_FLAG_TE7);
          USART2_TX_DMA_CHANNEL->CNDTR = len;		
          DMA_Cmd(USART2_TX_DMA_CHANNEL, ENABLE);
          
          uart2SendingFalg = 1;
        }   
        else
        {
          uart2SendingFalg = 2;
          
          j = uart2SendBuffNumber;
          for(i=0;i<len;i++)        
          {
            uart2SendBuff[j+i]  = buff[i]; 	
            uart2SendBuffNumber++;
          }		
          
          if(uart2SendingFalg==3)
          {
            for(i=0;i<uart2SendBuffNumber;i++)
            {
              uart2_tx_buff[i] = uart2SendBuff[i]; 	
            }		
            
            USART2->SR &= ~0x00000040;
           
            DMA_Cmd(USART2_TX_DMA_CHANNEL, DISABLE);
            DMA_ClearFlag(DMA1_FLAG_GL7|DMA1_FLAG_TC7|DMA1_FLAG_HT7|DMA1_FLAG_TE7);
            USART2_TX_DMA_CHANNEL->CNDTR = uart2SendBuffNumber;		
            DMA_Cmd(USART2_TX_DMA_CHANNEL, ENABLE);
            
            uart2SendBuffNumber = 0;
            
            uart2SendingFalg = 1;
          } 
          else
          {
            uart2SendingFalg = 1;
          }  
        }  
			#endif
			break;	
    case USART3_BASE:
			#ifdef USART3_EN 
				for(i=0;i<len;i++)
				{
					uart3_tx_buff[i] = buff[i]; 	
				}		
				
				//USART3_TRX_GPIO->BSRR |= (u32)USART3_TRX_PIN;	
					
				USART3->SR &= ~0x00000040;
				 
				DMA_Cmd(USART3_TX_DMA_CHANNEL, DISABLE);
				DMA_ClearFlag(DMA1_FLAG_GL2|DMA1_FLAG_TC2|DMA1_FLAG_HT2|DMA1_FLAG_TE2);
				USART3_TX_DMA_CHANNEL->CNDTR = len;		
				DMA_Cmd(USART3_TX_DMA_CHANNEL, ENABLE);
			#endif
			break;	
	}			
}

/*************************************************************************************************** 
***************************************************************************************************/  
uint32_t BSP_USART_Receive(USART_TypeDef* USARTx,uint8_t *buff,uint32_t mlen)
{
	uint8_t *pstr;
	uint32_t i=0,len=0;
	
  switch (*(uint32_t*)&USARTx)
  {
    case USART1_BASE:
			#ifdef USART1_EN 
			pstr = uart1_rx_data;					
			len = uart1_rx_number;
			uart1_rx_number = 0;  
			#endif
			break;			
    case USART2_BASE: 
			#ifdef USART2_EN 
			pstr = uart2_rx_data;			
			len = uart2_rx_number;
			uart2_rx_number = 0;  
			#endif
			break;			
    case USART3_BASE:
			#ifdef USART3_EN 
			pstr = uart3_rx_data;					
			len = uart3_rx_number; 
			uart3_rx_number = 0;  
			#endif
			break;			
	}	   
	
	if(mlen && (mlen<len))
	{
		len = mlen;
	}
	
	for(i=0;i<len;i++)
	{
		buff[i] = pstr[i];
	}		
			
	return(len);
}

/*************************************************************************************************** 
***************************************************************************************************/
