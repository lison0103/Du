
#include "includes.h"

extern void GetCpuID(void);

/*******************************************************************************
*******************************************************************************/
static u8 Para_Choice=0,PS_Flag=0;

const u8 *Menu_ConnectPC_Item[][2] =
{                                                           
  {" 01 发送数据    "," 01 CHINESE/中文  "},
  {" 02 接收再发送  "," 02 ENGLISH/英文  "},
};

const char ConnectPC_Title[2][20]={"连接电脑","Connect"}; 

u8 display_receive_buff[64];
u32 buff_num;
/*******************************************************************************
*******************************************************************************/
void menu_ConnectPC_display(void)
{
  u16 i;
  
  for(i=0;i<2;i++)
  {  
    if(Para_Choice==i)
    {  
      TXM_StringDisplay(0,8,50+(i*30),24,1,YELLOW ,RED, (void*)Menu_ConnectPC_Item[i][LANGUAGE]); 
    }
    else
    {
      TXM_StringDisplay(0,8,50+(i*30),24,1,YELLOW ,BLUE, (void*)Menu_ConnectPC_Item[i][LANGUAGE]); 
    }  
      
    OSTimeDlyHMSM(0, 0,0,5); 
  }
  
    //清除数据显示
    ZTM_RectangleFill (0,140,239,204,BLUE);
    //接收到的数据显示
    TXM_StringDisplay(0,0,50+(3*30),16,1,YELLOW ,BLUE, (void*)display_receive_buff);
  
}

/*******************************************************************************
*******************************************************************************/
void menu_connect_to_pc_cfg(void)
{
  u8  *m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)ConnectPC_Title[LANGUAGE]);  
  TXM_StringDisplay(0,190,290,24,0,RED ,0, "选择");

  Para_Choice = LANGUAGE;
  PS_Flag=0;  
  
  USB_Disconnect();
  OSTimeDlyHMSM(0, 0,0,100);
  Connect_To_COM();
  menu_ConnectPC_display();
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,100,&err);
    
    if(err == OS_ERR_TIMEOUT)//按键消息超时
    {
//      USB_Disconnect();
//      break;
      buff_num = USB_Receive_Data(display_receive_buff);
      if(buff_num)
      {        
        menu_ConnectPC_display();
        
        if((buff_num == 17) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[buff_num-4]==0X23) && (display_receive_buff[buff_num-3]==0X2a) && (display_receive_buff[buff_num-2]==0X23) && (display_receive_buff[buff_num-1]==0X2a))  
        {
              DuSysBuff[28] = display_receive_buff[10];
              DuSysBuff[29] = display_receive_buff[11];
              DuSysBuff[30] = display_receive_buff[12];
              
              DuSysBuff[31] = display_receive_buff[1];
              DuSysBuff[32] = display_receive_buff[2];
              DuSysBuff[33] = display_receive_buff[3];
              DuSysBuff[34] = display_receive_buff[4];
              DuSysBuff[35] = display_receive_buff[5];
              DuSysBuff[36] = display_receive_buff[6];
              DuSysBuff[37] = display_receive_buff[7];
              DuSysBuff[38] = display_receive_buff[8];
 
              //清空buffer
              for(u8 i = 0;i<64;i++)
                  display_receive_buff[i] = ' ';

              GetCpuID();
              
              du_sys_data_write();
              
              TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, "激活成功！");
              OSTimeDlyHMSM(0, 0,1,500);
              
              USB_Disconnect();
              validity_cfg();
              break;

        }
        //清空buffer
        for(u8 i = 0;i<64;i++)
            display_receive_buff[i] = ' ';
      }
    } 
    else if((!PS_Flag) && (m_keydata[0] == KEY_ESC))
    {
      USB_Disconnect();
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



            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "选择");
            
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            
            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "选择");
            

            switch(Para_Choice)
            {
              case 0:
                USB_Send_Data("USB_Virtual_COM_PORT\n", 22);
                break;
              case 1:
                USB_Receive_Data_Send();
              break;  
                
            }
            break; 
          case KEY_UP:
        
            if(Para_Choice < 1) Para_Choice++; else Para_Choice=0;
            break; 
          case KEY_DOWN:
            
            if(Para_Choice) Para_Choice--;else Para_Choice=1;
            break; 
        }  
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
        TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "确定");
        PS_Flag = 1; 
      }
      
      menu_ConnectPC_display();
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/
