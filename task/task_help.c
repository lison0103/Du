
#include "includes.h"

/*******************************************************************************
*******************************************************************************/

//@添加中英文翻译
const char *Menu_Help_Descrip1[][2] =
{                                          
  {"按键功能介绍","Key Features"},
  {"↑:1 选择菜单时上移","↑:1 Select Menu Up"},
  {"   2 输入数据时当前数据递增1位","2 When you enter data in the current data Increment 1"},
  {"↓:1 选择菜单时下移","↓:1 Select Menu Down"},
  {"   2 输入数据时当前数据递减1位","2 When you enter data in the current data is decremented 1"},
  {"←: 输入数据时光标左移","←: When entering data cursor left"},
  {"→: 输入数据时光标右移","→: When entering data cursor right"},
  {"SET:1 进入下一级菜单","SET:1 Enter the next level menu"},
  {"    2 设置参数时进入编辑状态","2 When you set the parameters to enter edit mode"},
  {"    3 输入数据时保存","3 Save the input data"},
  {"ESC:1 返回上一级菜单","ESC:1 Return to previous menu"},
  {"    2 设置参数时放弃操作","2 Abort the operation when setting parameters"},
  {"    3 输入数据时取消输入","3 Cancel the input data input"},
  {"F1/F2/F3: 根据显示屏提示功能","F1/F2/F3: According to the display prompts"},
};

const char *Menu_Help_Descrip2[][2] =
{                                          
  {"硬件版本查看方法","Hardware version Check method"},
  {"◆软件版本可在显示板ECT-01-D菜 单10中查看","◆ software version can be viewed in the display panel 10 ECT-01D menu"},
  {"◆DU必须与软件版本为2.0以上的主板相匹配使用","◆ DU must with software version 2.0 or higher of the board to match the use"},
  {"◆显示板按键区域有箭头，即为V3.0显示板","◆ display panel area with the arrow keys, a display panel that is V3.0"},
  {"◆ECT-01 V2.3与V3.0 外围端子相同，原则上ECT-01 V3.0主板可以完全兼容ECT-01 V2.3主板","◆ ECT-01 V2.3 and V3.0 the same peripheral terminals, in principle, ECT-01 V3.0 motherboard is fully compatible with ECT-01 V2.3 Motherboard"},
  {"◆ECT-01 V3.0的软件版本为V3.0及以上","◆ Software version ECT-01 V3.0 is V3.0 and higher"},
  {"◆ECT-01 V2.3的软件版本为V2.6","◆ECT-01 V2.3 software version is V2.6"},
};

const char *Menu_Help_Descrip3[][2] =
{                                          
  {"钥匙开梯","Key Power"},
  {"◆打钥匙1~3秒内松开，即可开梯","◆Play key 1-3 seconds release to open ladder"},
};

const char *Menu_Help_Descrip4[][2] =
{                                          
  {"故障复位","◆Fault reset"},
  {"◆按住控制柜复位按钮1~3秒内松开","◆Hold down the control panel reset button is released within 1 to 3 seconds"},
  {"◆按住显示板SET键1~3秒内松开","◆Press and hold the display panel SET key is released within 1 to 3 seconds"},
  {"◆按住DU的F1键1~3秒内松开","◆Hold down the F1 key DU 1 to 3 seconds release"},
  {"◆如主板与显示板ECT-01-D显示板已连接，在使用DU时，必须断开显示板","◆Such as the motherboard and display panel ECT-01-D display panel is connected, in the use of DU, you must disconnect the display panel"},
};

const char *Menu_Help_Descrip5[][2] =
{                                          
  {"通信配置","Communication Configuration"},
  {"可配置24位Modbus通信位，配置方法是：根据项目需要设置5项，配置功能表示为1，\
否则为0，当此5项异或为1且功能不冲突表示远程通信配置成功",
"Modbus communication can be configured to 24 bits, configuration method is: according to the project needs to be set 5, \
configuration function is represented as 1 and 0 otherwise, when the 5 XOR function is 1 and does not conflict with remote \
communication configuration indicates success"},
};

const char *Menu_Help_Descrip6[][2] =
{                                          
  {"参数恢复","Parameter recovers"},
  {"选择主板扶梯编号或参数组的编号，下载已备份的参数到当前扶梯主板，可根据项目需求修改少数参数从而快速完成主板的参数设置",
  "Select board escalator number or parameter group number, parameter download has been backed up to the current escalator motherboard, \
a few parameters can be modified according to the project needs to quickly complete board parameter settings"},
};

//const char *Menu_Help_Descrip1[][2] =
//{                                          
//  {"按键功能介绍：","Key Features:"},
//  {"\
//↑:1 选择菜单时上移           \
//   2 输入数据时当前数据递增1位\
//↓:1 选择菜单时下移           \
//   2 输入数据时当前数据递减1位\
//←: 输入数据时光标左移        \
//→: 输入数据时光标右移        \
//SET:1 进入下一级菜单         \
//     2 设置参数时进入编辑状态 \
//     3 输入数据时保存          \
//ESC:1 返回上一级菜单         \
//     2 设置参数时放弃操作     \
//     3 输入数据时取消输入      \
//F1/F2/F3: 根据显示屏提示功能 ",
//
//"↑:1 Select Menu Up"},
//};

