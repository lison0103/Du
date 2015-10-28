
#include "includes.h"

#include "iap.h"

extern void GetCpuID(void);
extern void du_hardware_test(void);

//#define VCP_TEST        1

/*******************************************************************************
*******************************************************************************/
#if VCP_TEST
static u8 Para_Choice=0,PS_Flag=0;

const u8 *Menu_ConnectPC_Item[][2] =
{                                                           
  {" 01 发送数据    "," 01 CHINESE/中文  "},
  {" 02 接收再发送  "," 02 ENGLISH/英文  "},
};
#endif
const char ConnectPC_Title[2][20]={"连接电脑","Connect"}; 

const char *Menu_Connect_To_PC_Descrip[][2] =
{                                          
  {"返回","Back"},
};

u8 display_receive_buff[64];
u32 buff_num;
/*******************************************************************************
*******************************************************************************/
void menu_ConnectPC_display(void)
{
  
#if VCP_TEST   
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
#endif
  
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
  u8  SetTime_Data[6];
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)ConnectPC_Title[LANGUAGE]);  
  
#if VCP_TEST  
  TXM_StringDisplay(0,190,290,24,0,RED ,0, "选择");
#else
  TXM_StringDisplay(0,190,290,24,0,RED ,0, (void*)Menu_Connect_To_PC_Descrip[0][LANGUAGE]);
#endif

#if VCP_TEST  
  Para_Choice = 0;
  PS_Flag=0;  
#endif
  
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
        //激活DU  *20151023#01#*#*
        if((buff_num == 16) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[buff_num-4]==0X23) && (display_receive_buff[buff_num-3]==0X2a) && (display_receive_buff[buff_num-2]==0X23) && (display_receive_buff[buff_num-1]==0X2a))  
        {
          
              //激活时清除flash里的几个数据
              for(u8 i = 0;i<100;i++)
              {
                DuSysBuff[i] = 0;
              }
              du_sys_data_write();
              OSTimeDlyHMSM(0, 0,1,0);        
              
              validity_date = 0;
              USER_RIGHT_LEVEL = 0;
              
#if !defined(ACTIVE_NEW)          
              //存储激活码日期
              DU_SERIAL_NUMBER(8) = display_receive_buff[10] - 0x30;
              DU_SERIAL_NUMBER(9) = display_receive_buff[11] - 0x30;
                            
              for(u8 i = 0;i < 6;i++)
              {
                  DU_SERIAL_NUMBER(10 + i) = display_receive_buff[3 + i] - 0x30;             
              }
              
              DU_REGISTERED_NUMBER = 0;
              
              //设置日期
               for(u8 i = 3;i < 9; i ++)
              {
                  display_receive_buff[i] -= 0x30;
              }
              
              SetTime_Data[0] =  display_receive_buff[3]*10 + display_receive_buff[4];
              SetTime_Data[1] =  display_receive_buff[5]*10 + display_receive_buff[6];
              SetTime_Data[2] =  display_receive_buff[7]*10 + display_receive_buff[8];
              SetTime_Data[3] =  TimeBuff[3];
              SetTime_Data[4] =  TimeBuff[4];
              SetTime_Data[5] =  TimeBuff[5];
              
              RTCC_SetTime(SetTime_Data);              
 
              //清空buffer
              for(u8 i = 0;i<64;i++)
                  display_receive_buff[i] = ' ';

              GetCpuID();
              
              du_sys_data_write();
#endif              
              TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, "激活成功！");
              OSTimeDlyHMSM(0, 0,1,500);
              
              USB_Disconnect();
