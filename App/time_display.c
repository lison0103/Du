
#include "includes.h"

static u8 Para_Choice=0,PS_Flag=0,Para_Data[6];

//@
u8 temp_date[6];
u8 record_buff[10];
u8 SET_FLAG = 0;
//@end
/*******************************************************************************
*******************************************************************************/
void time_display_oneline(u16 dw,u16 x,u16 y, u8 *tb, u8 set_bit)
{
  u8 dis_data[20],a[20];
  u16 i;
  
  dis_data[0] = '2';
	dis_data[1] = '0';
	dis_data[2] = (tb[0]/10)+0x30;
	dis_data[3] = (tb[0]%10)+0x30;
	dis_data[4] = '-';
	dis_data[5] = (tb[1]/10)+0x30;
	dis_data[6] = (tb[1]%10)+0x30;
	dis_data[7] = '-';
	dis_data[8] = (tb[2]/10)+0x30;
	dis_data[9] = (tb[2]%10)+0x30;
	dis_data[10] = ' ';
	dis_data[11] = (tb[3]/10)+0x30;
	dis_data[12] = (tb[3]%10)+0x30;
	dis_data[13] = ':';
	dis_data[14] = (tb[4]/10)+0x30;
	dis_data[15] = (tb[4]%10)+0x30;
	dis_data[16] = ':';
	dis_data[17] = (tb[5]/10)+0x30;														
	dis_data[18] = (tb[5]%10)+0x30;																						
  dis_data[19] = 0;
  
  if(set_bit)
  {
    set_bit = 2+((set_bit-1)*3);
    
    for(i=0;i<set_bit;i++)
    {
      a[i] = dis_data[i];
    }  
    a[set_bit] = 0;
    TXM_StringDisplay(0,x,y,24,1,BLACK,LGRAY, (void*)a);  
    
    a[0] = dis_data[set_bit];
    a[1] = dis_data[set_bit+1];
    a[2] = 0;
    TXM_StringDisplay(0,x+(set_bit*12),y,24,1,YELLOW,RED, (void*)a);  
    
    for(i=0;i<18-set_bit-1;i++)
    {
      a[i] = dis_data[i+set_bit+2];
    }  
    a[i] = 0;
    TXM_StringDisplay(0,x+24+(set_bit*12),y,24,1,BLACK,LGRAY, (void*)a);  
    
    
    //TXM_StringDisplay(dw,x,y,24,1,BLUE ,LGRAY, (void*)dis_data);
    
    //TXM_StringDisplay(0,16+(set_bit*16),150,32,1,YELLOW,RED, (void*)a);  
    //TXM_StringDisplay(dw,x,y,24,1,BLUE ,LGRAY, (void*)dis_data);
  }
  else
  {  
    TXM_StringDisplay(dw,x,y,24,1,WHITE ,DGRAY, (void*)dis_data);
  }
}

