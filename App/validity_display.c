/****************************************Copyright (c)****************************************************
** File Name:           validity_display.c
** Created By:          lisonchen
** Created date:        2015-09-16
** Version:             v1.00
** Descriptions:        使用有效期
**
*********************************************************************************************************/
#include "includes.h"

#define VDPASS_DES_MAX  10
#define VDPASS_LEN      6

static char const Password_Code[11] = {"-0123456789"};
static u8 *Temp = "------";
static u8 *PASS_Buff,PASS_Temp[20],Para_Cnum=0; //Para_Data=0,
static u8 Para_Choice=0,PS_Flag=0;


static u32 Cpu_LockID;
static u8 TimeBuff[6];
static u32 Current_Date;

static u32 Confirm_word;
static u32 Password_num;
static u8 Password_num_buff[10];
static u8 input_flag = 0;

u8 USER_RIGHT_VALIDITY = 0;
u8 validity_date,already_usedate = 0;
u32 last_set_date,current_set_date = 0;

u8 m_buff_temp[10];




u32 GetLockCode(void)
{
  u32 Lock_Code;
  u32 CpuID[3];
//获取CPU唯一ID
    CpuID[0]=*(vu32*)(0x1ffff7e8);
    CpuID[1]=*(vu32*)(0x1ffff7ec);
    CpuID[2]=*(vu32*)(0x1ffff7f0);
//加密算法,很简单的加密算法
    Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);

    return Lock_Code;
}




void validity_display(u8 set_bit)
{      
      char i,a[20];
      if(set_bit)
      {
        set_bit--;
        for(i=0;i<set_bit;i++)
        {
          a[i] = PASS_Temp[i];
        }  
        a[set_bit] = 0;
        TXM_StringDisplay(0,80,210,32,1,BLACK,DGRAY, (void*)a);  
        
        a[0] = PASS_Temp[set_bit];
        a[1] = 0;
        TXM_StringDisplay(0,80+(set_bit*16),210,32,1,YELLOW,RED, (void*)a);  

        for(;i<VDPASS_LEN-1;i++)
        {
          a[i-set_bit] = PASS_Temp[i+1];
        }  
        a[i-set_bit] = 0;
        TXM_StringDisplay(0,96+(set_bit*16),210,32,1,BLACK,DGRAY, (void*)a);  
      }
      else
      {  
        PASS_Temp[VDPASS_LEN] = 0;
        TXM_StringDisplay(0,80,210,32,1,BLACK,DGRAY, (void*)PASS_Temp);
      }
}

static u8 get_password_num(u8 dat)
{
  u8 i,cnt=0;
  
  for(i=0; i<VDPASS_DES_MAX; i++)
  {
    if(dat == Password_Code[i])
    {
      cnt = i;
      break;
    }            
  }  
  
  return(cnt);
}

void validity_cfg(void)
{
  u8  i,*m_keydata,err=0;
           
      RTCC_GetTime(TimeBuff);
      Current_Date = Get_Current_Date(TimeBuff);
      Cpu_LockID = GetLockCode();
      
      Confirm_word = Cpu_LockID/1000 + Current_Date;
      
      PASS_Temp[0] = Confirm_word/100000 + 0x30;
      PASS_Temp[1] = (Confirm_word%100000)/10000 + 0x30;
      PASS_Temp[2] = (Confirm_word%10000)/1000 + 0x30;
      PASS_Temp[3] = (Confirm_word%1000)/100 + 0x30;
      PASS_Temp[4] = (Confirm_word%100)/10 + 0x30;
      PASS_Temp[5] = Confirm_word%10 + 0x30;
      
      Password_num = Confirm_word*2/3 + 3;
      
      Password_num_buff[0] = Password_num/100000 + 0x30;
      Password_num_buff[1] = (Password_num%100000)/10000 + 0x30;
      Password_num_buff[2] = (Password_num%10000)/1000 + 0x30;
      Password_num_buff[3] = (Password_num%1000)/100 + 0x30;
      Password_num_buff[4] = (Password_num%100)/10 + 0x30;
      Password_num_buff[5] = Password_num%10 + 0x30;      

      m_buff_temp[0] = validity_date + 0x30;
//      m_buff_temp[1] = "天";
  
      ZTM_FullScreenImageDisp(310);
      ZTM_RectangleFill (0,0,239,25,BLUE);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 280,239, 319,BLACK); 
      TXM_StringDisplay(0,60,290,24,0,RED ,WHITE, "     忽略 输入");
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 30,239, 54,DGRAY); 
      TXM_StringDisplay(0,30,30,24,1,BLUE ,DGRAY, "剩余使用有效期");
      ZTM_RectangleFill (0, 60,239, 84,DGRAY); 
      TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, (void*)m_buff_temp);
	  TXM_StringDisplay(0,148,60,24,0,BLUE ,DGRAY, "天");
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 100,239, 124,DGRAY); 
      TXM_StringDisplay(0,60,100,24,1,BLUE ,DGRAY, "验 证 码 ：");
      ZTM_RectangleFill (0, 130,239, 154,DGRAY); 
//      TXM_StringDisplay(0,60,130,24,0,BLUE ,DGRAY, "1 2 3 4 5 6");
      TXM_StringDisplay(0,80,130,24,1,BLUE ,DGRAY, (void*)PASS_Temp);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 170,239, 194,DGRAY); 
      TXM_StringDisplay(0,60,170,24,1,BLUE ,DGRAY, "动 态 密 码 ：");
      ZTM_RectangleFill (0, 210,239, 242,DGRAY); 