//              du_hardware_test();
              validity_cfg();
              break;

        }
        //进入测试模式  *#86#*
        else if((buff_num == 6) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[1]==0X23) && (display_receive_buff[2]==0X38) && (display_receive_buff[3]==0X36) 
                && (display_receive_buff[4]==0X23) && (display_receive_buff[5] == 0x2a))  
        {
              //清空buffer
              for(u8 i = 0;i<64;i++)
                  display_receive_buff[i] = ' ';
              
              TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, "进入测试模式！");
              OSTimeDlyHMSM(0, 0,1,500);
              
              USB_Disconnect();
              
              du_hardware_test();

              break;

        }  
        //校准日期时间  *#20151014*15*27*00#*
        else if((buff_num == 21) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[1]==0X23) && (display_receive_buff[10]==0x2a) && (display_receive_buff[13]==0x2a) 
                && (display_receive_buff[16]==0x2a) && (display_receive_buff[buff_num - 2]==0X23) && (display_receive_buff[buff_num - 1] == 0x2a))  
        {
          
              TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, " 校准时间！");
              
              for(u8 i = 0;i < 21; i ++)
              {
                  display_receive_buff[i] -= 0x30;
              }
              
              SetTime_Data[0] =  display_receive_buff[4]*10 + display_receive_buff[5];
              SetTime_Data[1] =  display_receive_buff[6]*10 + display_receive_buff[7];
              SetTime_Data[2] =  display_receive_buff[8]*10 + display_receive_buff[9];
              SetTime_Data[3] =  display_receive_buff[11]*10 + display_receive_buff[12];
              SetTime_Data[4] =  display_receive_buff[14]*10 + display_receive_buff[15];
              SetTime_Data[5] =  display_receive_buff[17]*10 + display_receive_buff[18];
              
              RTCC_SetTime(SetTime_Data);              
          
              //清空buffer
              for(u8 i = 0;i<64;i++)
                  display_receive_buff[i] = ' ';
                           
              
              OSTimeDlyHMSM(0, 0,1,500);
              
              USB_Disconnect();
              
              menu_time_set();
                            
              break;

        }
        //密码重置 *#CZMM#*
        else if((buff_num == 8) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[1]==0X23) && (display_receive_buff[2]==0X43) && (display_receive_buff[3]==0X5A) 
                && (display_receive_buff[4]==0X4D) && (display_receive_buff[5] == 0x4D) && (display_receive_buff[6]==0X23) && (display_receive_buff[7] == 0x2a))  
        {
            TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, " 密码重置！");
            
            DU_USER_RIGHT_PASSWORD(6) = 0;
            
            du_sys_data_write();
            
            OSTimeDlyHMSM(0, 0,1,500);
            
            USB_Disconnect();
            
            break;
        }
        //进入升级模式，跳到loader *#GJSJ#*
        else if((buff_num == 8) && (display_receive_buff[0] == 0x2a) && (display_receive_buff[1]==0X23) && (display_receive_buff[2]==0X47) && (display_receive_buff[3]==0X4A) 
                && (display_receive_buff[4]==0X53) && (display_receive_buff[5] == 0x4A) && (display_receive_buff[6]==0X23) && (display_receive_buff[7] == 0x2a))  
        {
            TXM_StringDisplay(0,20,240,16,1,YELLOW ,BLUE, " 进入升级模式！");
                        
            OSTimeDlyHMSM(0, 0,1,500);
            
            USB_Disconnect();
            
            if(((*(vu32*)(FLASH_LOADER_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
            {	 
              iap_load_app(FLASH_LOADER_ADDR);
            }
            else 
            {
//              printf("非FLASH应用程序,无法执行!\r\n");
//              TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[7][LANGUAGE]);//状态：无APP程序                   
            }	 
//            iap_load_app(FLASH_LOADER_ADDR);
            
            break;
        }        
        else
        {              
            //清空buffer
            for(u8 i = 0;i<64;i++)
                display_receive_buff[i] = ' ';
        }
      }
    }
#if VCP_TEST
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
#else
    else if((m_keydata[0] == KEY_F3) || (m_keydata[0] == KEY_ESC))
    {
      USB_Disconnect();
      break;
    }     
#endif
  }  
}

/*******************************************************************************
*******************************************************************************/
