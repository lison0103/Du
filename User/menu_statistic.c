
#include "includes.h"

/*******************************************************************************
*******************************************************************************/
typedef struct statitem 
{
  u8 id;
  u16 addr;
  u16 wid;  
}Stat_Item;


const Stat_Item StatItem[8]=
{
  {1,256,330},
  {2,257,331},
  {3,258,332},
  {4,259,333},
  {5,260,334},
  {6,261,335},
  {7,262,336},
  {8,263,337}
};

const char STAT_DescripBuff[][2][21]={           	
                  
	{{"���п���           h"}, {"Fast up            h"}},
	{{"��������           h"}, {"Slow up            h"}},
	{{"���м�Ъ           h"}, {"Int. up            h"}},	 
	{{"���п���           h"}, {"Fast down          h"}},	 
	{{"��������           h"}, {"Slow down          h"}},	 
	{{"���м�Ъ           h"}, {"Int. down          h"}},	 	 
	{{"��ͣ����            "}, {"EMERG. stop         "}},	 	 
	{{"���ϴ���            "}, {"Fault number        "}},	 	 	 
};

/*******************************************************************************
*******************************************************************************/
void display_stat_data(void)
{
  u16 i;
  
  for(i=0;i<8;i++)
  {  
    TXM_DigitDisplay(StatItem[i].wid,0,0,24,0,0,0,pt_ModBuff[StatItem[i].addr],6,0,ALIGN_RIGHT);
  }
}

void delete_state_display(void)
{
    display_stat_data();
    OSTimeDlyHMSM(0, 0,0,10); 
}  

/*******************************************************************************
*******************************************************************************/
void menu_statistic(void)
{
  u8 *m_keydata,err=0;
  
  u16 i;
  
  ZTM_FullScreenImageDisp(310);
  
  OSTimeDlyHMSM(0, 0,0,100); 
  for(i=0;i<8;i++)
  {  
    TXM_FillTextWidget (320+i, (void*)STAT_DescripBuff[i][LANGUAGE]);
    OSTimeDlyHMSM(0, 0,0,50); 
  }
  ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
  TXM_StringDisplay(0,192,290,24,0,RED ,WHITE, "ɾ��"); 
  
  delete_state_display();
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,50,&err);
    if(err == OS_ERR_TIMEOUT)
    {
      display_stat_data();
    } 
    else if(m_keydata[0] == KEY_ESC)
    {
      break;
    }  
  }
}

/*******************************************************************************
*******************************************************************************/
