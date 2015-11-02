#ifndef __BKP_H_
#define __BKP_H_
#include "stm32f10x_conf.h"

//42个16位备份数据寄存器，84个字节
//地址:0x04~0x28,0x40~0xBC,偏移:0x04

//1~10
#define BKP_ADDR1(i)            (0x04 + 0x04*(i - 1))
//11~42
#define BKP_ADDR2(i)            (0x40 + 0x04*(i - 1))

void BKP_Init(void);
void BKP_Write(u16 addr, u16 data);
u16 BKP_Read(u16 addr);

#endif