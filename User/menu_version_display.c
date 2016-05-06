
#include "includes.h"
  
/*******************************************************************************
*******************************************************************************/
static u8 Para_Choice=0,PS_Flag=0;

u8  version_str[20] = {0};

const u8 *Menu_Version_Display_Item[][2] =
{                                                           
  {" DU 版本   "," DU   "},
  {" 主板VC 版本   "," ECTA VC   "},
  {" 主板VB 版本   "," ECTA VB   "},
  {" 扩展板上 版本   "," ECTB UP   "},
  {" 扩展板下 版本   "," ECTB DOWN   "},
};

const char Version_Display_Title[2][20]={"版本信息 ","Version "}; 


const char *Menu_Version_Display_Descrip[][2] =
{                                          
  {" 返回",
   " Back"},
};

/*******************************************************************************
*******************************************************************************/
void Version_Converter(u8 *version, u8 dat) 
{
    u8 temp_ay[5];
    
    
    temp_ay[0] = dat/100 + 0x30;
    temp_ay[1] = (dat%100)/10 + 0x30;
    temp_ay[2] = dat%10 + 0x30;
    temp_ay[3] = 0;
    temp_ay[4] = 0;
    
    if(temp_ay[0] != 0x30)
    {
        version[0] = 'V';
        version[1] = temp_ay[0];
        version[2] = temp_ay[1];
        version[3] = '.';
        version[4] = temp_ay[2];
    }  
    else if(temp_ay[1] != 0x30)
    {
        version[0] = 'V';
        version[1] = temp_ay[1];
        version[2] = '.';
        version[3] = temp_ay[2];
    } 
    else 
    {
        version[0] = ' ';
        version[1] = ' ';
        version[2] = ' ';
        version[3] = ' ';      
    }   
}  
  
   
/*******************************************************************************
*******************************************************************************/
void menu_version_display(void)
{
    u8 i;
    
    for( i = 0; i < 5; i++ )
    {
        TXM_StringDisplay(0,8,50+(i*30),24,0,BLACK ,BLACK, (void*)Menu_Version_Display_Item[i][LANGUAGE]); 
        OSTimeDlyHMSM(0, 0,0,5); 
    }
    
    TXM_StringDisplay(0,120,50,24,0,BLACK ,BLACK, (void*)Version);
    OSTimeDlyHMSM(0, 0,0,5);
    
    Version_Converter(version_str, ModBuff[411]);
    TXM_StringDisplay(0,150,80,24,0,BLACK ,BLACK, (void*)version_str);
    OSTimeDlyHMSM(0, 0,0,5);
    
    Version_Converter(version_str, ModBuff[351]);
    TXM_StringDisplay(0,150,110,24,0,BLACK ,BLACK, (void*)version_str);
    OSTimeDlyHMSM(0, 0,0,5);
    
    Version_Converter(version_str, ModBuff[352]);
    TXM_StringDisplay(0,180,140,24,0,BLACK ,BLACK, (void*)version_str);
    OSTimeDlyHMSM(0, 0,0,5);
    
    Version_Converter(version_str, ModBuff[353]);
    TXM_StringDisplay(0,180,170,24,0,BLACK ,BLACK, (void*)version_str);      
    OSTimeDlyHMSM(0, 0,0,5); 

}

/*******************************************************************************
*******************************************************************************/
void menu_version_display_cfg(void)
{
  u8  *m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)Version_Display_Title[LANGUAGE]);  

  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)Menu_Version_Display_Descrip[0][LANGUAGE]);


  PS_Flag=0;  
  
  menu_version_display();
  
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
  
  }  
}

/*******************************************************************************
*******************************************************************************/
