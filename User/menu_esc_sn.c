
#include "includes.h"

#define SN_DES_MAX  30
#define SN_LEN      13
  
/*******************************************************************************
*******************************************************************************/

static u8 *SN_Buff,SN_Temp[20],Para_Cnum=0; //Para_Data=0,
static u8 Para_Choice=0,PS_Flag=0;

static char const esc_df_sn[20] = {"E0000-000-000   "};
static char const EscSN_Code[40] = {"- 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
                                    
const char EscSN_Title[2][20]={"扶梯编号设置","ESC SN CONFIG"}; 
/*******************************************************************************
*******************************************************************************/
void esc_sn_displaya(u8 set_bit)
{  
  char i,a[20];
  
  if(set_bit)
  {
    set_bit--;
    for(i=0;i<set_bit;i++)
    {
      a[i] = SN_Temp[i];
    }  
    a[set_bit] = 0;
    TXM_StringDisplay(0,16,150,32,1,BLACK,LGRAY, (void*)a);  
    
    a[0] = SN_Temp[set_bit];
    a[1] = 0;
    TXM_StringDisplay(0,16+(set_bit*16),150,32,1,YELLOW,RED, (void*)a);  

    for(;i<SN_LEN-1;i++)
    {
      a[i-set_bit] = SN_Temp[i+1];
    }  
    a[i-set_bit] = 0;
    TXM_StringDisplay(0,32+(set_bit*16),150,32,1,BLACK,LGRAY, (void*)a);  
  }
  else
  {  
    SN_Temp[SN_LEN] = 0;
    TXM_StringDisplay(0,16,150,32,1,BLACK,LGRAY, (void*)SN_Temp);
  }  
}

u8 get_sn_Cnum(u8 dat)
{
  u8 i,cnt=0;
  
  for(i=0; i<SN_DES_MAX; i++)
  {
    if(dat == EscSN_Code[i])
    {
      cnt = i;
      break;
    }            
  }  
  
  return(cnt);
}

/*******************************************************************************
*******************************************************************************/
void menu_sn_cfg(void)
{
  u8  i,*m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)EscSN_Title[LANGUAGE]);  
  TXM_StringDisplay(0,190,290,24,0,RED ,0, "修改");

  SN_Buff = &ModBuff[1018];
  
  for(i=0;i<16;i++)
  {  
    if(((SN_Buff[i]!=0X20) && (SN_Buff[i]!=0X2D) && (SN_Buff[i]<0X30)) || ((SN_Buff[i]>0X39)&&(SN_Buff[i]<0X41)) || (SN_Buff[i]>0X5A))
    {
      SN_Buff[i] = esc_df_sn[i];
    }  
  }
  
  for(i=0;i<16;i++)
  {
    SN_Temp[i] = SN_Buff[i];
  }  
  
  Para_Choice=0;
  PS_Flag=0;  
  
  esc_sn_displaya(Para_Choice);
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,60000,&err);
    
    if(err == OS_ERR_TIMEOUT)
    {
      break;
    } 
    else if((!PS_Flag) && (m_keydata[0] == KEY_ESC))
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

            for(i=0;i<SN_LEN;i++)
            {
              SN_Temp[i] = SN_Buff[i];
            }  
            
            Para_Choice=0;
            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "修改");
            
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            
            Para_Choice=0;
            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "修改");
            
            for(i=0;i<SN_LEN;i++)
            {
              SN_Buff[i] = SN_Temp[i];
            }  
            modbus_write(MB_COM_PORT, 509, 8);

            break; 
          case KEY_UP:
            
            if(Para_Cnum < SN_DES_MAX) Para_Cnum++; else Para_Cnum=0;
            SN_Temp[Para_Choice-1] = EscSN_Code[Para_Cnum];
            break; 
          case KEY_DOWN:
            
            if(Para_Cnum) Para_Cnum--;else Para_Cnum=SN_DES_MAX;
            SN_Temp[Para_Choice-1] = EscSN_Code[Para_Cnum];
            break; 
          case KEY_LEFT:
            if(Para_Choice>1) Para_Choice--; 
            Para_Cnum = get_sn_Cnum(SN_Temp[Para_Choice-1]);
            break; 
          case KEY_RIGHT:
            if(Para_Choice<SN_LEN) Para_Choice++;
            Para_Cnum = get_sn_Cnum(SN_Temp[Para_Choice-1]);
            break; 
        }  
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
        Para_Choice = 1;
        Para_Cnum = get_sn_Cnum(SN_Buff[Para_Choice-1]);
        
        TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "确定");
        PS_Flag = 1; 
      }
      
      esc_sn_displaya(Para_Choice);
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/
