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


const char validity_disp_item[][25]={
"     忽略 输入",
"   Ignore Input",
" 剩余使用有效期",
"Validity  Date",
"天",
"Day",
"    验 证 码 ：",
"Verification code:",
"   动 态 密 码 ：",
"Dynamic password:",
"     忽略 确定",
"    Ignore  OK ",
"密码正确",
"  RIGHT ",
"密码错误",
"  Error ",
"180 天",
"180 Day"
}; 

static char const Password_Code[11] = {"-0123456789"};
static u8 *Temp = "------";
static u8 *PASS_Buff,PASS_Temp[20],Para_Cnum=0; 
static u8 Para_Choice=0,PS_Flag=0;


//static u32 Cpu_LockID;
//static u8 TimeBuff[6];
static u32 Current_Date;

static u32 Confirm_word;
static u32 Password_num;
static u8 Password_num_buff[10];
static u8 input_flag = 0;

u8 validity_date = 0;
u8 last_set_date[6],current_set_date[6];

u8 m_buff_temp[3];


/*******************************************************************************
//获取验证码
*******************************************************************************/
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
    
//    RTCC_GetTime(TimeBuff);
    Get_Current_Date(current_set_date, TimeBuff);
    Current_Date = current_set_date[0]*100000 + current_set_date[1]*10000 + current_set_date[2]*1000 + current_set_date[3]*100 + current_set_date[4]*10 + current_set_date[5];
    Lock_Code = Lock_Code/1000 + Current_Date;
    
    return Lock_Code;
}

/*******************************************************************************
//获取动态密码
*******************************************************************************/
u32 GetDynamicPassNum(void)
{
  u32 Pass_Num,Lock_Num;
  
  Lock_Num = GetLockCode();

  Pass_Num = ((Lock_Num*2)/3) + 3;
  
  return Pass_Num;
  
}

