#include "iap.h"
	

iapfun jump2app; 
u16 iapbuf[1024];   

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM("WFI");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{
	__ASM("CPSID I");    		  
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM("CPSIE I");		  
}
//����ջ����ַ
//addr:ջ����ַ
void MSR_MSP(u32 addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	                        //���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		                //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)	
                
                INTX_DISABLE();                                                 //�ر������ж�
                               
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
                __set_PSP(*(volatile unsigned int*) appxaddr);                  //�������ý���PSP��ջ��ַ
                __set_CONTROL(0);                                               //����CONTROL�Ĵ�����ֵ��������ʲôδ֪???
                __set_MSP(*(volatile unsigned int*) appxaddr);                  //�������ý���MSP��ջ��ַ
                
                /* ensure what we have done could take effect */
                __ISB();
                
                
                INTX_DISABLE();
                
                jump2app();							//��ת��APP.
	}
}		 














