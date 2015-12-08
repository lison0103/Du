#include "iap.h"
	

iapfun jump2app; 
u16 iapbuf[1024];   

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM("WFI");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{
	__ASM("CPSID I");    		  
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM("CPSIE I");		  
}
//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(u32 addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	                        //检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		                //用户代码区第二个字为程序开始地址(复位地址)	
                
                INTX_DISABLE();                                                 //关闭所有中断
                               
                /* MCU peripherals re-initial. */              
                {
                  
                    GPIO_InitTypeDef GPIO_InitStruct;
                                                    
                    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;                 
                    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                  
                                    
                    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;                 
                    GPIO_InitStruct.GPIO_Pin &= ~(GPIO_Pin_13 | GPIO_Pin_14); /* SWDIO/SWCLK */                  
                    GPIO_Init(GPIOA, &GPIO_InitStruct);
                                                       
                    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;                  
                    GPIO_Init(GPIOB, &GPIO_InitStruct);                  
                    GPIO_Init(GPIOC, &GPIO_InitStruct);                  
                    GPIO_Init(GPIOD, &GPIO_InitStruct);                 
                    GPIO_Init(GPIOE, &GPIO_InitStruct);                  
                    GPIO_Init(GPIOF, &GPIO_InitStruct);                 
                    GPIO_Init(GPIOG, &GPIO_InitStruct);                 
  //                  GPIO_Init(GPIOH, &GPIO_InitStruct);                 
  //                  GPIO_Init(GPIOI, &GPIO_InitStruct);

                  /* reset systick */
                  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

                  /* disable all peripherals clock. */
                  RCC->AHBENR = 0;
                  RCC->APB1ENR = 0;
                  RCC->APB2ENR = 0;
                  
  //                USART2->BRR = 0;
                  
                  /* Switch to default cpu clock. */
                  RCC->CFGR = 0;
              } /* MCU peripherals re-initial. */
              
              /* Disable MPU */
//              MPU->CTRL &= ~MPU_CTRL_ENABLE_Msk;



                /* Set new vector table pointer */
                SCB->VTOR = appxaddr;
                
                /* reset register values */
                __set_BASEPRI(0);
                __set_FAULTMASK(0);
                
                /* set up MSP and switch to it */
                __set_PSP(*(volatile unsigned int*) appxaddr);                  //重新设置进程PSP堆栈地址
                __set_CONTROL(0);                                               //设置CONTROL寄存器的值，作用是什么未知???
                __set_MSP(*(volatile unsigned int*) appxaddr);                  //重新设置进程MSP堆栈地址
                
                /* ensure what we have done could take effect */
                __ISB();
                
                
                INTX_DISABLE();
                
                jump2app();							//跳转到APP.
	}
}		 














