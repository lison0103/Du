
#include "includes.h"

GPIO_InitTypeDef    GPIO_InitStruct;
USART_InitTypeDef   USART_InitStruct;

//#define USART1_DR_Base 0x40013804

/***************************************************************************************************
***************************************************************************************************/
void NVIC_Configuration(void)
{
//  NVIC_InitTypeDef NVIC_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
 
#ifdef  VECT_TAB_RAM
    // Set the Vector Table base location at 0x20000000
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); //Ram中调试
#else  /* VECT_TAB_FLASH  */
    // Set the Vector Table base location at 0x08000000
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); //Flash中调试
    //@
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000); //Flash中调试
    //@end
#endif
/*                                                                        
  //设置NVIC优先级分组为Group2：0-3抢占式优先级，0-3的响应式优先级       
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                        
                                                                          
  NVIC_Init(&NVIC_InitStructure);                                        
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;                         
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                   
  NVIC_Init(&NVIC_InitStructure);                                    
*/    
}

/***************************************************************************************************
***************************************************************************************************/
void RCC_Configuration(uint32_t PLLMul)
{
  ErrorStatus HSEStatus;
  
  SystemInit();

  RCC_DeInit(); //时钟初始化
  RCC_HSEConfig(RCC_HSE_ON); //打开外部时钟
  HSEStatus = RCC_WaitForHSEStartUp(); //读取外部时钟状态
  if(HSEStatus == SUCCESS) //启动成功
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //预取指缓存使能 
    FLASH_SetLatency(FLASH_Latency_2); //设置代码延时。这里是二个周期
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//设置AHB的时钟HCLK 	  
    RCC_PCLK2Config(RCC_HCLK_Div1); //高速总线选用的就是HCLK	
    RCC_PCLK1Config(RCC_HCLK_Div2);	  //低速总线用的是HCLK的2分频
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//选择PLL的输入时钟以及它的分频系数	
    RCC_PLLCmd(ENABLE);	//使能PLL锁相环
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
      ;
    }			 //等待LL锁相环稳定
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//选择PLL锁相环为系统时钟	
    while(RCC_GetSYSCLKSource() != 0x08) //检验输出的系统时钟是不是由锁相环提供的
    {
      ;
    }
  }
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE); //for dma  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//为外部中断

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); //USART1 时钟使能
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); //USART2 时钟使能

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  
                         |RCC_APB2Periph_GPIOB   
                         |RCC_APB2Periph_GPIOC,
                 
                         ENABLE); //端口时钟使能  

}

/***************************************************************************************************
***************************************************************************************************/
void prot_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
  {  
    RCC_PLLCmd(DISABLE);	//使能PLL锁相环
    
    while(1)
    {
      
    };  
  }    
}

void test(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA |
                         RCC_APB2Periph_GPIOB, ENABLE);  
  
  
  /* Enable the TIM1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 

  /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* GPIOB Configuration: BKIN pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
 
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 4095;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 2047;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 1023;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 511;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 1;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

  TIM_CCPreloadControl(TIM1, ENABLE);

  TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  
  while(1);
}
/***************************************************************************************************
***************************************************************************************************/
//@ 硬件版本
void hardware_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  //上拉
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB , &GPIO_InitStruct);
}


u8 GetHardwareVerison(void)
{
    if(HARDWARE_VERSION == 0)
    {
        return HARDWARE_V2;
    }
    else
    {
        return HARDWARE_V1;
    }

}
//@end

/***************************************************************************************************
***************************************************************************************************/
void ini_device(void)
{ 
  RCC_Configuration(RCC_PLLMul_9);
  
  prot_init();
  
  NVIC_Configuration();
  
  //@
  hardware_init();
  //@end
  
  //lcd_initial();
  //lcd_init(); 
  
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

/***************************************************************************************************
***************************************************************************************************/
void SysTick_init(void)
{
  SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);
}

void BSP_Init(void)
{  

  ini_device();

  Flash_W25X_Init();

  USART1_Init();
  USART2_Init();
  USART3_Init();
  
  //SystemInit(); //72M
  //LED_GPIO_Config();  
  
  //test
  //test();
}


/***************************************************************************************************
***************************************************************************************************/