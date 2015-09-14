
#ifndef __BSP_RTCC_H

#define __BSP_RTCC_H

#define RTCC_READ      1
#define RTCC_WRITE     2

#include "stm32f10x.h" 

void RTCC_Init(void);

void RTCC_SetTime( unsigned char *pcBuff ) ;
u8 RTCC_GetTime( unsigned char *pcBuff ) ;

#endif // __BSP_RTCC_H
