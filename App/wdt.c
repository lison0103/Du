#include "includes.h"
#include "iwdg.h"

void Task_WDT_Init(void *p_arg)
{
  (void)p_arg;   
  
   wdt_init();             //��ʼ���������Ź���10s��λ
  
    while(1)
    {
        IWDG_ReloadCounter();  //ι��
        
        OSTimeDlyHMSM(0, 0,5,0); 
    }  
}