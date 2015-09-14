
#include "includes.h"

#define Null      0
#define IOMenu_Num 17

#define DEBUG_Num 20

#define iobuff    gsIOarray.pBuff

#define CurrentItemNumber  UserChoose

typedef struct menuitem        
{
//  u8 MenuLevel;          
  
  u8 MenuCount;        

  u8 low1; 
  u8 *DisplayString1[2];
  
  u8 low2;
  u8 *DisplayString2[2];     

  void (*Subs)();                       
  
  const struct menuitem *ChildrenMenus;                                      
  const struct menuitem *ParentMenus;  
                                      
}MenuItem;   

typedef struct iocgc
{
  u8 number;
  u8 eepadr;
  u8 dmax;  
}IOCGC;

typedef struct menudisdata
{
  const u8 *distext[2]; 
  u32 *pdata;
}sMenuDisData;


void NullSubs(void) {};

OS_EVENT *msgEvent_Menu;
static u8 *m_keydata;

/*******************************************************************************
*******************************************************************************/
u16 menu_flag=0;

u16 menu_level=0,menu_picture=0;
u16 menuItemNumber=0;

const u16 HelpArrayPictureIndex[] = {31,32,30}; 
const u16 MenuArrayPictureIndex[] = {101,102,103,104,105,106,107,100,108,109,110,111,112,113,114,115};

u16 HelpArrayNumber=0,MenuArrayNumber=0;

static u16 DisplayPictureNumber=20;

void passwordcheck(void);

u8 TimeBuff[6];

/*******************************************************************************            
*******************************************************************************/           

/*******************************************************************************  ParaSetMenu	0
*******************************************************************************/
const MenuItem MainMenu[]=
{
  { 10, 1,"��ѡ��: �˵� 01 ", "Select-> Menu 01",2,"--->    �������"," INPUT/OUTPUT   ",NullSubs,Null, Null},// IOMenu
  { 10, 1,"��ѡ��: �˵� 02 ", "Select-> Menu 02",2,"--->    ʵʱ����"," REALTIME DATA  ",NullSubs,Null, Null},// DebugMenu 
  { 10, 1,"��ѡ��: �˵� 03 ", "Select-> Menu 03",2,"--->    ͳ������"," STATISTIC DATA ",NullSubs,Null, Null},// Statmenu
  { 10, 1,"��ѡ��: �˵� 04 ", "Select-> Menu 04",2,"--->    ���ϼ�¼"," FAULT RECODE   ",NullSubs,Null, Null},// LogMenu  
  { 10, 1,"��ѡ��: �˵� 05 ", "Select-> Menu 05",2,"--->    Ӧ������"," UTILY CONFIG   ",NullSubs,Null, Null},// CfgMenu
  { 10, 1,"��ѡ��: �˵� 06 ", "Select-> Menu 06",2,"--->    ͨ������"," COMM CONFIG    ",passwordcheck,Null, Null},//CommMenu  
  { 10, 1,"��ѡ��: �˵� 07 ", "Select-> Menu 07",2,"--->    �鿴����"," VIEW PARAMETER ",NullSubs,Null, Null},// ParaViewMenu
  { 10, 1,"��ѡ��: �˵� 08 ", "Select-> Menu 08",2,"--->    ���ò���"," SET PARAMETER  ",passwordcheck,Null, Null},// ParaSetMenu
  { 10, 1,"��ѡ��: �˵� 09 ", "Select-> Menu 09",2,"--->    ��������"," BACKUP/RESET   ",passwordcheck,Null, Null},// BackupMenu 
  { 10, 1,"��ѡ��: �˵� 10 ", "Select-> Menu 10",2,"--->    �汾��Ϣ"," ABOUT          ",NullSubs,Null, Null},// about_display
};		  

/*******************************************************************************
*******************************************************************************/
void passwordcheck(void)
{
  
}

/*******************************************************************************
*******************************************************************************/
void menu_display(void)
{
  
}

/*******************************************************************************
*******************************************************************************/
void Display_MenuItem(void)
{
  ZTM_FullScreenImageDisp(DisplayPictureNumber);
}

/*******************************************************************************
*******************************************************************************/
void menu_processa(void)
{ 
  if(menu_flag==0)
  {  
    if(m_keydata[0] == KEY_F2)
    {
      ZTM_SetCartoon (1,0,0,0, 0,180, 100,0, 0);
      
      menu_flag = 2;
      MenuArrayNumber=0; 
      DisplayPictureNumber = MenuArrayPictureIndex[MenuArrayNumber];
    }  
    //�����˵�
    else if(m_keydata[0] == KEY_F3)
    {
      ZTM_SetCartoon (1,0,0,0, 0,180, 100,0, 0);
      
      menu_flag = 3;
      HelpArrayNumber=0; 
      DisplayPictureNumber = HelpArrayPictureIndex[HelpArrayNumber];
    }
  }
  else if(menu_flag==0x12)
  {
    if(m_keydata[0] == KEY_DOWN)
    {
      menuItemNumber++;
      if(MenuArrayNumber>35) MenuArrayNumber = 0;
    }  
    else if(m_keydata[0] == KEY_UP)
    {
      if(menuItemNumber) menuItemNumber--;else menuItemNumber=35;
    }  
  }  
  else if(menu_flag==2)
  {
    if(m_keydata[0] == KEY_DOWN)
    {
      MenuArrayNumber++;
      if(MenuArrayNumber>15) MenuArrayNumber = 0;
      DisplayPictureNumber = MenuArrayPictureIndex[MenuArrayNumber];
    }  
    else if(m_keydata[0] == KEY_UP)
    {
      if(MenuArrayNumber>0) MenuArrayNumber--;else MenuArrayNumber=15;
      DisplayPictureNumber = MenuArrayPictureIndex[MenuArrayNumber];
    }  
    else if(m_keydata[0] == KEY_ESC)
    {
      DisplayPictureNumber = 0;
      menu_flag = 0;
    }  
    else if(m_keydata[0] == KEY_SET)
    {
      if(MenuArrayNumber==0)
      {
        error_record();
      }  
      else if(MenuArrayNumber>=8)
      {  
        para_setup(MenuArrayNumber-8);
      }  
    }  
  } 
  else if(menu_flag==3)
  {
    if(m_keydata[0] == KEY_DOWN)
    {
      HelpArrayNumber++;
      if(HelpArrayNumber>2) HelpArrayNumber = 0;
      DisplayPictureNumber = HelpArrayPictureIndex[HelpArrayNumber];
    }  
    else if(m_keydata[0] == KEY_UP)
    {
      if(HelpArrayNumber>0) HelpArrayNumber--;else HelpArrayNumber=2;
      DisplayPictureNumber = HelpArrayPictureIndex[HelpArrayNumber];
    }  
    else if(m_keydata[0] == KEY_ESC)
    {
      DisplayPictureNumber = 0;
      menu_flag = 0;
    }  
  } 
}

/*******************************************************************************
*******************************************************************************/
void Task_Menu(void *p_arg)
{
  (void)p_arg; 

  OSTimeDlyHMSM(0, 0,0,500);

  RTCC_Init();
  
  while (1) 
  {  
    //m_keydata = OSMboxPend(KeyMbox,0,&err);  
    OSTimeDlyHMSM(0, 0,0,500);  
    
    RTCC_GetTime(TimeBuff);
  } 
}

/*******************************************************************************
*******************************************************************************/