/*******************************************************************************
*******************************************************************************/
void time_display(u16 dw,u16 tw,u8 *tb)
{
  u8 dis_data[31];

	dis_data[0] = ' ';
	dis_data[1] = ' ';
	dis_data[2] = 'D';
	dis_data[3] = 'U';
	dis_data[4] = ' ';

  dis_data[5] = '2';
	dis_data[6] = '0';
	dis_data[7] = (tb[0]/10)+0x30;
	dis_data[8] = (tb[0]%10)+0x30;
	dis_data[9] = '-';
	dis_data[10] = (tb[1]/10)+0x30;
	dis_data[11] = (tb[1]%10)+0x30;
	dis_data[12] = '-';
	dis_data[13] = (tb[2]/10)+0x30;
	dis_data[14] = (tb[2]%10)+0x30;
	dis_data[15] = ' ';
	dis_data[16] = ' ';
	dis_data[17] = (tb[3]/10)+0x30;
	dis_data[18] = (tb[3]%10)+0x30;
	dis_data[19] = ':';
	dis_data[20] = (tb[4]/10)+0x30;
	dis_data[21] = (tb[4]%10)+0x30;
	dis_data[22] = ':';
	dis_data[23] = (tb[5]/10)+0x30;														
	dis_data[24] = (tb[5]%10)+0x30;																						

	dis_data[25] = ' ';
	dis_data[26] = ' ';
	dis_data[27] = ' ';
	dis_data[28] = ' ';
	dis_data[29] = ' ';

	dis_data[30] = 0;

  dis_data[2] = 'D';
  dis_data[3] = 'a';
  dis_data[4] = 't';
  dis_data[5] = 'e';
  dis_data[6] = ' ';  
  dis_data[15] = 0;
  TXM_FillTextWidget (dw, (void*)&dis_data[2]);
  
  dis_data[12] = 'T';
  dis_data[13] = 'i';
  dis_data[14] = 'm';
  dis_data[15] = 'e';
  dis_data[16] = ' ';
  dis_data[25] = 0;
  TXM_FillTextWidget (tw, (void*)&dis_data[12]);
}
/*******************************************************************************
*******************************************************************************/
//@获取当前年月日，格式150915
void Get_Current_Date(u8 date[], u8 *tb)
{
  
	date[0] = (tb[0]/10);
	date[1] = (tb[0]%10);
	date[2] = (tb[1]/10);
	date[3] = (tb[1]%10);
	date[4] = (tb[2]/10);
	date[5] = (tb[2]%10);  
               
}
//@end
/*******************************************************************************
*******************************************************************************/
void menu_time_set(void)
{
  u8  i,*m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
//  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)EscSN_Title[LANGUAGE]);  
  TXM_StringDisplay(0,65,290,24,1,LGRAY ,BLACK, "下传");
  TXM_StringDisplay(0,190,290,24,1,LGRAY ,BLACK, "设置");

  Para_Choice=0;
  PS_Flag=0;  
  
  TXM_StringDisplay(0,8,50,24,1,CYAN ,LGRAY, "DU TIME & DATE:");
  TXM_StringDisplay(0,8,120,24,1,BLUE ,LGRAY, "ECT TIME & DATE:");

  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,100,&err);
    
    time_display_oneline(0,8,80,TimeBuff, 0);
    time_display_oneline(0,8,150,&ModBuff[50], 0);
    
    if(err == OS_ERR_TIMEOUT)
    {
      
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
                        
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            
            //@
            SET_FLAG = 1;
            //@end
            
            RTCC_SetTime(Para_Data);
            
            for(i=0;i<6;i++)
            {  
              ModBuff[50+i] = Para_Data[i];
            }
            modbus_write(MB_COM_PORT, 25, 3);

            break; 
          //@ 修改支持时间日期设置上下翻滚，月份设置大小月和闰年   month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
          case KEY_UP:
            switch(Para_Choice)
            {
              case 1://年
                if(Para_Data[Para_Choice-1]<99) Para_Data[Para_Choice-1]++;
                break;
              case 2://月
                if(Para_Data[Para_Choice-1]<12) Para_Data[Para_Choice-1]++;
                else Para_Data[Para_Choice-1] = 1;
                if(Para_Data[2] > month[Para_Data[1]-1]) Para_Data[2] = month[Para_Data[1]-1];
                break;
              case 3://日
                if(Para_Data[Para_Choice-1] < ((Para_Data[1] == 2) ? (month[Para_Data[1]-1] + Leap_Year(2000+Para_Data[0])) : (month[Para_Data[1]-1])) )                  
                     Para_Data[Para_Choice-1]++;
                else Para_Data[Para_Choice-1] = 1;
                break;
              case 4://时
                if(Para_Data[Para_Choice-1]<23) Para_Data[Para_Choice-1]++;
                else Para_Data[Para_Choice-1] = 0;
                break;
              default://分、秒
                if(Para_Data[Para_Choice-1]<59) Para_Data[Para_Choice-1]++;
                else Para_Data[Para_Choice-1] = 0;
            }  
            break; 
          case KEY_DOWN:
            switch(Para_Choice)
            {
              case 1://年
                if(Para_Data[Para_Choice-1]>15) Para_Data[Para_Choice-1]--;
                break;
              case 2://月
                if(Para_Data[Para_Choice-1]>1) Para_Data[Para_Choice-1]--;
                else Para_Data[Para_Choice-1] = 12;
                if(Para_Data[2] > month[Para_Data[1]-1]) Para_Data[2] = month[Para_Data[1]-1];
                break;
              case 3://日
                if(Para_Data[Para_Choice-1]>1) Para_Data[Para_Choice-1]--;
                else Para_Data[Para_Choice-1] = (Para_Data[1] == 2) ? (month[Para_Data[1]-1] + Leap_Year(2000+Para_Data[0])) :  (month[Para_Data[1]-1]);
                break;
              case 4://时
                if(Para_Data[Para_Choice-1]>1) Para_Data[Para_Choice-1]--;
                else Para_Data[Para_Choice-1] = 23;
                break;
              default://分、秒
                if(Para_Data[Para_Choice-1]) Para_Data[Para_Choice-1]--;
                else Para_Data[Para_Choice-1] = 59;
            }  
            break;
          //@end
          case KEY_LEFT:
            if(Para_Choice>1) Para_Choice--; 
            break; 
          case KEY_RIGHT:
            if(Para_Choice<6) Para_Choice++;
            break; 
        } 
        
        if(!PS_Flag)
        {  
          TXM_StringDisplay(0,8,230,24,1,LGRAY ,LGRAY, "                   ");
          
          Para_Choice=0;
          TXM_StringDisplay(0,190,290,24,1,LGRAY ,BLACK, "设置");
          
          
          //@获取当前设置时间,记录为上次设置日期
          #if 1
          if(1 == SET_FLAG)
          {
              SET_FLAG = 0;
              if(USER_RIGHT_VALIDITY == 1)
              {
                  Get_Current_Date(current_set_date, Para_Data);     
                  
                  for(u8 j = 0; j < 6; j++)
                  {
                    last_set_date[j] = current_set_date[j];
                  
                  }
                  
                  DuSysBuff[30] = last_set_date[0];
                  DuSysBuff[31] = last_set_date[1];
                  DuSysBuff[32] = last_set_date[2];
                  DuSysBuff[33] = last_set_date[3];
                  DuSysBuff[34] = last_set_date[4];
                  DuSysBuff[35] = last_set_date[5]; 
                  
                  du_sys_data_write();
              }
          }
          #endif
          //@end
        }  
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
        Para_Choice = 1;
        for(i=0;i<6;i++)
        {  
          Para_Data[i] = TimeBuff[i];
        }
        
        TXM_StringDisplay(0,190,290,24,1,WHITE ,BLACK, "确定");
        PS_Flag = 1; 
        
        //@获取当前设置时间，记录与上次设置时间的时间差值
        #if 1
        if(USER_RIGHT_VALIDITY == 1)
        {
            Get_Current_Date(temp_date, Para_Data);
            VALIDITY_USE_DATE += Calculate(last_set_date,temp_date);
            
            du_sys_data_write();
        }
        #endif
        //@end
        
      }
      else if(m_keydata[0]==KEY_F1)
      {        
        for(i=0;i<6;i++)
        {  
          ModBuff[50+i] = TimeBuff[i];
        }
        modbus_write(MB_COM_PORT, 25, 3);
      }
               
      if(PS_Flag)
      {  
        time_display_oneline(0,8,230,Para_Data, Para_Choice);
      }    
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/