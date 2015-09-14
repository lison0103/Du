
#include "includes.h"

/*******************************************************************************
*******************************************************************************/

static u16 ESC_Bk_Addr; //Para_Data=0,
static u8 PS_Flag=0;

const char EscRecover_Title[2][20]={"参数恢复>主板","PARA RECOVER > MB"}; 
const char EscBackup_Title[2][20]={"扶梯参数备份", "ESC PARA BACK"}; 

u16 MCRC16( uint8_t *pucFrame, uint16_t usLen )
{
 
    
  return(CRC16( pucFrame, usLen ));  
}

/*******************************************************************************
*******************************************************************************/
void esc_sn_display(u16 x,u16 y,u8 *buff,u8 set_bit)
{  
  char i,a[20];
  
  if(set_bit)
  {
    set_bit--;
    for(i=0;i<set_bit;i++)
    {
      a[i] = buff[i]; 
    }  
    a[set_bit] = 0;
    TXM_StringDisplay(0,x,y,32,1,BLACK,LGRAY, (void*)a);  
    
    a[0] = buff[set_bit];
    a[1] = 0;
    TXM_StringDisplay(0,x+(set_bit*16),y,32,1,YELLOW,RED, (void*)a);  

    for(;i<12;i++)
    {
      a[i-set_bit] = buff[i+1];
    }  
    a[i-set_bit] = 0;
    TXM_StringDisplay(0,x+16+(set_bit*16),y,32,1,BLACK,LGRAY, (void*)a);  
  }
  else
  {  
    for(i=0;i<13;i++)
    {
      a[i] = buff[i]; 
    }  
    a[13] = 0;
    TXM_StringDisplay(0,x,y,32,1,BLACK,LGRAY, (void*)a);
  }  
}

/*******************************************************************************
*******************************************************************************/
u8 para_backup_process(u16 bk_num)
{
  u32 i;

  buff_temp[0] = 0xff;          
  buff_temp[1] = 0xaa;          
  buff_temp[2] = 0x33;          
  buff_temp[3] = 0xcc;          
  
  //系统参数
  for(i=0;i<240;i++)
  {  
    buff_temp[i+100] = ModBuff[i+1100];          
  }

  //COMM参数  
  for(i=0;i<242;i++)
  {  
    buff_temp[i+400] = ModBuff[i+1350];          
  }
  
  //多段速参数  
  for(i=0;i<50;i++)
  {  
    buff_temp[i+700] = ModBuff[i+1600];          
  }
  
  //复位数据  
  for(i=0;i<252;i++)
  {  
    buff_temp[i+800] = ModBuff[i+1700];          
  }

  //故障记录
  for(i=0;i<2400;i++)
  {  
    buff_temp[i+1100] = ModBuff[i+3000];          
  }
  
  i = bk_num+5;
  
  i = i*4096;
  
  Flash_W25X_Write(buff_temp,i,4096);   
  
  return(1);
}

u8 para_restore_process(u16 bk_num)
{
  u32 i;
  
  i = bk_num+5;
  i = i*4096;
  
  Flash_W25X_Read(buff_temp,i,4096);   

  //系统参数  
  if(!MCRC16( &buff_temp[100], 240 ))
  {  
    for(i=0;i<240;i++)
    {  
      ModBuff[i+1100] = buff_temp[i+100];          
    }
    
    modbus_write(MB_COM_PORT, 550, 120);
  }
  
  //COMM参数  
  if(!MCRC16( &buff_temp[400], 242 ))
  {  
    for(i=0;i<242;i++)
    {  
      ModBuff[i+1350] = buff_temp[i+400];          
    }
    modbus_write(MB_COM_PORT, 675, 121);
  }
  
  //多段速参数  
  if(!MCRC16( &buff_temp[700], 50 ))
  {  
    for(i=0;i<50;i++)
    {  
      ModBuff[i+1600] = buff_temp[i+700];          
    }
    modbus_write(MB_COM_PORT, 800, 25);
  }
  
  //复位数据  
  if(!MCRC16( &buff_temp[1700], 252 ))
  {  
    for(i=0;i<252;i++)
    {  
      ModBuff[i+1700] = buff_temp[i+800];          
    }
    
    modbus_write(MB_COM_PORT, 850, 50);
    modbus_write(MB_COM_PORT, 900, 76);
  }

  return(1);
}