/*******************************************************************************
//密码动态显示函数
*******************************************************************************/
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
           
      
      Confirm_word = GetLockCode();
      
      PASS_Temp[0] = Confirm_word/100000 + 0x30;
      PASS_Temp[1] = (Confirm_word%100000)/10000 + 0x30;
      PASS_Temp[2] = (Confirm_word%10000)/1000 + 0x30;
      PASS_Temp[3] = (Confirm_word%1000)/100 + 0x30;
      PASS_Temp[4] = (Confirm_word%100)/10 + 0x30;
      PASS_Temp[5] = Confirm_word%10 + 0x30;
      
      Password_num = GetDynamicPassNum();
      
      Password_num_buff[0] = Password_num/100000 + 0x30;
      Password_num_buff[1] = (Password_num%100000)/10000 + 0x30;
      Password_num_buff[2] = (Password_num%10000)/1000 + 0x30;
      Password_num_buff[3] = (Password_num%1000)/100 + 0x30;
      Password_num_buff[4] = (Password_num%100)/10 + 0x30;
      Password_num_buff[5] = Password_num%10 + 0x30;      

      m_buff_temp[0] = validity_date/100 + 0x30;
      m_buff_temp[1] = validity_date%100/10 + 0x30;
      m_buff_temp[2] = validity_date%10 + 0x30;
  
      ZTM_FullScreenImageDisp(310);
      ZTM_RectangleFill (0,0,239,25,BLUE);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 280,239, 319,BLACK); 
      TXM_StringDisplay(0,60,290,24,0,RED ,WHITE, (void*)validity_disp_item[0 + LANGUAGE]);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 30,239, 54,DGRAY); 
      TXM_StringDisplay(0,20,30,24,1,BLUE ,DGRAY, (void*)validity_disp_item[2 + LANGUAGE]);
      ZTM_RectangleFill (0, 60,239, 84,DGRAY); 
      TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, (void*)m_buff_temp);
      TXM_StringDisplay(0,148,60,24,0,BLUE ,DGRAY, (void*)validity_disp_item[4 + LANGUAGE]);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 100,239, 124,DGRAY); 
      TXM_StringDisplay(0,20,100,24,1,BLUE ,DGRAY, (void*)validity_disp_item[6 + LANGUAGE]);
      ZTM_RectangleFill (0, 130,239, 154,DGRAY); 

      TXM_StringDisplay(0,80,130,24,1,BLUE ,DGRAY, (void*)PASS_Temp);
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 170,239, 194,DGRAY); 
      TXM_StringDisplay(0,20,170,24,1,BLUE ,DGRAY, (void*)validity_disp_item[8 + LANGUAGE]);
      ZTM_RectangleFill (0, 210,239, 242,DGRAY); 

      OSTimeDlyHMSM(0, 0,0,10);

  
      PASS_Buff = Temp;
  
      for(i=0;i<6;i++)
      {
        PASS_Temp[i] = PASS_Buff[i];
      }  
      
      Para_Choice=0;
      PS_Flag=0;  
      
      validity_display(Para_Choice);
      
      while(1)
      {
        if(input_flag == 1)//判断密码是否正确
        {
          input_flag = 0;
          
          if( PASS_Temp[0] == Password_num_buff[0] && PASS_Temp[1] == Password_num_buff[1] && PASS_Temp[2] == Password_num_buff[2]
             && PASS_Temp[3] == Password_num_buff[3] && PASS_Temp[4] == Password_num_buff[4] && PASS_Temp[5] == Password_num_buff[5] )
          {
              USER_RIGHT_VALIDITY = 1;
              validity_date = 180;
              VALIDITY_USE_DATE = 0;
//              RTCC_GetTime(TimeBuff);
              Get_Current_Date(last_set_date, TimeBuff);
              
              DuSysBuff[30] = last_set_date[0];
              DuSysBuff[31] = last_set_date[1];
              DuSysBuff[32] = last_set_date[2];
              DuSysBuff[33] = last_set_date[3];
              DuSysBuff[34] = last_set_date[4];
              DuSysBuff[35] = last_set_date[5]; 		                
                      
              
              du_sys_data_write();
              
              TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, (void*)validity_disp_item[12 + LANGUAGE]);
              TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, (void*)validity_disp_item[16 + LANGUAGE]);
              OSTimeDlyHMSM(0, 0,2,0);
              break;
          }
          else if( PASS_Temp[0] == (0 + 0x30) && PASS_Temp[1] == (0 + 0x30) && PASS_Temp[2] == (0 + 0x30) 
                  && PASS_Temp[3] == (0 + 0x30) && PASS_Temp[4] == (0 + 0x30) && PASS_Temp[5] == (0 + 0x30) )
          {
              USER_RIGHT_VALIDITY = 1;
              validity_date = 180;
              VALIDITY_USE_DATE = 0;
//              RTCC_GetTime(TimeBuff);
              Get_Current_Date(last_set_date, TimeBuff);
              
              DuSysBuff[30] = last_set_date[0];
              DuSysBuff[31] = last_set_date[1];
              DuSysBuff[32] = last_set_date[2];
              DuSysBuff[33] = last_set_date[3];
              DuSysBuff[34] = last_set_date[4];
              DuSysBuff[35] = last_set_date[5]; 		             
                            
              du_sys_data_write();
              
              TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, (void*)validity_disp_item[12 + LANGUAGE]);
              TXM_StringDisplay(0,100,60,24,1,BLUE ,DGRAY, (void*)validity_disp_item[16 + LANGUAGE]);
              OSTimeDlyHMSM(0, 0,2,0);
              break;
          }
          else
          {
              USER_RIGHT_VALIDITY = 0;
                     
              du_sys_data_write();
              
              TXM_StringDisplay(0,70,250,24,1,YELLOW ,RED, (void*)validity_disp_item[14 + LANGUAGE]);
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
                TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, (void*)validity_disp_item[0 + LANGUAGE]);
                
                break; 
              case KEY_SET:
              case KEY_F3:  
                PS_Flag = 0;
                
                Para_Choice=0;
                TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, (void*)validity_disp_item[0 + LANGUAGE]);
                input_flag = 1;
    //            for(i=0;i<VDPASS_LEN;i++)
    //            {
    //              PASS_Buff[i] = PASS_Temp[i];
    //            }  
                

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
                else Para_Choice = VDPASS_LEN; 
                Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
                break; 
              case KEY_RIGHT:
                if(Para_Choice<VDPASS_LEN) Para_Choice++;
                else Para_Choice = 1;
                Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
                break; 
            }  
          } 
          else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
          {
              Para_Choice = 1;
              Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
              
              TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, (void*)validity_disp_item[10 + LANGUAGE]);
              PS_Flag = 1; 
          }
          
          validity_display(Para_Choice);
        }  
      }      

}
