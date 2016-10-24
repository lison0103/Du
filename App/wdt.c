#include "includes.h"
#include "iwdg.h"

void Task_WDT_Init(void *p_arg)
{
  (void)p_arg;   

  u8 TimerCheck = 0u,TimerReset = 0u;
  u8 KeyDataTemp = 0u;
   wdt_init();             //初始化独立看门狗，20s复位
  
    while(1)
    {
        IWDG_ReloadCounter();  //2s喂一次狗       
        
        if( ++TimerCheck > 1 )
        {
          TimerCheck = 0u;
          TimerReset = 0u;
          while(!LCM_HandOn_Check())
          {
            if( ++TimerReset > 10 )
            {
              GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
              OSTimeDlyHMSM(0, 0,0,100);
              GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
              
              KeyDataTemp = KEY_ESC;
              OSTimeDlyHMSM(0, 0,3,0);
              OSMboxPost(KeyMbox,(void *)&KeyDataTemp);
              break;
            }
          }

        }
        OSTimeDlyHMSM(0, 0,2,0); 
    }  
}



