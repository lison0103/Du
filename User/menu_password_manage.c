/****************************************Copyright (c)****************************************************
** File Name:           menu_password_manage.c
** Created By:          lisonchen
** Created date:        2015-09-15
** Version:             v1.00
** Descriptions:        密码管理菜单
**
*********************************************************************************************************/
#include "includes.h"

#define PASS_DES_MAX  10
#define PASS_LEN      6
  
/*******************************************************************************
*******************************************************************************/

static u8 *PASS_Buff,PASS_Temp[20],PASS_NUMBER[20],Para_Cnum=0; 
static u8 Para_Choice=0,PS_Flag=0;

static char const Password_Code[11] = {"-0123456789"};
                                    
const char Password_Title[2][20]={"密码管理","USER RIGHT"}; 
const char *input_item[][2]={
  {" 输入","Input"},{" 确定","  OK "},{" 修改","Alter"},{"擦除","Earse"},{"正在擦除数据...","Erasing data..."},
  {"   擦除完成!   "," Erase finish! "},
  {"剩余使用天数: ",
  "Validity Date:"},
  {"验证码：",
  "PIN:    "},
  {"  请输入旧密码：   ",
   "Enter Old Password:"},
  {"  请输入新密码：   ",
   "Enter New Password:"},
  {" 请再次输入新密码：",
   "Repeat Enter New:  "},
  {" 密码修改成功 ",
   "successfully"},
  {" 密码修改失败 ",
   " fails "},
  {" 密码正确 ",//13
   " Correct "},
  {" 密码错误 ",
   " Wrong "}
}; 

u8 USER_RIGHT_LEVEL = 0;
u8 Temp[] = "------";
u8 SN[16];
const u8 *Version = {"V1.2.2"};
u8 Set_Flag = 0;
u8 EARSE_CHIP = 0;
extern u8 m_buff_temp[3];
u8 ChangePassword_Flag = 0;
s8 HW_TEST_FLAG = 0;
extern void du_hardware_test(void);
/*******************************************************************************
*******************************************************************************/
void menu_password_display(u8 set_bit)
{  
  char i,a[20];
  
  if(set_bit)
  {
    set_bit--;
    for(i=0;i<set_bit;i++)
    {
      a[i] = PASS_Temp[i];
      
      if( '-' != a[i])
          a[i] = '*';
    }  
    a[set_bit] = 0;
    TXM_StringDisplay(0,70,130,32,1,BLACK,LGRAY, (void*)a);  

    
    a[0] = PASS_Temp[set_bit];
    a[1] = 0;
    TXM_StringDisplay(0,70+(set_bit*16),130,32,1,YELLOW,RED, (void*)a);  

    for(;i<PASS_LEN-1;i++)
    {
      a[i-set_bit] = PASS_Temp[i+1];
      if( '-' != a[i-set_bit])
        a[i-set_bit] = '*';
    }  
    a[i-set_bit] = 0;
    TXM_StringDisplay(0,86+(set_bit*16),130,32,1,BLACK,LGRAY, (void*)a);  
  }
  else
  {  
    PASS_Temp[PASS_LEN] = 0;
    for(i=0;i<PASS_LEN;i++)
    {
      a[i] = PASS_Temp[i];
      
      if( '-' != a[i])
        a[i] = '*';
    }  
    a[PASS_LEN] = 0;
    TXM_StringDisplay(0,70,130,32,1,BLACK,LGRAY, (void*)a);
//    TXM_StringDisplay(0,70,130,32,1,BLACK,LGRAY, (void*)PASS_Temp);
  }  
}

u8 get_password_num(u8 dat)
{
  u8 i,cnt=0;
  
  for(i=0; i<PASS_DES_MAX; i++)
  {
    if(dat == Password_Code[i])
    {
      cnt = i;
      break;
    }            
  }  
  
  return(cnt);
}

/*******************************************************************************
*******************************************************************************/
void menu_password_cfg(void)
{
  u8  i,*m_keydata,err=0;
  u8  exitcount = 0;
  u8  inputerror = 0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  OSTimeDlyHMSM(0, 0,0,10);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)Password_Title[LANGUAGE]);  
  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0][LANGUAGE]);//输入
  TXM_StringDisplay(0,120,290,24,1,RED ,BLACK, (void*)input_item[2][LANGUAGE]);//修改
  
  TXM_StringDisplay(0,5,45,16,0,BLACK ,BLACK, (void*)Version);//版本
  TXM_StringDisplay(0,5,260,16,0,BLACK ,BLACK, (void*)input_item[7][LANGUAGE]);//序列号
  
  for(u8 i = 0;i < 16;i++)
  {
    SN[i] = DU_SERIAL_NUMBER(i) + 0x30;
  }
  
  TXM_StringDisplay(0,70,260,16,0,BLACK ,BLACK, (void*)SN);//
  

  TXM_StringDisplay(0,5,240,16,0,BLACK ,BLACK, (void*)input_item[6][LANGUAGE]);//剩余使用天数
  
