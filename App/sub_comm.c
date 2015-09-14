
#include "includes.h"

OS_EVENT *msgEvent_MCLCM;

static u8 buff[1200];
u16 test_enable=0;

static u8 err;
OS_EVENT *Mutex_Modbus;


/***************************************************************************************************
***************************************************************************************************/
u8 modbus_read(USART_TypeDef* USARTx, u16 start_addr, u16 read_len)
{
  u8 rxFlag=1,wms=0,len;
  u16 uint1=0,uint2=0,uint3=0;

  OSMutexPend(Mutex_Modbus, 0, &err);  
  
  if(test_enable) 
  {
    return(3);
  }
  
  test_enable=1;
    
  //发送
  if(ECT_A_VERSION==3)
  {  
    buff[0] = 2;
  }
  else
  {
    buff[0] = 1;
  }  
  buff[1] = 3;
  buff[2] = start_addr>>8;
  buff[3] = start_addr;
  buff[4] = read_len>>8;
  buff[5] = read_len;
  
  uint1 = CRC16( buff, 6 );
  buff[6] = uint1;
  buff[7] = uint1>>8;
  
  BSP_USART_Send(USARTx,buff,8);
  
  for(wms=0;wms++<20;)
  {
    OSTimeDlyHMSM(0, 0,0,10);
    //有接收
    len=BSP_USART_Receive(USARTx,buff,0);
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
      uint2 = read_len<<1;
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
  
  test_enable=0;
  
  OSTimeDlyHMSM(0, 0, 0, 30);

  OSMutexPost(Mutex_Modbus);   

  return(rxFlag);
}

u8 modbus_write(USART_TypeDef* USARTx, u16 start_addr, u16 len)
{
  u8 rxFlag=1,wms=0;
  u16 i=0,j=0;
  
  OSMutexPend(Mutex_Modbus, 0, &err);
  
  if(test_enable) 
  {
    return(3);
  }
  
  test_enable=1;
    
  //发送
  buff[0] = 1;
  buff[1] = 16;
  buff[2] = start_addr>>8;
  buff[3] = start_addr;
  buff[4] = len>>8;
  buff[5] = len;
  buff[6] = len<<1;
  
  j = start_addr<<1;
  for(i=0;i<buff[6];i++)
  {
    buff[7+i] = ModBuff[j+i]; 
  }  
  j = buff[6]+9;
  i = CRC16( buff, j-2 );
  buff[j-2] = i;
  buff[j-1] = i>>8;
  
  BSP_USART_Send(USARTx,buff,j);
  
  for(wms=0;wms++<20;)
  {
    OSTimeDlyHMSM(0, 0,0,10);
    //有接收
    len=BSP_USART_Receive(USARTx,buff,0);
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
      if((buff[1]==16))
      {
        rxFlag = 0; 
      }  
    }  
  }  
  else
  {
    rxFlag = 1;
  }  
  
  test_enable=0;
  
  //OSTimeDlyHMSM(0, 0, 0, 30);
  
  OSMutexPost(Mutex_Modbus);  

  return(rxFlag);
}

/***************************************************************************************************
//DTS上位机信息
//用于下载图片等上位机应用
***************************************************************************************************/
void DTS_simulation(u16 rxlen, u8 *rxbuff)
{
  u8 a[2]={0,0},flag=0;
  u16 len=0,i,waitms=0;
  
  Delay_us(10000);
  //OSTimeDly(50);
  //清除之前的通信内容
  len = BSP_USART_Receive(LCM_COM_PORT,buff,0);
  len = rxlen;

  do
  {      
    if(len && (buff[0] == 0xaa) && (buff[len-4]==0XCC) && (buff[len-3]==0X33) && (buff[len-2]==0XC3) && (buff[len-1]==0X3C))
    {
      waitms = 0;
      if((buff[1]==0x94))
      {
        i = (buff[6]<<8) | buff[7];
        i += 12; 
        if((len == i) && (flag==0)) //
        {
          BSP_USART_Send(LCM_COM_PORT,buff,len);
         
          Delay_us(10000);
          //OSTimeDlyHMSM(0, 0,0,10); 
          
          a[1] = buff[6];
          a[0] = buff[7];
          BSP_USART_Send(USART3,a,2);
          flag=1; 
        }
        else 
        {
          while(1);
        }  
      }  
      else
      {  
        BSP_USART_Send(LCM_COM_PORT,buff,len);
      }
    }
    else if(len)
    {
      len = BSP_USART_Receive(USART3,buff,0);
    }  
    
    len = BSP_USART_Receive(LCM_COM_PORT,buff,0);
    if((len) && (flag)) 
    {
      flag = 0;
      len=0;
    }
    if(len)
    {
      BSP_USART_Send(USART3,buff,len);
    }  
    
    if(flag==0) 
    {
      len = BSP_USART_Receive(USART3,buff,0);
    }
    else
    {
      flag++;
    }  
    
    Delay_us(1000);
    //OSTimeDly(1);
    
  }while(waitms++<2000);
  
  waitms = 0;
}

/***************************************************************************************************
***************************************************************************************************/
void AppTask_COM(void *p_arg)
{
  u16 len=0;
  (void)p_arg;   
  
  Mutex_Modbus = OSMutexCreate (32, &err);  
  
  msgEvent_MCLCM = OSSemCreate(1); 
  while (1)
  {
    if(test_enable==0)
    {  
      len = BSP_USART_Receive(USART3,buff,0);
      if(len && (buff[0] == 0xaa) && (buff[len-4]==0XCC) && (buff[len-3]==0X33) && (buff[len-2]==0XC3) && (buff[len-1]==0X3C))
      {
        //接收到DTS上位机信息
        test_enable = 2;
        DTS_simulation(len, buff);
        test_enable = 0;
      }  
    }
    
    //OSTimeDly(1); 
    OSTimeDlyHMSM(0, 0,0,20);  
  }
}

/***************************************************************************************************
***************************************************************************************************/
