
#include "includes.h"

#define MER_LINE  90

static u8 *m_keydata,err=0;
//static u8 error_dis_flag=0;
static u16 Fault_Number=0,Fault_Counter=0,Fault_First_Address=0;
/******************************************************************************* 
*******************************************************************************/
void error_record_display(void)
{
  u8 *err_buff;
  u16 i;
/* 
  TXM_StringDisplay(0,10,40,32,1,BLACK ,WHITE, "查看类型:");
  if(error_dis_flag&0x01)
  {  
    TXM_StringDisplay(0,160,40,32,1,BLACK ,WHITE, "记录");   

    TXM_StringDisplay(0,10, 80,32,1,WHITE ,DGREEN, "查看第"); 
    TXM_DigitDisplay( 0,120,80,32,1,WHITE ,DGREEN,1234,4,0,ALIGN_RIGHT);
    TXM_StringDisplay(0,200,80,32,1,WHITE ,DGREEN, "组");    
  }
  else
  {  
    TXM_StringDisplay(0,160,40,32,1,BLACK ,WHITE, "实时");

    TXM_StringDisplay(0,10,80,32,1,BLACK ,WHITE, "与主板  无连接");    
  }
  
//  TXM_StringDisplay(0,138,50,32,1,0xffff ,0x10ff, "查看类型:记录");
  
  TXM_StringDisplay(0, 10, 120,32,1,0xffff ,0x10ff, "查看");
  TXM_DigitDisplay( 0, 80, 120,32,1,0xffff ,0x10ff,1234,4,0,ALIGN_LEFT);
  TXM_StringDisplay(0,150, 120,32,1,0xffff ,0x10ff, "/");
  TXM_DigitDisplay( 0,170, 120,32,1,0xffff ,0x10ff,1234,4,0,ALIGN_LEFT);
*/
//  Fault_Counter=0;
//  Fault_Number = pt_ModBuff[264];
//  Fault_First_Address
  
//  TXM_FillTextWidget (390, " 查看     /   ");
  
//  TXM_DigitDisplay(394,0,0,24,0,0,0,Fault_Counter,3,0,ALIGN_RIGHT);
//  TXM_DigitDisplay(395,0,0,24,0,0,0,Fault_Number,3,0,ALIGN_RIGHT);

  TXM_DigitDisplay(0,80,MER_LINE,32,1,RED ,LGRAY,Fault_Counter,4,0,ALIGN_RIGHT);
  TXM_DigitDisplay(0,160,MER_LINE,32,0,NAVY ,WHITE,Fault_Number,4,0,ALIGN_RIGHT);

  if(Fault_First_Address)
  {  
    i = (300+Fault_First_Address-Fault_Counter)%300;
    i = 3000+(i*8);
 
    err_buff = &ModBuff[i];
    
    time_display_oneline(396,0,0, &err_buff[2], 0);
    display_error_descrip(398,err_buff[1]);
  }
  else
  {
    TXM_FillTextWidget (392, "无故障记录");
    TXM_FillTextWidget (393, "No Record ");
  }  
}

/******************************************************************************* 
*******************************************************************************/
void error_record(void)
{    
  ZTM_FullScreenImageDisp(314);
  
  Fault_Counter=1;
  Fault_Number = pt_ModBuff[264];
  Fault_First_Address = pt_ModBuff[265];
  
  OSTimeDlyHMSM(0, 0,0,100); 
  
  ZTM_RectangleFill (0, 280,239, 319,BLACK); 
  TXM_StringDisplay(0,60,290,24,0,RED ,0, "删除"); 

  ZTM_RectangleFill (0,MER_LINE-8,239, MER_LINE+40,DGRAY); 
  TXM_StringDisplay(0,8,MER_LINE,32,0,NAVY ,WHITE, "查看"); 
  TXM_StringDisplay(0,150,MER_LINE,32,0,NAVY ,WHITE, "/"); 
  
  error_record_display();   
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,60000,&err);
    
    if((err == OS_ERR_TIMEOUT) || (m_keydata[0]==KEY_ESC))
    {
      break;    
    }  
    else
    {
      if((m_keydata[0]==KEY_UP) || (m_keydata[0]==KEY_LEFT))
      {
        Fault_Counter++;
        if(Fault_Counter > Fault_Number) Fault_Counter = 1;
      }  
      else if((m_keydata[0]==KEY_DOWN) || (m_keydata[0]==KEY_RIGHT))
      {
        if(Fault_Counter>1) Fault_Counter--; else Fault_Counter = Fault_Number;     
      }  
      
      error_record_display();
    }  
/*    
    switch(m_keydata[0])
    {
      case KEY_F1:
        error_dis_flag ^= 0x01;
        break;
      case KEY_F2:
        break;
      case KEY_F3:
        break;
      case KEY_UP:
      
        break;
      case KEY_ESC:
        return_flag = 1;
        break;
    }
    
    error_record_display();   
    
    if(return_flag) break;
*/    
  }  
}

/******************************************************************************* 
*******************************************************************************/