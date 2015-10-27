
#include "includes.h"

/*******************************************************************************
*******************************************************************************/

static u8 *ErrType_Buff,*RstPara_Buff,ErrType_Data=0,RstPara_Data=0;
static u8 Para_Number=0,Para_Choice=0,PS_Flag=0;

const u8 FaultType_Descrip[][2][21] =
{
  {"紧急故障         ","Emerg. error    "},
  {"一般故障         ","Normal Fault    "},
};

const u8 FaultRstType_Descrip[][2][21] =
{                         
  {"自恢复           ","Auto reset      "},
  {"人工复位         ","Manual reset    "},
  {"断电保持&人工复位","Power off locked"},
};

//@添加中英文翻译
const char *Menu_Error_Config_Descrip[][2] =
{                                          
  {"故障分类","FAULT CLASS"},
  {"切换      修改","Switch    Alter"},
  {"故障类型","Fault type"},
  {"复位类型","Reset Type"},
};

//@end

u8 MdReadRst_En=0;
/*******************************************************************************
*******************************************************************************/
void error_cfg_display(void)
{
  char a[50]={"                              "};
  u16 f_color[2] = {BLACK,BLACK},b_color[2] = {LGRAY,LGRAY};
  
  if(!PS_Flag)
  {
    ErrType_Data = ErrType_Buff[Para_Number/8] >> (Para_Number%8);
    RstPara_Data = RstPara_Buff[Para_Number];
  }  
  else
  {
    f_color[Para_Choice] = YELLOW;
  } 
  
  get_error_descrip(Para_Number+1, a); 
  TXM_StringDisplay(0,0,45,24,1,BLACK,LGRAY, (void*)a); 
  
  b_color[Para_Choice] = RED;
  //@
  TXM_StringDisplay(0,8,150,24,1,f_color[0],b_color[0], (void*)FaultType_Descrip[ErrType_Data][LANGUAGE]);
  TXM_StringDisplay(0,8,210,24,1,f_color[1],b_color[1], (void*)FaultRstType_Descrip[RstPara_Data][LANGUAGE]);
  //@end  
}

/*******************************************************************************
*******************************************************************************/
void menu_error_cfg(void)
{
  u8 *m_keydata,err=0;

  MdReadRst_En = 1;
  
  ZTM_RectangleFill (0,0,239,39,NAVY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,WHITE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  //@
  OSTimeDlyHMSM(0, 0,0,10);
//  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, "故障分类");
//  
//  TXM_StringDisplay(0,60,290,24,0,RED ,0, "切换      修改");
//  
//  TXM_StringDisplay(0,12,120,24,0,BLACK , 0, "故障类型");
//  
//  TXM_StringDisplay(0,12,180,24,0,BLACK ,0, "复位类型");
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)Menu_Error_Config_Descrip[0][LANGUAGE]);
  
  TXM_StringDisplay(0,60,290,24,0,RED ,0, (void*)Menu_Error_Config_Descrip[1][LANGUAGE]);
  
  TXM_StringDisplay(0,12,120,24,0,BLACK , 0, (void*)Menu_Error_Config_Descrip[2][LANGUAGE]);
  
  TXM_StringDisplay(0,12,180,24,0,BLACK ,0, (void*)Menu_Error_Config_Descrip[3][LANGUAGE]);  
  //@end
  while(MdReadRst_En<2)
  {
    OSTimeDlyHMSM(0, 0,0,10);
  }  
  ErrType_Buff = &ModBuff[1260];
  RstPara_Buff = &ModBuff[1700];
  
  Para_Number = 0;
  ErrType_Data = ErrType_Buff[Para_Number/8];
  RstPara_Data = RstPara_Buff[Para_Number];

  error_cfg_display();
  
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

            //ErrType_Data = ErrType_Buff[(Para_Number-1)/8];
            //RstPara_Data = RstPara_Buff[Para_Number-1];

            break; 
          case KEY_SET:
            PS_Flag = 0;
            
            ErrType_Buff[(Para_Number)/8] &= ~(1<<((Para_Number)%8));
            ErrType_Buff[(Para_Number)/8] |= (ErrType_Data<<((Para_Number)%8));
            modbus_write(MB_COM_PORT, 630+(Para_Number/16), 1);
            
            if(ECT_A_VERSION == 3)
            {   
              RstPara_Buff[Para_Number] = RstPara_Data;
              modbus_write(MB_COM_PORT, 850+(Para_Number/2), 1);
            }
            
            break; 
          case KEY_UP:
            if(Para_Choice) 
            {
              RstPara_Data++;
              if(RstPara_Data>2) RstPara_Data = 0; 
            } 
            else
            {
              if(ErrType_Data) ErrType_Data = 0; else ErrType_Data = 1;
            }  
            
            break; 
          case KEY_DOWN:
            if(Para_Choice) 
            {   
              if(RstPara_Data) RstPara_Data--; else RstPara_Data = 2; 
            } 
            else
            {
              if(ErrType_Data) ErrType_Data = 0; else ErrType_Data = 1;
            }  
            
            break; 
        }  
      } 
      else
      {
        switch(m_keydata[0])
        {
          case KEY_F3:
          case KEY_SET:
            PS_Flag = 1;
            
            break;    
            
          case KEY_F1:
            if(Para_Choice) Para_Choice = 0; else Para_Choice = 1;
 
            break;  
            
          case KEY_RIGHT:
          case KEY_UP:
            if(Para_Number<249) Para_Number++; else Para_Number = 0;
            break;
          case KEY_LEFT:
          case KEY_DOWN:
            if(Para_Number>0) Para_Number--; else Para_Number = 249;
            break;
        }  
      }
      
      error_cfg_display();
    }  
  }  
  
  MdReadRst_En = 0;
}

/*******************************************************************************
*******************************************************************************/
