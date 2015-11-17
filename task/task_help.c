
#include "includes.h"

/*******************************************************************************
*******************************************************************************/

//@�����Ӣ�ķ���
const char *Menu_Help_Descrip1[][2] =
{                                          
  {"�������ܽ���","Key Features"},
  {"��:1 ѡ��˵�ʱ����","��:1 Select Menu Up"},
  {"   2 ��������ʱ��ǰ���ݵ���1λ","2 When you enter data in the current data Increment 1"},
  {"��:1 ѡ��˵�ʱ����","��:1 Select Menu Down"},
  {"   2 ��������ʱ��ǰ���ݵݼ�1λ","2 When you enter data in the current data is decremented 1"},
  {"��: ��������ʱ�������","��: When entering data cursor left"},
  {"��: ��������ʱ�������","��: When entering data cursor right"},
  {"SET:1 ������һ���˵�","SET:1 Enter the next level menu"},
  {"    2 ���ò���ʱ����༭״̬","2 When you set the parameters to enter edit mode"},
  {"    3 ��������ʱ����","3 Save the input data"},
  {"ESC:1 ������һ���˵�","ESC:1 Return to previous menu"},
  {"    2 ���ò���ʱ��������","2 Abort the operation when setting parameters"},
  {"    3 ��������ʱȡ������","3 Cancel the input data input"},
  {"F1/F2/F3: ������ʾ����ʾ����","F1/F2/F3: According to the display prompts"},
};

const char *Menu_Help_Descrip2[][2] =
{                                          
  {"Ӳ���汾�鿴����","Hardware version Check method"},
  {"������汾������ʾ��ECT-01-D�� ��10�в鿴","�� software version can be viewed in the display panel 10 ECT-01D menu"},
  {"��DU����������汾Ϊ2.0���ϵ�������ƥ��ʹ��","�� DU must with software version 2.0 or higher of the board to match the use"},
  {"����ʾ�尴�������м�ͷ����ΪV3.0��ʾ��","�� display panel area with the arrow keys, a display panel that is V3.0"},
  {"��ECT-01 V2.3��V3.0 ��Χ������ͬ��ԭ����ECT-01 V3.0���������ȫ����ECT-01 V2.3����","�� ECT-01 V2.3 and V3.0 the same peripheral terminals, in principle, ECT-01 V3.0 motherboard is fully compatible with ECT-01 V2.3 Motherboard"},
  {"��ECT-01 V3.0������汾ΪV3.0������","�� Software version ECT-01 V3.0 is V3.0 and higher"},
  {"��ECT-01 V2.3������汾ΪV2.6","��ECT-01 V2.3 software version is V2.6"},
};

const char *Menu_Help_Descrip3[][2] =
{                                          
  {"Կ�׿���","Key Power"},
  {"����Կ��1~3�����ɿ������ɿ���","��Play key 1-3 seconds release to open ladder"},
};

const char *Menu_Help_Descrip4[][2] =
{                                          
  {"���ϸ�λ","��Fault reset"},
  {"����ס���ƹ�λ��ť1~3�����ɿ�","��Hold down the control panel reset button is released within 1 to 3 seconds"},
  {"����ס��ʾ��SET��1~3�����ɿ�","��Press and hold the display panel SET key is released within 1 to 3 seconds"},
  {"����סDU��F1��1~3�����ɿ�","��Hold down the F1 key DU 1 to 3 seconds release"},
  {"������������ʾ��ECT-01-D��ʾ�������ӣ���ʹ��DUʱ������Ͽ���ʾ��","��Such as the motherboard and display panel ECT-01-D display panel is connected, in the use of DU, you must disconnect the display panel"},
};

const char *Menu_Help_Descrip5[][2] =
{                                          
  {"ͨ������","Communication Configuration"},
  {"������24λModbusͨ��λ�����÷����ǣ�������Ŀ��Ҫ����5����ù��ܱ�ʾΪ1��\
����Ϊ0������5�����Ϊ1�ҹ��ܲ���ͻ��ʾԶ��ͨ�����óɹ�",
"Modbus communication can be configured to 24 bits, configuration method is: according to the project needs to be set 5, \
configuration function is represented as 1 and 0 otherwise, when the 5 XOR function is 1 and does not conflict with remote \
communication configuration indicates success"},
};

const char *Menu_Help_Descrip6[][2] =
{                                          
  {"�����ָ�","Parameter recovers"},
  {"ѡ��������ݱ�Ż������ı�ţ������ѱ��ݵĲ�������ǰ�������壬�ɸ�����Ŀ�����޸����������Ӷ������������Ĳ�������",
  "Select board escalator number or parameter group number, parameter download has been backed up to the current escalator motherboard, \
a few parameters can be modified according to the project needs to quickly complete board parameter settings"},
};

//const char *Menu_Help_Descrip1[][2] =
//{                                          
//  {"�������ܽ��ܣ�","Key Features:"},
//  {"\
//��:1 ѡ��˵�ʱ����           \
//   2 ��������ʱ��ǰ���ݵ���1λ\
//��:1 ѡ��˵�ʱ����           \
//   2 ��������ʱ��ǰ���ݵݼ�1λ\
//��: ��������ʱ�������        \
//��: ��������ʱ�������        \
//SET:1 ������һ���˵�         \
//     2 ���ò���ʱ����༭״̬ \
//     3 ��������ʱ����          \
//ESC:1 ������һ���˵�         \
//     2 ���ò���ʱ��������     \
//     3 ��������ʱȡ������      \
//F1/F2/F3: ������ʾ����ʾ���� ",
//
//"��:1 Select Menu Up"},
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
