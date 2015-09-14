
#ifndef __BSP_H
#define __BSP_H

#include "stm32f10x.h" 

#include "bsp_rtc_1302.h" 

void SysTick_init(void);
void BSP_Init(void);

void key_init(void);
u16 key_scan(void);

u8 read_lcm_busy(void);

void Delay_us(uint32_t n);

extern OS_EVENT * msg_key;
extern OS_EVENT *KeyQEvent;
extern OS_EVENT *KeyMbox;
extern OS_EVENT *msgEvent_Menu;

//void *Qstart[10];    
extern u8 *Qmsg_KEY_UP;     
extern u8 *Qmsg_KEY_DOWN;
extern u8 *Qmsg_KEY_LEFT;
extern u8 *Qmsg_KEY_RIGHT;
extern u8 *Qmsg_KEY_F1;
extern u8 *Qmsg_KEY_F2;
extern u8 *Qmsg_KEY_F3;
extern u8 *Qmsg_KEY_POWER;
extern u8 *Qmsg_KEY_SET;
extern u8 *Qmsg_KEY_ESC;

#endif // __BSP_H