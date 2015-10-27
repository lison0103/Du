
#include "includes.h"
  
/*******************************************************************************
*******************************************************************************/
static u8 Para_Choice=0,PS_Flag=0;

const u8 *Menu_Language_Item[][2] =
{                                                           
  {" 01 中文/CHINESE  "," 01 CHINESE/中文  "},
  {" 02 英文/ENGLISH  "," 02 ENGLISH/英文  "},
};

const char Language_Title[2][20]={"语言选择","LANGUAGE"}; 

//@添加中英文翻译
const char *Menu_Language_Descrip[][2] =
{                                          
  {" 修改",
   "Alter"},
  {" 确定",
   "  OK "},
};

//@end
/*******************************************************************************
*******************************************************************************/
void menu_language_display(void)
{
  u16 i;
  
  for(i=0;i<2;i++)
  {  
    if(Para_Choice==i)
    {  
      TXM_StringDisplay(0,8,50+(i*30),24,1,YELLOW ,RED, (void*)Menu_Language_Item[i][LANGUAGE]); 
    }
    else
    {
      TXM_StringDisplay(0,8,50+(i*30),24,1,YELLOW ,BLUE, (void*)Menu_Language_Item[i][LANGUAGE]); 
    }  
      
    OSTimeDlyHMSM(0, 0,0,5); 
  }
}

/*******************************************************************************
*******************************************************************************/
void menu_language_cfg(void)
{
  u8  *m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)Language_Title[LANGUAGE]);  
//  TXM_StringDisplay(0,190,290,24,0,RED ,0, "修改");
  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)Menu_Language_Descrip[0][LANGUAGE]);

  Para_Choice = LANGUAGE;
  PS_Flag=0;  
  
  menu_language_display();
  
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

            Para_Choice = LANGUAGE;

//            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "修改");
            TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)Menu_Language_Descrip[0][LANGUAGE]);
            
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            
//            TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "修改");
            TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)Menu_Language_Descrip[0][LANGUAGE]);
            
            LANGUAGE = Para_Choice;
            du_sys_data_write();

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
//        TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "确定");
        TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)Menu_Language_Descrip[1][LANGUAGE]);
        PS_Flag = 1; 
      }
      
      menu_language_display();
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/
