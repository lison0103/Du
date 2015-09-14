
#include "includes.h"

/*******************************************************************************
*******************************************************************************/
void Task_Help(void)
{
  u8 *m_keydata,err,cnt=0;

  OSTimeDlyHMSM(0, 0,0,50);

  cnt=30;
  ZTM_FullScreenImageDisp(cnt);
  
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
        if(cnt<32) cnt++;else cnt = 30;
        ZTM_FullScreenImageDisp(cnt);
      }
      else if(m_keydata[0] == KEY_DOWN)
      {  
        if(cnt>30) cnt--;else cnt = 32;
        ZTM_FullScreenImageDisp(cnt);
      }  
    }  
  }  
}

/*******************************************************************************
*******************************************************************************/