/*******************************************************************************
*******************************************************************************/
void backup_display(void)
{
  u16 fcolor=0,bcolor=0;
  
  if(ESC_Bk_Addr)
  {
    TXM_StringDisplay(0,8,115,24,1,BLUE ,LGRAY, "当前备份编号："); 

    if(PS_Flag)
    {
      fcolor = YELLOW;
      bcolor = RED;  
    }
    else 
    {
      fcolor = BLACK;
      bcolor = LGRAY;  
    }  
    
    TXM_DigitDisplay(0,180,115,24,1,fcolor ,bcolor, ESC_Bk_Addr,4,0,ALIGN_RIGHT);
  }
  else
  {
    TXM_StringDisplay(0,8,115,24,1,RED ,WHITE, "当前主板无备份");
  }

  TXM_StringDisplay(0,8,150,24,1,BLUE ,LGRAY, "当前备份数量："); 
  TXM_DigitDisplay(0,180,150,24,1,BLACK ,LGRAY, DuSysBuff[10],4,0,ALIGN_RIGHT);
}

void restore_display(u16 num,u8 *buff)
{
  u16 fcolor=0,bcolor=0;
  u32 i;
  
  u8 *pbuff = &buff_temp[100];

  if(RECORD_ESC_NUMBER)
  {
    //TXM_StringDisplay(0,8,115,24,0,NAVY ,0, "选择参数组："); 
    i = num+4;
    i = i*4096;
  
    Flash_W25X_Read(buff_temp,i,4096);   

    if(PS_Flag)
    {
      fcolor = YELLOW;
      bcolor = RED;  
    }
    else 
    {
      fcolor = BLACK;
      bcolor = LGRAY;  
    }  
    
    TXM_DigitDisplay(0,165,115,24,1,fcolor ,bcolor, num,4,0,ALIGN_RIGHT);
    esc_sn_display(8,145,buff,0);
    
    //显示主要参数
    //控制方式
    if(pbuff[3]==0)
    {
      TXM_StringDisplay(0,8,190,24,1,YELLOW ,DGRAY, "星 三 角");
    } 
    else if(pbuff[3]==1)
    {
      TXM_StringDisplay(0,8,190,24,1,YELLOW ,DGRAY, "单 变 频");
    }  
    else if(pbuff[3]==2)
    {
      TXM_StringDisplay(0,8,190,24,1,YELLOW ,DGRAY, "复合控制");
    }  
    
    //主机 
    if(pbuff[5]==0)
    {
      TXM_StringDisplay(0,115,190,24,1,YELLOW ,DGRAY, "双 主 机");
    } 
    else if(pbuff[1]==1)
    {
      TXM_StringDisplay(0,115,190,24,1,YELLOW ,DGRAY, "单 主 机");
    }
    
    //主机 
    switch(pbuff[4])
    {
    case 0:TXM_StringDisplay(0,8,220,24,1,YELLOW ,DGRAY, "上下扩展");break;
    case 1:TXM_StringDisplay(0,8,220,24,1,YELLOW ,DGRAY, "下端扩展");break;
    case 2:TXM_StringDisplay(0,8,220,24,1,YELLOW ,DGRAY, "上端扩展");break;
    case 3:TXM_StringDisplay(0,8,220,24,1,YELLOW ,DGRAY, "单 主 板");break;  
    } 

    //节能
    if(pbuff[15]==0)
    {
      TXM_StringDisplay(0,115,220,24,1,YELLOW ,DGRAY, "有 间 歇");
    } 
    else if(pbuff[14]==0)
    {
      TXM_StringDisplay(0,115,220,24,1,YELLOW ,DGRAY, "快 慢 速");
    }
    else  
    {
      TXM_StringDisplay(0,115,220,24,1,YELLOW ,DGRAY, "无 节 能");
    }
    
    //测速方式 
    switch(pbuff[45])
    {
    case 0:TXM_StringDisplay(0,8,250,24,1,YELLOW ,DGRAY, "X1&2飞轮探头测速 ");break;
    case 1:TXM_StringDisplay(0,8,250,24,1,YELLOW ,DGRAY, "主轴测速  2 探头 ");break;
    case 2:TXM_StringDisplay(0,8,250,24,1,YELLOW ,DGRAY, "主轴测速  3 探头 ");break;
    case 3:TXM_StringDisplay(0,8,250,24,1,YELLOW ,DGRAY, "X1&2飞轮 X6&8主轴");break;  
    }
  } 
  else
  {
    //TXM_StringDisplay(0,8,115,24,0,RED ,0, "无可选备份参数组"); 
  }  
}

