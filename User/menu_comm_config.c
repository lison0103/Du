
#include "includes.h"

/*******************************************************************************
*******************************************************************************/
const char EscStateDisItem[][2][21]= 
{                         
  {" 无配置功能         "," NONE               "}, 
  
  {" 扶梯故障           "," ESC fault          "},  
  {" 扶梯上行           "," ESC UP             "},  
  {" 扶梯下行           "," ESC DOWN           "},  
  {" 扶梯停止           "," ESC STOP           "},  
  {" 扶梯检修           "," ESC service        "},  
  {" 急停状态           "," Emergency stop     "},  
  {" 慢速运行           "," Running -> Slow    "},  
  {" 间歇停梯           "," Running -> Intt.   "},  

  {" 安全回路故障       "," SF chain fault     "}, 
  {" 主板检测故障       "," MB detect fault    "},   
  {" 手动运行           "," Manula             "},  
  {" 自动运行           "," Auto               "},  
  {" 快慢速控制         "," Fast/Slow enable   "},  
  {" 间歇控制模式       "," Intt. enable       "},  
  {"                    ","                    "},  
  {" 扶梯报警           "," ESC alarm          "}, 
  
  {" 星三角控制         "," Delta/Star         "},  
  {" 变频控制           "," VVVF               "},  
  {" 快速1              "," Fast 1             "},  
  {" 快速2              "," Fast 2             "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  
  {" 远程停梯           "," Remote stop        "},  
  {" 钥匙停梯           "," Key stop           "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  {"                    ","                    "},  
  {" 一般故障           "," Fault->Normal      "},
  {" 紧急故障           "," Fault->Emergency   "},    
};

static u16 *CommPara_Buff,Para_Data=0;
static u16 Para_Number=0,Para_Counter=0,PS_Flag=0;

//@添加中英文翻译
const char *Menu_Comm_Config_Descrip[][2] =
{                                          
  {"通信配置","CMS MODBUS"},
  {"删除"," Del"},

};

//@end

/*******************************************************************************
*******************************************************************************/
void comm_cfg_display_coed_str(u16 wid_num,u16 citem)
{
  char a[50]={"                              "};
  u16 i;
  
  if(citem <= 32) 
  {
    if(citem)
    {
      a[1] = 'S';
      a[2] = 0x30+(citem/10);
      a[3] = 0x30+(citem%10); 
    } 
    a[20] = 0;
    strcat(a, EscStateDisItem[citem][LANGUAGE]);
    i=strlen(a);
    for(;i<40;i++)
    {
      a[i] = ' ';
    }  
  }  
  else if(citem <= 64) 
  {
    citem -= 33;
    a[20] = 0;
    strcat(a, EscAlarmDisItem[citem][LANGUAGE]);
    a[40] = 0;
  }  
  else if(citem < 320) 
  {
    citem -= 64; 
    
    get_error_descrip(citem, a);
  }  
  else
  {
    a[0] = 'e';
    a[1] = 'r';
    a[2] = 'r';
    a[3] = 'o';
    a[4] = 'r';
    a[5] = 0;
  }  
  
  TXM_FillTextWidget(wid_num,a);  
}

void comm_cfg_display(void)
{
  char a[10]={"40001 H 0"};  
  u16 i,fcode;
  
  if(PS_Flag)
  {
    comm_cfg_display_coed_str(580+Para_Counter,Para_Data);
  } 
  else
  {  
    if(Para_Number>15) a[4] ='2';
    if((Para_Number>7) && (Para_Number<16)) a[6] = 'L'; 
    a[8] = 0X30+Para_Number%8;
      
    TXM_FillTextWidget(568,a);  
    
    for(i=0;i<5;i++)
    {
      fcode = CommPara_Buff[Para_Number*5+i];
      
      if(Para_Counter==i)
      {
        comm_cfg_display_coed_str(570+i,fcode);
      }  
      else
      {
        comm_cfg_display_coed_str(560+i,fcode);
      }  
      
      OSTimeDlyHMSM(0, 0,0,10);
    }
  }
}

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
*******************************************************************************/
void menu_comm_cfg(void)
{
  u8 *m_keydata,err=0;
  
  CommPara_Buff = (u16*)&ModBuff[1350];
  
  Para_Number=0;
  Para_Counter=0;
  PS_Flag=0;
  
  ZTM_FullScreenImageDisp(315);
  OSTimeDlyHMSM(0, 0,0,50); 
  ZTM_RectangleFill (0,0,239,35,BLACK); 
  OSTimeDlyHMSM(0, 0,0,10);
  
  comm_cfg_display();
  //@
//  TXM_StringDisplay(0,8,5,24,0,RED ,0, "通信配置"); 
  TXM_StringDisplay(0,8,5,24,0,RED ,0, (void*)Menu_Comm_Config_Descrip[0][LANGUAGE]); 
  OSTimeDlyHMSM(0, 0,0,50); 
  ZTM_RectangleFill (0, 285,239, 319,BLACK); 
//  TXM_StringDisplay(0,60,290,24,0,RED ,0, "删除"); 
  TXM_StringDisplay(0,60,290,24,0,RED ,0, (void*)Menu_Comm_Config_Descrip[1][LANGUAGE]); 
  //@end
  
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
            Para_Data = CommPara_Buff[Para_Number*5+Para_Counter];
            break; 
          case KEY_SET:
            PS_Flag = 0;
            CommPara_Buff[Para_Number*5+Para_Counter] = Para_Data;
            modbus_write(MB_COM_PORT, 675+(Para_Number*5+Para_Counter), 1);
            break; 
          case KEY_UP:
            if(Para_Data<320) Para_Data++;else Para_Data = 0;
            break; 
          case KEY_DOWN:
            if(Para_Data) Para_Data--;else Para_Data=320;
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
            Para_Data = CommPara_Buff[Para_Number*5+Para_Counter];
            break;       
          case KEY_LEFT:
            if(Para_Number) Para_Number--;
            break;
          case KEY_RIGHT:
            if(Para_Number<23) Para_Number++;
            break;
          case KEY_UP:
            if(Para_Counter) Para_Counter--;
            break;
          case KEY_DOWN:
            if(Para_Counter<4) Para_Counter++;
            break;
        }  
      }
      
      comm_cfg_display();
    }  
  }  
}



/*******************************************************************************
*******************************************************************************/
