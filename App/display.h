
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f10x.h"

#define DIS_FORMAT_U16    0
#define DIS_FORMAT_S16    1
#define DIS_ALIGN_LEFT    0
#define DIS_ALIGN_MIDDLE  1
#define DIS_ALIGN_RIGHT   2
#define DIS_BCOLOR_DISABLE  0
#define DIS_BCOLOR_ENABLE   1

typedef struct
{  
  u8 DIS_Size; 

  u8 DIS_Format;
  
  u8 DIS_Align;
  u8 DIS_Bits;  
  u8 DIS_Dots;

  u8 DIS_BcolorState;
  
  u16 TextCon;

  u16 DIS_x;
  u16 DIS_y;
  
  u16 DIS_Fcolor;
  u16 DIS_Bcolor;
          
} DIS_DIGITAL_TypeDef; 





#endif //__DISPLAY_H
