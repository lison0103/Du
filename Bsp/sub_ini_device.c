#include "main_include.h"

#include "stm32f10x_rcc.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"
#include "misc.h"
#include "stm32f10x_dma.h"
 
#include "uart1.h"
#include "uart2.h"

#include "LCD12864.h"
#include "led.h"

GPIO_InitTypeDef    GPIO_InitStruct;
USART_InitTypeDef   USART_InitStruct;

//#define USART1_DR_Base 0x40013804

/*******************************************************************************
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
 
#ifdef  VECT_TAB_RAM
    // Set the Vector Table base location at 0x20000000
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); //Ram�е���
#else  /* VECT_TAB_FLASH  */
    // Set the Vector Table base location at 0x08000000
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); //Flash�е���
#endif
 
  //����NVIC���ȼ�����ΪGroup2��0-3��ռʽ���ȼ���0-3����Ӧʽ���ȼ�
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
  NVIC_Init(&NVIC_InitStructure);   
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
*******************************************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStatus;
  
  SystemInit();

  RCC_DeInit(); //ʱ�ӳ�ʼ��
  RCC_HSEConfig(RCC_HSE_ON); //���ⲿʱ��
  HSEStatus = RCC_WaitForHSEStartUp(); //��ȡ�ⲿʱ��״̬
  if(HSEStatus == SUCCESS) //�����ɹ�
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Ԥȡָ����ʹ�� 
    FLASH_SetLatency(FLASH_Latency_2); //���ô�����ʱ�������Ƕ�������
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHB��ʱ��HCLK 	  
    RCC_PCLK2Config(RCC_HCLK_Div1); //��������ѡ�õľ���HCLK	
    RCC_PCLK1Config(RCC_HCLK_Div2);	  //���������õ���HCLK��2��Ƶ
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//ѡ��PLL������ʱ���Լ����ķ�Ƶϵ��	
    RCC_PLLCmd(ENABLE);	//ʹ��PLL���໷
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
      ;
    }			 //�ȴ�LL���໷�ȶ�
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//ѡ��PLL���໷Ϊϵͳʱ��	
    while(RCC_GetSYSCLKSource() != 0x08) //���������ϵͳʱ���ǲ��������໷�ṩ��
    {
      ;
    }
  }
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE); //for dma  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//Ϊ�ⲿ�ж�

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); //USART1 ʱ��ʹ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); //USART2 ʱ��ʹ��

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  
                         |RCC_APB2Periph_GPIOB   
                         |RCC_APB2Periph_GPIOC  
                         |RCC_APB2Periph_GPIOD
                         |RCC_APB2Periph_GPIOE ,
                 
                         ENABLE); //�˿�ʱ��ʹ��  

}


/*******************************************************************************
*******************************************************************************/
void prot_init(void)
{
  //A��ָʾ��
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
  GPIO_WriteBit(GPIOC,GPIO_Pin_15, Bit_SET);

  //B��ָʾ��
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
  GPIO_WriteBit(GPIOA,GPIO_Pin_0, Bit_SET);
    
//------------------------------------------------------------------------------
  //ADC
  //RST
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
  GPIO_WriteBit(GPIOD,GPIO_Pin_13, Bit_SET);
     
  //CLK
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
  GPIO_WriteBit(GPIOD,GPIO_Pin_12, Bit_SET);
    
  //DOUT
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
  GPIO_WriteBit(GPIOD,GPIO_Pin_14, Bit_SET);
  
  //INPUT
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
  
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
  
//RELAY
/* 
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8
                             |GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
  //��ʼ���̵��������
  GPIO_WriteBit(GPIOB, 
                GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9, 
                Bit_SET);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
  //��ʼ���̵��������
  GPIO_WriteBit(GPIOD, 
                GPIO_Pin_6|GPIO_Pin_7, 
                Bit_SET);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE , &GPIO_InitStruct);
  //��ʼ���̵��������
  GPIO_WriteBit(GPIOE, 
                GPIO_Pin_0, 
                Bit_SET);
  
//------------------------------------------------------------------------------
//LED /�����
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
                             |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE , &GPIO_InitStruct);
  
  //��ʼ�� 
  GPIO_WriteBit(GPIOE, 
                GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
                |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13,
                Bit_RESET);
//-------------------------------------------------------   
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
  //��ʼ�� 
  GPIO_WriteBit(GPIOB, 
                GPIO_Pin_0,
                Bit_RESET);
//  
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
  //��ʼ�� 
  GPIO_WriteBit(GPIOC, 
                GPIO_Pin_4|GPIO_Pin_5,
                Bit_RESET);
//LED INDICATOR
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  
//------------------------------------------------------------------------------
//INPUT  
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12; // 3
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
                             | GPIO_Pin_14 | GPIO_Pin_15; // 6
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
                             | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; // 7
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
                             |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 
                             |GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
                             |GPIO_Pin_14 | GPIO_Pin_15  ; // 14
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD , &GPIO_InitStruct);
//
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15; // 2
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE , &GPIO_InitStruct);
  
//------------------------------------------------------------------------------
//USART1 DDU
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //?? af/out or 50MHz
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
   
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_ResetBits(GPIOA, GPIO_Pin_7); //����״̬

//USART2 MAINBOARD
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ��������Ĭ��ֵ
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //?? af/out or 50MHz
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA , &GPIO_InitStruct);
   
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_SetBits(GPIOA, GPIO_Pin_6); //����״̬
  
  Delay_ms(100);
      
  #ifndef JTAG_EN    
    AFIO->MAPR = (0x00FFFFFF & AFIO->MAPR) | 0x04000000;          //�ر�JTAG 
  #endif   
  */
}

/*******************************************************************************
*******************************************************************************/
void ini_device(void)
{ 
  RCC_Configuration();
  prot_init();
  NVIC_Configuration();
  
  lcd_initial();
  lcd_init(); 
  
  //Led_PortIint();
  
  //USART1_Configuration();  
  //USART2_Configuration();               
  /*
  if (SysTick_Config(SystemFrequency / 1000))
  { 
    while (1);
  }
  */
}

/*******************************************************************************
*******************************************************************************/