//  validity_date = 180 - VALIDITY_USE_DATE;
  m_buff_temp[0] = validity_date/100 + 0x30;
  m_buff_temp[1] = validity_date%100/10 + 0x30;
  m_buff_temp[2] = validity_date%10 + 0x30;
  TXM_StringDisplay(0,125,240,16,0,BLACK ,BLACK, (void*)m_buff_temp);//天
  
  if(DU_USER_RIGHT_PASSWORD(6) == 1)
  {
      for(u8 i=0;i<6;i++)
      {
        PASS_NUMBER[i] = DU_USER_RIGHT_PASSWORD(i);
      }
  }
  else
  {
      for(u8 i=0;i<6;i++)
      {
        DU_USER_RIGHT_PASSWORD(i) = i + 0x30;   
        PASS_NUMBER[i] = DU_USER_RIGHT_PASSWORD(i);
      }
      DU_USER_RIGHT_PASSWORD(6) = 1;
      du_sys_data_write();
  }
  
  PASS_Buff = Temp;
  
  for(i=0;i<6;i++)
  {
    PASS_Temp[i] = PASS_Buff[i];
  }  
  
  Para_Choice=0;
  PS_Flag=0;  
  
  menu_password_display(Para_Choice);

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////while(1)///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,500,&err);
    
    if(err == OS_ERR_TIMEOUT)
    {
        for(i=0;i<6;i++)
        {
            if( '-' != PASS_Temp[i])
              TXM_StringDisplay(0,70+i*16,130,32,1,BLACK,LGRAY, "*");  
        } 
        exitcount++;
        if(exitcount > 12)
        {
            exitcount = 0;
            EARSE_CHIP = 0;
            ChangePassword_Flag = 0;
            inputerror = 0;
            break;
        }
    } 
    else if((!PS_Flag) && (m_keydata[0] == KEY_ESC))
    {
        EARSE_CHIP = 0;
        ChangePassword_Flag = 0;
        exitcount = 0;
        inputerror = 0;
        HW_TEST_FLAG = 0;
        break;
    }
#if DU_FOR_TEST
    //擦除有效期管理的几个数据
    else if(EARSE_CHIP == 1)
    {
      if(m_keydata[0]==KEY_F1)
      {       
        EARSE_CHIP = 0;
        TXM_StringDisplay(0,40,200,24,1,YELLOW ,RED, (void*)input_item[4][LANGUAGE]);//正在擦除数据...
        
        for(u8 i = 0;i<100;i++)
        {
          DuSys_Data[i] = 0;
        }
        du_sys_data_write();
        OSTimeDlyHMSM(0, 0,1,0);        
        
        validity_date = 0;
//        SPI_W25X_ChipErase();

        TXM_StringDisplay(0,40,200,24,1,YELLOW ,RED, (void*)input_item[5][LANGUAGE]);//擦除完成!
        OSTimeDlyHMSM(0, 0,2,0);
        break;
      }     
    }
