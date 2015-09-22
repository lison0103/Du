
#ifndef __KEY_H
#define __KEY_H

//#define OLDHW

#define KEY_SW2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define KEY_SW3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define KEY_SW4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define KEY_SW5  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define KEY_SW6  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)
#define KEY_SW7  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY_SW8  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define KEY_SW9  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define KEY_SW10  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)


#ifdef OLDHW
#define KEY_UP          0xe0
#define KEY_DOWN        0x22  
#define KEY_LEFT        0xa3
#define KEY_RIGHT       0xa1
#define KEY_F1          0x91
#define KEY_F2          0x12
#define KEY_F3          0x93
#define KEY_POWER       0xd0
#define KEY_SET         0x33
#define KEY_ESC         0x70
#else
#define KEY_UP          0xd0
#define KEY_DOWN        0x93  
#define KEY_LEFT        0x91
#define KEY_RIGHT       0x12
#define KEY_F1          0xa1
#define KEY_F2          0x22
#define KEY_F3          0xa3
#define KEY_POWER       0xe0
#define KEY_SET         0x70
#define KEY_ESC         0x31
#endif
#endif //__KEY_H