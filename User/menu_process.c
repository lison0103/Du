
#include "includes.h"

/*******************************************************************************
*******************************************************************************/
const u8 *Menu_ParaItem_Descrip[][2] =
{
  {" 01 ������������ "," 01 BASE PARA CFG  "},
  {" 02 ������������ "," 02 MB INPUT CFG   "},
  {" 03 ����������� "," 03 MB OUTPUT CFG  "},
  {" 04 �϶��������� "," 04 UPPER INPUT    "},
  {" 05 �϶�������� "," 05 UPPER OUTPUT   "},
  {" 06 �¶��������� "," 06 LOWER INPUT    "},
  {" 07 �¶�������� "," 07 LOWER OUTPUT   "},
  {" 08 ��ʱ���ٶ�   "," 08 MULTI SPEED    "},
  {" 09 Զ��ͨ������ "," 09 CMS MODBUS     "},
  {" 10 ���Ϸ���     "," 10 FAULT CLASS    "},
}; 

//@
const u8 *Menu_Item_Descrip[][2] =
{                                          
  {" 01 �����ݺ�����  "," 01 ESC SN CFG    "},
  {" 02 �鿴���ϼ�¼  "," 02 FAULT LOG     "},
  {" 03 �鿴ͳ������  "," 03 STATISTICS    "},
  {" 04 ��������      "," 04 PARA SETTING  "},
  {" 05 ��������      "," 05 PARA BACKUP   "},
  {" 06 �����ָ�      "," 06 PARA RECOVER  "},
  {" 07 ʱ����������  "," 07 TIME & DATE   "},
  {" 08 �������      "," 08 USER RIGHT    "},
  {" 09 ����/LANGUAGE "," 09 LANGUAGE/���� "},
//  {" 10 ���ӵ���      "," 10 CONNECT TO PC "},
  {" 10 �汾��Ϣ      "," 10 Version       "},
}; 
//@end
u16 MenuItem=0,MenuItem_Max=0,Menu_Level=0,disFlag=0;

//@ 10Ϊ������ӵ���
#define MenuItemMax   10 
//@end