#endif    
    else 
    {
      exitcount = 0;
      
      if(PS_Flag)
      {
          switch(m_keydata[0])
          {
            case KEY_ESC:
              
              PS_Flag = 0;
              
              ChangePassword_Flag = 0;

              for(i=0;i<PASS_LEN;i++)
              {
                PASS_Temp[i] = PASS_Buff[i];
              }  
              
              Para_Choice=0;
              TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0][LANGUAGE]);//输入
              
              TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, "                     ");
              TXM_StringDisplay(0,0,180,24,1,YELLOW ,LGRAY,  "                              ");
              
              break; 
            case KEY_SET:
            case KEY_F3:  
              if(ChangePassword_Flag != 0)
              {
                  for(int j=0;j<PASS_LEN;j++)
                  {                  
                      if( '-' == PASS_Temp[j])
                      {
                          inputerror = 1;
                          if(LANGUAGE) TXM_StringDisplay(0,5,180,16,1,YELLOW ,RED,  "Please enter the 6 digit code");
                          else TXM_StringDisplay(0,15,180,24,1,YELLOW ,RED,  "请输入6位数字密码");
                          break;
                      }
                  }               
                  if(0 == inputerror)
                  {
                    PS_Flag = 0;
                    Set_Flag = 1;
                    Para_Choice=0;                            
                  }
                  inputerror = 0;
              }
              else
              {                               
                  PS_Flag = 0;
                  Set_Flag = 1;
                  Para_Choice=0;
                  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0][LANGUAGE]);//输入                
              }
              break; 
              
            case KEY_UP:              
              if(Para_Cnum < PASS_DES_MAX) Para_Cnum++; else Para_Cnum=0;
              PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
              TXM_StringDisplay(0,0,180,24,1,YELLOW ,LGRAY,  "                              ");
              break; 
            case KEY_DOWN:              
              if(Para_Cnum) Para_Cnum--;else Para_Cnum=PASS_DES_MAX;
              PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
              TXM_StringDisplay(0,0,180,24,1,YELLOW ,LGRAY,  "                              ");
              break; 
            case KEY_LEFT:
              if(Para_Choice>1) Para_Choice--; 
              else Para_Choice = PASS_LEN; 
              Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
              TXM_StringDisplay(0,0,180,24,1,YELLOW ,LGRAY,  "                              ");
              break; 
            case KEY_RIGHT:
              if(Para_Choice<PASS_LEN) Para_Choice++;
              else Para_Choice = 1; 
              Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
              TXM_StringDisplay(0,0,180,24,1,YELLOW ,LGRAY,  "                              ");
              break; 
          }  
      } 
      else if((m_keydata[0]==KEY_F2) || (m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
          HW_TEST_FLAG = 0;
          
          if(m_keydata[0]==KEY_F2)
          {
              TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, (void*)input_item[8][LANGUAGE]);
              ChangePassword_Flag = 1;
          }
        
          Para_Choice = 1;
          Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
          
          TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[1][LANGUAGE]);//确认
          TXM_StringDisplay(0,50,180,24,1,BLACK ,LGRAY, "               ");
          PS_Flag = 1; 
          
          PASS_Buff = Temp;
          
          for(i=0;i<6;i++)
          {
            PASS_Temp[i] = PASS_Buff[i];
          } 
      }
      else if((m_keydata[0] == KEY_F1) || (m_keydata[0] == KEY_UP) || (m_keydata[0] == KEY_DOWN))
      {
          if(m_keydata[0] == KEY_F1)
          {
              if(HW_TEST_FLAG == 0 || HW_TEST_FLAG == 1 || HW_TEST_FLAG == 4)
                HW_TEST_FLAG++;
              else
                HW_TEST_FLAG = 0;
              
              if(HW_TEST_FLAG == 5)
              {
                HW_TEST_FLAG = 0;
                du_hardware_test();
                break;
              }
          }
          else if(m_keydata[0] == KEY_UP)
          {
              if(HW_TEST_FLAG == 3)
                HW_TEST_FLAG++;
              else
                HW_TEST_FLAG = 0;
          }
          else if(m_keydata[0] == KEY_DOWN)
          {
              if(HW_TEST_FLAG == 2)
                HW_TEST_FLAG++;
              else
                HW_TEST_FLAG = 0;
          }
      }
      else
      {
          HW_TEST_FLAG = 0;
      }
     
      menu_password_display(Para_Choice);
      
      //验证密码是否正确
      if(Set_Flag)
      {
            Set_Flag = 0;
            if( PASS_Temp[0] == DU_USER_RIGHT_PASSWORD(0) && PASS_Temp[1] == DU_USER_RIGHT_PASSWORD(1) && PASS_Temp[2] == DU_USER_RIGHT_PASSWORD(2) 
               && PASS_Temp[3] == DU_USER_RIGHT_PASSWORD(3) && PASS_Temp[4] == DU_USER_RIGHT_PASSWORD(4) && PASS_Temp[5] == DU_USER_RIGHT_PASSWORD(5) )//权限2密码
            {
                if(ChangePassword_Flag)//修改密码模式
                {
                    ChangePassword_Flag = 2;
                    
                    Para_Choice = 1;
                    Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
                    
                    TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[1][LANGUAGE]);//确认
                    PS_Flag = 1; 
                                    
                    TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, (void*)input_item[9][LANGUAGE]);
                }
                else
                {
                    USER_RIGHT_LEVEL = 2;
                    DU_USER_RIGHT_LEVEL = 2;
                    DU_INPUT_PASS_DATE(0) = TimeBuff[2];
                    DU_INPUT_PASS_DATE(1) = TimeBuff[3];
                    du_sys_data_write();
                    TXM_StringDisplay(0,65,180,24,1,YELLOW ,RED,  (void*)input_item[13][LANGUAGE]);
                    OSTimeDlyHMSM(0, 0,1,0);
                    break;
                }
            }
            else if( PASS_Temp[0] == (3 + 0x30) && PASS_Temp[1] == (2 + 0x30) && PASS_Temp[2] == (1 + 0x30) 
                    && PASS_Temp[3] == (3 + 0x30) && PASS_Temp[4] == (1 + 0x30) && PASS_Temp[5] == (2 + 0x30) )//权限1密码
            {
                USER_RIGHT_LEVEL = 1;
                DU_USER_RIGHT_LEVEL = 1;
                DU_INPUT_PASS_DATE(0) = TimeBuff[2];
                DU_INPUT_PASS_DATE(1) = TimeBuff[3];
                du_sys_data_write();
                TXM_StringDisplay(0,65,180,24,1,YELLOW ,RED,  (void*)input_item[13][LANGUAGE]);
                OSTimeDlyHMSM(0, 0,1,0);
                break;
            }
    #if DU_FOR_TEST
            //打开擦除数据隐藏功能
            else if( PASS_Temp[0] == (0 + 0x30) && PASS_Temp[1] == (0 + 0x30) && PASS_Temp[2] == (0 + 0x30) 
                    && PASS_Temp[3] == (0 + 0x30) && PASS_Temp[4] == (0 + 0x30) && PASS_Temp[5] == (0 + 0x30) )
            {
                EARSE_CHIP = 1;
                ZTM_RectangleFill (0,280,239,319,BLACK);
                OSTimeDlyHMSM(0, 0,0,10);
                TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, (void*)input_item[6][LANGUAGE]);//擦除
            }
    #endif
            else if(ChangePassword_Flag == 2)//保存第一次输入的新密码
            {
                ChangePassword_Flag = 3;
                for(u8 i=0;i<6;i++)
                {
                  PASS_NUMBER[i] = PASS_Temp[i];
                }
                
                
                Para_Choice = 1;
                Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
                
                TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[1][LANGUAGE]);//确认
                PS_Flag = 1; 
                          
                TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, (void*)input_item[10][LANGUAGE]);
            }
            else if(ChangePassword_Flag == 3)
            {
              //两次输入密码一致，保存新密码
              
              if( PASS_Temp[0] == PASS_NUMBER[0] && PASS_Temp[1] == PASS_NUMBER[1] && PASS_Temp[2] == PASS_NUMBER[2] 
                 && PASS_Temp[3] == PASS_NUMBER[3] && PASS_Temp[4] == PASS_NUMBER[4] && PASS_Temp[5] == PASS_NUMBER[5] )
              {
                  for(u8 i=0;i<6;i++)
                  {
                      PASS_NUMBER[i] = PASS_Temp[i];
                      DU_USER_RIGHT_PASSWORD(i) = PASS_Temp[i];
                  }
                  du_sys_data_write();
                  ChangePassword_Flag = 0;
                  TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, "                     ");
                  TXM_StringDisplay(0,60,180,24,1,YELLOW ,RED,  (void*)input_item[11][LANGUAGE]);
                  
                  OSTimeDlyHMSM(0, 0,1,0);
                  PS_Flag = 0;
                  Para_Choice=0;
                  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0][LANGUAGE]);//输入  
                  
              }
              else//两次输入密码不一样
              {
                  ChangePassword_Flag = 0;
                  TXM_StringDisplay(0,50,100,16,1,BLACK ,LGRAY, "                      ");
                  TXM_StringDisplay(0,60,180,24,1,YELLOW ,RED,  (void*)input_item[12][LANGUAGE]);
                  
                  OSTimeDlyHMSM(0, 0,1,0);
                  PS_Flag = 0;
                  Para_Choice=0;
                  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0][LANGUAGE]);//输入               
              }
              
            }           
            else//输入密码错误
            {
                USER_RIGHT_LEVEL = 0;
                if(DU_USER_RIGHT_LEVEL > 0)
                {            
                    DU_USER_RIGHT_LEVEL = 0;
                    DU_INPUT_PASS_DATE(0) = 0;
                    DU_INPUT_PASS_DATE(1) = 0;
                    du_sys_data_write();
                }
                TXM_StringDisplay(0,65,180,24,1,YELLOW ,RED,  (void*)input_item[14][LANGUAGE]);
                OSTimeDlyHMSM(0, 0,1,0);
                
                if(ChangePassword_Flag != 0)
                {
                    Para_Choice = 1;
                    Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
                    PS_Flag = 1; 
                }
                
            }
            
            TXM_StringDisplay(0,50,180,24,1,BLACK ,LGRAY, "                 ");
            PASS_Buff = Temp;
            
            for(i=0;i<6;i++)
            {
              PASS_Temp[i] = PASS_Buff[i];
            }           
            
            menu_password_display(Para_Choice); 
      }
      
    }  

  }  
}

/*******************************************************************************
*******************************************************************************/
