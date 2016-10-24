#include "includes.h"
#include "os_cpu.h"

#define INDEX_ADR 1001
#define DU_OFFSET_ADR 1

u8 buff_temp[4096];

/*******************************************************************************
*******************************************************************************/
u16 esc_bk_pos_check(u8 *sn)
{
  u8 flag=0,cnt=0;
  u16 sn_number=0,i,j,k,a;
  u32 adr; 
    
  for(i=0;i<10;i++)
  {
    adr = i;
    adr = (i*1000) + INDEX_ADR;
      
    Flash_W25X_Read(buff_temp,adr,1000);
    
    for(j=0;j<50;j++)
    {
      a = (j*20)+2;
      cnt = 0;
      for(k=0;k<16;k++)
      {  
        if(buff_temp[a+k] == sn[k])
        {
          cnt++;
        }  
        else
        {
          break;
        }  
      }
        
      if(cnt==16)
      {
        sn_number = (i*50)+j+1;
        flag = 1;
        break;
      }  
    }  

    if(flag)
    {
      break;
    }  
  }   
  
  return(sn_number);
}

u8 get_esc_bk_item_index(u16 num,u8 *buff)
{  
  u32 addr; 

  if(num>RECORD_ESC_NUMBER)
  {
    return(1);
  }  
  else
  {
    addr = num-1;
    addr = (addr*20)+INDEX_ADR;
  
    Flash_W25X_Read(buff,addr,20);    
  }  
  
  return(1);
}

u16 esc_bk_pos_write(u8 *sn,u16 num)
{
  u16 i;
  u32 adr; 
 
  adr = num-1;
  adr = (adr*20)+INDEX_ADR;
      
  buff_temp[0] = num;
  buff_temp[1] = num>>8;

  for(i=0;i<16;i++)
  {
    buff_temp[i+2] = sn[i];
  }  
  buff_temp[18] = 0XCC;
  buff_temp[19] = 0X33;
  
  Flash_W25X_Write(buff_temp,adr,20);  
  
  return(esc_bk_pos_check(sn));
}

  
/*  
u16 esc_bk_num_check(void)
{
  u8 flag=0,cnt=0;
  u16 sn_number=0,i,j,k,a;
  u32 adr; 
    
  for(i=0;i<10;i++)
  {
    adr = i;
    adr = (i+1)*1000;
      
    Flash_W25X_Read(buff,adr,1000);
    
    for(j=0;j<50;j++)
    {
      a = (j*20)+2;
      cnt = 0;
      for(k=0;k<16;k++)
      {  
        if(buff[a] == sn[k])
        {
          cnt++;
        }  
        else
        {
          break;
        }  
      }
        
      if(cnt==16)
      {
        sn_number = (i*50)+j+1;
        flag = 1;
        break;
      }  
    }  

    if(flag)
    {
      break;
    }  
  }   
  
  return(sn_number);
}
*/  

/*******************************************************************************
*******************************************************************************/
void du_sys_data_write(void)
{
  u16 i;
//@
#if OS_CRITICAL_METHOD == 3u
   int cpu_sr;
#endif
  OS_ENTER_CRITICAL();
//@end
  
  i = CRC16( DuSys_Data, 98 );
  DuSys_Data[98] = i;
  DuSys_Data[99] = i>>8;
      
  Flash_W25X_Write(DuSys_Data,DU_OFFSET_ADR,100);  
  OSTimeDlyHMSM(0, 0,0,100);    
  Flash_W25X_Write(DuSys_Data,DU_OFFSET_ADR+200,100);  

//@  
  OS_EXIT_CRITICAL();
//@end  
  
  BKP_Write(BKP_ADDR2(1),LANGUAGE);
  BKP_Write(BKP_ADDR2(2),RECORD_ESC_NUMBER);
  BKP_Write(BKP_ADDR2(3),USER_RIGHT_VALIDITY);
  BKP_Write(BKP_ADDR2(4),VALIDITY_USE_DATE);
  for( u8 j = 0; j < 6; j++ )
  {
    BKP_Write(BKP_ADDR2(5+j),VALIDITY_LAST_DATE(j));
  }  
  BKP_Write(BKP_ADDR2(11),DU_REGISTERED_NUMBER);
  BKP_Write(BKP_ADDR2(12),DU_RTC_ERROR_NUMBER);
  for( u8 j = 0; j < 7; j++ )
  {
    BKP_Write(BKP_ADDR2(13+j),DU_USER_RIGHT_PASSWORD(j));
  }
  BKP_Write(BKP_ADDR2(20),DU_INPUT_PASS_DATE(0));
  BKP_Write(BKP_ADDR2(21),DU_INPUT_PASS_DATE(1));
  BKP_Write(BKP_ADDR2(22),DU_USER_RIGHT_LEVEL);
}

void esc_bk_init(void)
{
  u16 i;
  u8 errorflag = 0;
  
  BKP_Init();

//@
#if OS_CRITICAL_METHOD == 3u
   int cpu_sr;
#endif
  OS_ENTER_CRITICAL();  
//@end
  
  Flash_W25X_Read(DuSys_Data,DU_OFFSET_ADR,100);  
  if(CRC16(DuSys_Data, 100))
  {
    OSTimeDlyHMSM(0, 0,0,100);
    Flash_W25X_Read(DuSys_Data,DU_OFFSET_ADR+200,100);  
    if(CRC16(DuSys_Data, 100))
    {
      
      for(i=0;i<100;i++)
      {
        DuSys_Data[i] = 0;
      } 
      
      DU_REGISTERED_NUMBER = BKP_Read(BKP_ADDR2(5));
      
      if( DU_REGISTERED_NUMBER )
      { 
          LANGUAGE = BKP_Read(BKP_ADDR2(1));
          RECORD_ESC_NUMBER = BKP_Read(BKP_ADDR2(2));
          USER_RIGHT_VALIDITY = BKP_Read(BKP_ADDR2(3));
          VALIDITY_USE_DATE = BKP_Read(BKP_ADDR2(4));
          for( u8 j = 0; j < 6; j++ )
          {
            VALIDITY_LAST_DATE(j) = BKP_Read(BKP_ADDR2(5+j));
          }  
          DU_REGISTERED_NUMBER = BKP_Read(BKP_ADDR2(11));
          DU_RTC_ERROR_NUMBER = BKP_Read(BKP_ADDR2(12));
          for( u8 j = 0; j < 7; j++ )
          {
            DU_USER_RIGHT_PASSWORD(j) = BKP_Read(BKP_ADDR2(13+j));
          }
          DU_INPUT_PASS_DATE(0) = BKP_Read(BKP_ADDR2(20));
          DU_INPUT_PASS_DATE(1) = BKP_Read(BKP_ADDR2(21)); 
          DU_USER_RIGHT_LEVEL = BKP_Read(BKP_ADDR2(22)); 
          GetCpuID();
      }
      else
      {
          DU_REGISTERED_NUMBER = 0u;
      }
      
      du_sys_data_write();
      
      errorflag = 1;
    }  
  }  
  else
  {
    
  }  
//@  
  OS_EXIT_CRITICAL();
  
  if(errorflag)
  {       
      errorflag = 0;
      if(DU_USER_RIGHT_PASSWORD(6) == 1)
      {
          Unknow_Error_display();
      }
  }
//@end  
}

/*******************************************************************************
*******************************************************************************/