//@end
u8 ITEM_PAGE = 0;
#define HELP_ITEM_MAX 5
void Menu_Help_Display(u8 item,u8 page)
{
    ZTM_FullScreenImageDisp(40);
    
    switch(item)
    {
      case 0:
        if(LANGUAGE)
        {            
            TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[0][1]);
            OSTimeDlyHMSM(0, 0,0,10);
            
            if(0 == page)
            {
              for(u8 i = 1;i<7;i++)
              {
                TXM_StringDisplay(0,0,40+i*32,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[i][1]);
                OSTimeDlyHMSM(0, 0,0,10);
              }
              ITEM_PAGE = 1;
            }
            else if(1 == page)
            {
              for(u8 i = 7;i<13;i++)
              {
                TXM_StringDisplay(0,0,40+(i-6)*32,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[i][1]);
                OSTimeDlyHMSM(0, 0,0,10);
              }
              ITEM_PAGE = 0;
            }
        }
        else
        {
            TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[0][0]);
            OSTimeDlyHMSM(0, 0,0,10);
            
            for(u8 i = 1;i<13;i++)
            {
              TXM_StringDisplay(0,0,64+i*18,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[i][0]);
              OSTimeDlyHMSM(0, 0,0,10);
            }  
            ITEM_PAGE = 0;
//            TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[0][0]);
//            OSTimeDlyHMSM(0, 0,0,10);
//            
//
//              TXM_StringDisplay(0,0,82,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip1[1][0]);
//              OSTimeDlyHMSM(0, 0,0,10);
                   
        }
                                                                                  
        break;
    case 1:
      if(LANGUAGE)
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[0][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          if(0 == page)
          {
            for(u8 i = 1;i<4;i++)
            {
              TXM_StringDisplay(0,0,100+(i-1)*80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[i][1]);
              OSTimeDlyHMSM(0, 0,0,10);
            }
            ITEM_PAGE = 1;
          }
          else if(1 == page)
          {
            for(u8 i = 4;i<7;i++)
            {
              TXM_StringDisplay(0,0,100+(i-4)*80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[i][1]);
              OSTimeDlyHMSM(0, 0,0,10);
            }
            ITEM_PAGE = 0;
          }           
      }
      else
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[0][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          if(0 == page)
          {
            for(u8 i = 1;i<6;i++)
            {
              TXM_StringDisplay(0,0,80+(i-1)*48,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[i][0]);
              OSTimeDlyHMSM(0, 0,0,10);
            }
            ITEM_PAGE = 1;
          }
          else if(1 == page)
          {
            for(u8 i = 6;i<7;i++)
            {
              TXM_StringDisplay(0,0,80+(i-6)*48,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip2[i][0]);
              OSTimeDlyHMSM(0, 0,0,10);
            } 
            ITEM_PAGE = 0;
          }
      }
      break;
    case 2:
      if(LANGUAGE)
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip3[0][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip3[1][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;        
      }
      else
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip3[0][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip3[1][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;
      }
      break;
      
    case 3:
      if(LANGUAGE)
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip4[0][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          if(0 == page)
          {
            for(u8 i = 1;i<4;i++)
            {
              TXM_StringDisplay(0,0,100+(i-1)*80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip4[i][1]);
              OSTimeDlyHMSM(0, 0,0,10);
            }
            ITEM_PAGE = 1;
          }
          else if(1 == page)
          {
            for(u8 i = 4;i<5;i++)
            {
              TXM_StringDisplay(0,0,100+(i-4)*80,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip4[i][1]);
              OSTimeDlyHMSM(0, 0,0,10);
            }
            ITEM_PAGE = 0;
          }         
      }
      else
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip4[0][0]);
          OSTimeDlyHMSM(0, 0,0,10);
                    
          for(u8 i = 1;i<5;i++)
          {
            TXM_StringDisplay(0,0,80+(i-1)*48,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip4[i][0]);
            OSTimeDlyHMSM(0, 0,0,10);
          }
          ITEM_PAGE = 0;     
      }
      break;
    case 4:
      if(LANGUAGE)
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip5[0][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,100,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip5[1][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;        
      }
      else
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip5[0][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,100,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip5[1][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;
      }
      break;
    case 5:
      if(LANGUAGE)
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip6[0][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,100,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip6[1][1]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;        
      }
      else
      {
          TXM_StringDisplay(0,0,40,24,0,BLACK ,BLACK, (void*)Menu_Help_Descrip6[0][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          TXM_StringDisplay(0,0,100,16,0,BLACK ,BLACK, (void*)Menu_Help_Descrip6[1][0]);
          OSTimeDlyHMSM(0, 0,0,10);
          
          ITEM_PAGE = 0;
      }
      break;
    default:
      break;
    }
}

void Task_Help(void)
{
  u8 *m_keydata,err;
  s8 cnt=0;

  OSTimeDlyHMSM(0, 0,0,50);

  Menu_Help_Display(0,0);
  
  while(1)
  {    
    m_keydata = OSMboxPend(KeyMbox,20000,&err);
    if((err == OS_ERR_TIMEOUT) || (m_keydata[0] == KEY_ESC))
    {
      break;
    }  
    else
    {
      if(m_keydata[0] == KEY_UP)
      {
          cnt--;
          if(cnt < 0)
          { 
            cnt = HELP_ITEM_MAX;          
          }

          Menu_Help_Display(cnt,0);
      }
      else if(m_keydata[0] == KEY_DOWN)
      { 
        if(ITEM_PAGE != 1)
        {
            cnt++;
            if(cnt > HELP_ITEM_MAX)
            { 
              cnt = 0;          
            }
        }
        Menu_Help_Display(cnt,ITEM_PAGE);
      }  
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/