/*******************************************************************************
*******************************************************************************/
void menu_para_item_display(void)
{
  u16 i;
  
  if(disFlag)
  {
    i = MenuItem+1;
    if(i>9) i=0;
    TXM_StringDisplay(0,8,10+(i*30),24,1,OLIVE ,CYAN, (void*)Menu_ParaItem_Descrip[i][LANGUAGE]); 
    if(MenuItem) i=MenuItem-1; else i=9;
    TXM_StringDisplay(0,8,10+(i*30),24,1,OLIVE ,CYAN, (void*)Menu_ParaItem_Descrip[i][LANGUAGE]); 
     
    TXM_StringDisplay(0,8,10+(MenuItem*30),24,1,YELLOW ,RED, (void*)Menu_ParaItem_Descrip[MenuItem][LANGUAGE]); 
  }
  else
  {  
    for(i=0;i<10;i++)
    {  
      if(MenuItem==i)
      {  
        TXM_StringDisplay(0,8,10+(i*30),24,1,YELLOW ,RED, (void*)Menu_ParaItem_Descrip[i][LANGUAGE]); 
      }
      else
      {
        TXM_StringDisplay(0,8,10+(i*30),24,1,OLIVE ,CYAN, (void*)Menu_ParaItem_Descrip[i][LANGUAGE]); 
        //TXM_FillTextWidget (510+i, (void*)Menu_ParaItem_Descrip[i][LANGUAGE]);
      } 
      OSTimeDlyHMSM(0, 0,0,5); 
    }
    
    disFlag = 1;
  }  
}
//@
void menu_item_display(void)
{
  u16 i;
  
  if(disFlag)
  {
    i = MenuItem+1;
    if(i>=MenuItemMax) i=0;
    TXM_StringDisplay(0,8,20+(i*30),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
    if(MenuItem) i=MenuItem-1; else i=MenuItemMax-1;
    TXM_StringDisplay(0,8,20+(i*30),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
    
    TXM_StringDisplay(0,8,20+(MenuItem*30),24,1,YELLOW ,RED, (void*)Menu_Item_Descrip[MenuItem][LANGUAGE]); 
  }
  else
  {  
    for(i=0;i<MenuItemMax;i++)
    {  
      if(MenuItem==i)
      {  
        //TXM_FillTextWidget (533+i, (void*)Menu_Item_Descrip[i][LANGUAGE]);
        TXM_StringDisplay(0,8,20+(i*30),24,1,YELLOW ,RED, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
      }
      else
      {
        //TXM_FillTextWidget (513+i, (void*)Menu_Item_Descrip[i][LANGUAGE]);
        TXM_StringDisplay(0,8,20+(i*30),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
      }  
      
      OSTimeDlyHMSM(0, 0,0,5); 
    }
    
    disFlag = 1;
  }
}
//@end
/*******************************************************************************
*******************************************************************************/
void menu_process(void)
{
  u8 *m_keydata,err=0;
  
  MenuItem=0;
  Menu_Level=0;
  //@
  MenuItem_Max=MenuItemMax;
  //@end
  disFlag = 0;
  
  ZTM_FullScreenImageDisp(311);
  OSTimeDlyHMSM(0, 0,0,10);
  menu_item_display();
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,20000,&err);
    if((err == OS_ERR_TIMEOUT) || (m_keydata[0] == KEY_ESC))
    {
      if(!Menu_Level)
      {  
        break;
      }
      else
      {
        Menu_Level=0;
        MenuItem = 3;
        //@
        MenuItem_Max=MenuItemMax;
        //@end
        disFlag = 0;
        
        ZTM_FullScreenImageDisp(311);
        OSTimeDlyHMSM(0, 0,0,10);
        menu_item_display();
      }  
    } 
    else
    {
      if(m_keydata[0] == KEY_UP)
      {
        if(MenuItem) MenuItem--; else MenuItem = MenuItem_Max-1;
      } 
      else if(m_keydata[0] == KEY_DOWN)
      {
        MenuItem++; if(MenuItem>=MenuItem_Max) MenuItem = 0;
      }  
      else if(m_keydata[0] == KEY_SET)
      {
        if(Menu_Level==1)
        {  
          switch(MenuItem)
          {
            case 0:
              menu_para_base();
              break;
            //@��ʱ���ٶ� �ù��ܻ�û���
            case 7:
              break;
            //@end
            case 8:
              menu_comm_cfg();
              break;
            case 9:
              menu_error_cfg();
              break;
          default:
            menu_para_io(MenuItem-1);
          }  
        }
        else
        {
          switch(MenuItem)
          {
            case 0: 
              menu_sn_cfg();
              break;
            case 1:
              error_record();
              break;
            case 2:
              menu_statistic();
              break;
            case 3: //���ò���
              MenuItem=0;
              Menu_Level=1;
              MenuItem_Max=10;
              
              disFlag = 0;
              
              break;
            case 4:  
              menu_para_backup();
              break;
            case 5: 
              menu_para_restore();
              break;
            case 6: 
              menu_time_set();
              break;
            case 7: 
              //@�������
              if(USER_RIGHT_VALIDITY == 1)
              {
                menu_password_cfg();
              }
              else
              {
                validity_cfg();
              }
              //@end
              break;
            case 8: 
              menu_language_cfg();
              break;
            //@���ӵ���
            case 9:
//              menu_connect_to_pc_cfg();
              menu_version_display_cfg();
              break;
            //@end
          }
        }  
        
        ZTM_FullScreenImageDisp(311);
        OSTimeDlyHMSM(0, 0,0,10); 
        
        disFlag = 0;
      }
      
      if(Menu_Level)
      {
        menu_para_item_display();
      }  
      else
      {  
        menu_item_display();
      }  
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/