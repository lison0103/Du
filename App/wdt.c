#include "includes.h"
#include "iwdg.h"

void Task_WDT_Init(void *p_arg)
{
  (void)p_arg;   
  
   wdt_init();             //��ʼ���������Ź���20s��λ
  
    while(1)
    {
        IWDG_ReloadCounter();  //2sιһ�ι�
        
        OSTimeDlyHMSM(0, 0,2,0); 
    }  
}