/*******************************************************************************
*******************************************************************************/
void menu_para_restore(void)
{
  u8 *m_keydata,err=0,item_buff[20];
  u16 item_choice=0;

  ZTM_RectangleFill (0,0,239,39,NAVY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);

  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)EscRecover_Title[LANGUAGE]); 
  
  TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "选择");
  
  TXM_StringDisplay(0,8,45,24,0,NAVY ,0, "主板扶梯编号："); 
  esc_sn_display(8,70,&ModBuff[1018],0);
  
  ZTM_BColorPutLine (108, 8, 108, 232);
  ZTM_BColorPutLine (180, 8, 180, 232);
  
  ESC_Bk_Addr = esc_bk_pos_check(&ModBuff[1018]);

  if(RECORD_ESC_NUMBER)
  {
    TXM_StringDisplay(0,8,115,24,0,NAVY ,0, "选择参数组："); 
  } 
  else
  {
    TXM_StringDisplay(0,8,115,24,0,RED ,0, "无可选备份参数组"); 
  }  
  
  if(RECORD_ESC_NUMBER)
  {
    if(ESC_Bk_Addr && (item_choice <= RECORD_ESC_NUMBER))
    {
      item_choice = ESC_Bk_Addr;
    } 
    else
    {
      item_choice = 1;
    }  
  }  
  get_esc_bk_item_index(item_choice,item_buff);
  restore_display(item_choice,&item_buff[2]);
  
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
          case KEY_F3:
          case KEY_ESC:
            PS_Flag = 0;                                  
            break; 
          case KEY_F2:
            PS_Flag = 0;                                  
            if(!ESC_Bk_Addr)
            {
              DuSysBuff[10]++;
              ESC_Bk_Addr = DuSysBuff[10];
            }
            
            para_restore_process(item_choice-1);
            
          case KEY_UP:
            
            if(item_choice < RECORD_ESC_NUMBER)
            {
              item_choice++;
            }  
            
            get_esc_bk_item_index(item_choice,item_buff);
            
            break; 
          case KEY_DOWN:
            if(item_choice>1)
            {
              item_choice--;
            }  
            
            get_esc_bk_item_index(item_choice,item_buff);
              
            break; 
        }
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {         
        PS_Flag = 1; 
        TXM_StringDisplay(0,130,290,24,1,RED ,BLACK, "确定       ");
      } 
    }
    
    restore_display(item_choice,&item_buff[2]);
  }  
}

/*******************************************************************************
*******************************************************************************/
void menu_para_backup(void)
{
  u8 *m_keydata,err=0;

  ZTM_RectangleFill (0,0,239,39,NAVY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)EscBackup_Title[LANGUAGE]); 
  
  TXM_StringDisplay(0,190,290,24,1,RED ,BLACK, "备份");
 
  //esc_sn_display(u16 x,u16 y,char *buff,u8 set_bit);
  
  ESC_Bk_Addr = esc_bk_pos_check(&ModBuff[1018]);
  
  if(RECORD_ESC_NUMBER<ESC_Bk_Addr) ESC_Bk_Addr = 0;
  
  TXM_StringDisplay(0,8,50,24,0,NAVY ,0, "主板扶梯编号："); 
  esc_sn_display(8,75,&ModBuff[1018],0);
  
  PS_Flag=0;  
  
  backup_display();
  
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
          case KEY_F3:
          case KEY_ESC:
            PS_Flag = 0;                                  
            TXM_StringDisplay(0,130,290,24,1,RED ,BLACK, "     备份");
            break; 
          case KEY_F2:
            PS_Flag = 0;                                  
            TXM_StringDisplay(0,130,290,24,1,RED ,BLACK, "     备份");
            if(!ESC_Bk_Addr)
            {
              DuSysBuff[10]++;
              ESC_Bk_Addr = DuSysBuff[10];
            }
            
            para_backup_process(ESC_Bk_Addr-1);
            
            esc_bk_pos_write(&ModBuff[1018],ESC_Bk_Addr);
            
            du_sys_data_write();
            
            break; 
        }
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {         
        PS_Flag = 1; 
        TXM_StringDisplay(0,130,290,24,1,RED ,BLACK, "确认 返回");
      } 
    }
    
    backup_display();
  }  
}

/*******************************************************************************
*******************************************************************************/
