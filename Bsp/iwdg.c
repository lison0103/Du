#include "iwdg.h"

u32 count = 3125; //最大值0xFFF / 4095    Tout = ((4*2^prer)*count) / 40

void wdt_init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
    
    IWDG_SetPrescaler(IWDG_Prescaler_256);  //设置IWDG预分频值:设置IWDG预分频值为64
    
    IWDG_SetReload(count);  //设置IWDG重装载值
    
    IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
    
    IWDG_Enable();  //使能IWDG 
}
