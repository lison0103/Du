#include "includes.h"

#define MB_COM_PORT     USART1

static u8 buff[300];

/***************************************************************************************************
***************************************************************************************************/
static u8 modbus_reada(u16 start_addr, u16 len)
{
  u8 rxFlag=1,wms=0;
  u16 uint1=0,uint2=0,uint3=0;
  
  //发送
  buff[0] = 1;
  buff[1] = 3;
  buff[2] = start_addr>>8;
  buff[3] = start_addr;
  buff[4] = len>>8;
  buff[5] = len;
  
  uint1 = CRC16( buff, 6 );
  buff[6] = uint1;
  buff[7] = uint1>>8;
  
  BSP_USART_Send(MB_COM_PORT,buff,8);
  
  for(wms=0;wms++<50;)
  {
    OSTimeDlyHMSM(0, 0,0,10);
    //有接收
    len=BSP_USART_Receive(MB_COM_PORT,buff,0);
    if(len) break;
  }      
  
  if(len)
  { 
    if(CRC16( buff, len))
    {
      rxFlag = 2; 
    }  
    else
    {  
      uint2 = len<<1;
      uint3 = start_addr<<1;
      for(uint1=0; uint1<uint2; uint1++)
      {        
        ModBuff[uint1+uint3] = buff[3+uint1];
      }
      rxFlag = 0; 
    }  
  }  
  else
  {
    rxFlag = 1;
  }  
  
  return(rxFlag);
}

/***************************************************************************************************
***************************************************************************************************/
void AppTask_COM(void *p_arg)
{
  (void)p_arg;   
   
  while (1)
  {
    BSP_USART_Send(MB_COM_PORT,buff,10);
    //modbus_read(25,10);
    
    OSTimeDlyHMSM(0, 0, 0, 500);  
  }
}

/***************************************************************************************************
***************************************************************************************************/