//      TXM_StringDisplay(0,80,230,24,0,BLUE ,LGRAY, "------");
      OSTimeDlyHMSM(0, 0,0,10);

  PASS_Buff = Temp;
  
//  for(i=0;i<6;i++)
//  {  
//    if((PASS_Buff[i]<0X30)&&(PASS_Buff[i]>0X39))//(PASS_Buff[i]>0X30)&&(PASS_Buff[i]<0X39)
//    {
//      PASS_Buff[i] = password_num[i];
//    }  
//  }
  
  for(i=0;i<6;i++)
  {
    PASS_Temp[i] = PASS_Buff[i];
  }  
  
  Para_Choice=0;
  PS_Flag=0;  
  
  validity_display(Para_Choice);
  
  while(1)
  {
    if(input_flag == 1)
    {
      input_flag = 0;
      
      if( PASS_Temp[0] == Password_num_buff[0] && PASS_Temp[1] == Password_num_buff[1] && PASS_Temp[2] == Password_num_buff[2]
         && PASS_Temp[3] == Password_num_buff[3] && PASS_Temp[4] == Password_num_buff[4] && PASS_Temp[5] == Password_num_buff[5] )
      {
        USER_RIGHT_VALIDITY = 1;
        validity_date = 180;
        RTCC_GetTime(TimeBuff);
        last_set_date = Get_Current_Date(TimeBuff);
             		
        m_buff_temp[0] = last_set_date/100000;
        m_buff_temp[1] = (last_set_date%100000)/10000;
        m_buff_temp[2] = (last_set_date%10000)/1000;
        m_buff_temp[3] = (last_set_date%1000)/100 ;
        m_buff_temp[4] = (last_set_date%100)/10;
        m_buff_temp[5] = last_set_date%10; 		
		
        Flash_W25X_Write((u8 *)m_buff_temp,R_PASS_ADDR,6);
		
		m_buff_temp[0] = USER_RIGHT_VALIDITY;
		
		Flash_W25X_Write((u8 *)m_buff_temp,R_PASS_ADDR + 6,1);
        
        TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, "密码正确");
        TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, "180 天");
        OSTimeDlyHMSM(0, 0,2,0);
        break;
      }
      else if( PASS_Temp[0] == (0 + 0x30) && PASS_Temp[1] == (0 + 0x30) && PASS_Temp[2] == (0 + 0x30) 
              && PASS_Temp[3] == (0 + 0x30) && PASS_Temp[4] == (0 + 0x30) && PASS_Temp[5] == (0 + 0x30) )
      {
        USER_RIGHT_VALIDITY = 1;
        validity_date = 180;
        RTCC_GetTime(TimeBuff);
        last_set_date = Get_Current_Date(TimeBuff);
		
        m_buff_temp[0] = last_set_date/100000;
        m_buff_temp[1] = (last_set_date%100000)/10000;
        m_buff_temp[2] = (last_set_date%10000)/1000;
        m_buff_temp[3] = (last_set_date%1000)/100 ;
        m_buff_temp[4] = (last_set_date%100)/10;
        m_buff_temp[5] = last_set_date%10; 		
		
        Flash_W25X_Write((u8 *)m_buff_temp,R_PASS_ADDR,6);
		
		m_buff_temp[0] = USER_RIGHT_VALIDITY;
		
		Flash_W25X_Write((u8 *)m_buff_temp,R_PASS_ADDR + 6,1);
        
        TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, "密码正确");
        TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, "180 天");
        OSTimeDlyHMSM(0, 0,2,0);
        break;
      }
      else
      {
        USER_RIGHT_VALIDITY = 0;
		
		m_buff_temp[0] = USER_RIGHT_VALIDITY;
		
		Flash_W25X_Write((u8 *)m_buff_temp,R_PASS_ADDR + 6,1);
		
        TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, "密码错误");
      }     
    }    
    
    m_keydata = OSMboxPend(KeyMbox,60000,&err);
    
    if(err == OS_ERR_TIMEOUT)
    {
      break;
    } 
    else if((!PS_Flag) && ((m_keydata[0] == KEY_ESC) || (m_keydata[0] == KEY_F2)))
    {
      break;
    } 
    else 
    {
      if(PS_Flag)
      {
        switch(m_keydata[0])
        {
          case KEY_ESC:
            
            PS_Flag = 0;

            for(i=0;i<VDPASS_LEN;i++)
            {
              PASS_Temp[i] = PASS_Buff[i];
            }  
            
            Para_Choice=0;
            TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, "     忽略 输入");
            
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            
            Para_Choice=0;
            TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, "     忽略 输入");
            input_flag = 1;
//            for(i=0;i<VDPASS_LEN;i++)
//            {
//              PASS_Buff[i] = PASS_Temp[i];
//            }  
            
//            modbus_write(MB_COM_PORT, 509, 8);

            break; 
          case KEY_UP:
            
            if(Para_Cnum < VDPASS_DES_MAX) Para_Cnum++; else Para_Cnum=0;
            PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
            break; 
          case KEY_DOWN:
            
            if(Para_Cnum) Para_Cnum--;else Para_Cnum=VDPASS_DES_MAX;
            PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
            break; 
          case KEY_LEFT:
            if(Para_Choice>1) Para_Choice--; 
            Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
            break; 
          case KEY_RIGHT:
            if(Para_Choice<VDPASS_LEN) Para_Choice++;
            Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
            break; 
        }  
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
        Para_Choice = 1;
        Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
        
        TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, "     忽略 确定");
        PS_Flag = 1; 
      }
      
      validity_display(Para_Choice);
    }  
  }      

}
