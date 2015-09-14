
#include "includes.h"

extern u8 MdReadRst_En;
u16 RstBuffCrc=0;

void Task_READ_ECT(void *p_arg)
{
  (void)p_arg;   
  
  u16 i,err_number=0;
    
  while(modbus_read(MB_COM_PORT, 115, 2))
  {
    OSTimeDlyHMSM(0, 0,0,100); 
  }  
  
  if((ModBuff[230]==ModBuff[231]) && (ModBuff[230]>10) && (ModBuff[230]<18))
  {
    ECT_A_VERSION = 1;
  }  

  while(modbus_read(MB_COM_PORT, 150, 100))
  {
    OSTimeDlyHMSM(0, 0,0,100); 
  }  
  
  if(ModBuff[411] == ModBuff[351])
  {
    if((ModBuff[411]>=20) && (ModBuff[411]<28))
    {
      ECT_A_VERSION = 2;
    }  
    else if(ModBuff[411]>=28)
    {
      ECT_A_VERSION = 3;
    }  
  }  
  
  while(1)
  {
    //查看数据有无更新
     modbus_read(MB_COM_PORT, 200, 50);
    //基本信号
    if(pt_ModBuff[210] != pt_ModBuff[549])
    {
      modbus_read(MB_COM_PORT, 500, 50);
    }  
    //系统参数
    if(pt_ModBuff[211] != pt_ModBuff[669])
    {
      modbus_read(MB_COM_PORT, 550, 120);
    }  
    //通信配置
    if(pt_ModBuff[212] != pt_ModBuff[795])
    {
      modbus_read(MB_COM_PORT, 675, 121);
    }  
    //多段速
    if(pt_ModBuff[213] != pt_ModBuff[824])
    {
      modbus_read(MB_COM_PORT, 800, 25);
    } 
    
    //统计数据
    if(pt_ModBuff[216] != pt_ModBuff[299])
    {
      modbus_read(MB_COM_PORT, 250, 50);
    } 
    else 
    {
      if(MdReadRst_En)
      {
        modbus_read(MB_COM_PORT, 975, 1);
        if(RstBuffCrc != pt_ModBuff[975])
        {
          modbus_read(MB_COM_PORT, 850, 125);
        }  
        MdReadRst_En = 2;
        RstBuffCrc = pt_ModBuff[975];
      }  
      
      //故障记录
      if(err_number != pt_ModBuff[263])
      {
        for(i=0;i<10;i++)
        {
          modbus_read(MB_COM_PORT, 1500+(i*120), 120);          
        }  
        
        err_number = pt_ModBuff[263];
      }  
      
      
    }  
    
    
/*    //通信配置
    else if(pt_ModBuff[212] != pt_ModBuff[669])
    {
      modbus_read(MB_COM_PORT, 550, 121);
    }  
*/    
    modbus_read(MB_COM_PORT, 0, 50);

    modbus_read(MB_COM_PORT, 300, 100);
    
    modbus_read(MB_COM_PORT, 400, 100);
    
    OSTimeDlyHMSM(0, 0,0,200); 
  }  
}