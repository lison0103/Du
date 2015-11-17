#include "includes.h"
#include "iwdg.h"

void Task_WDT_Init(void *p_arg)
{
  (void)p_arg;   
  
   wdt_init();             //初始化独立看门狗，20s复位
  
    while(1)
    {
        IWDG_ReloadCounter();  //2s喂一次狗
        
        OSTimeDlyHMSM(0, 0,2,0); 
    }  
}