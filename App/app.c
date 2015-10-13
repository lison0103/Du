
#include "includes.h"
#include "string.h"

//#define MB_COM_PORT     USART3

//static u8 buff[1024],displayBuff[100];

typedef struct 
{
  u8 head;
  u8 code;
  u8 time[6]; 
}FAULT_CODE_STRUCT;

typedef struct 
{
  //状态  200
  
  
  //基本信息 100
  u8 BasePara;
  //统计数据 100
  u8 *StatBuff;
  //多段速配置 50
  u8 *MspPara;
  //系统参数 240
  u8 *SysPara;
  //通信配置 242
  u8 *ComPara;
  //实时数据 100
  u8 *RtBuff;
  
  //故障记录 2400条
  FAULT_CODE_STRUCT *fault_record; 
  
}ESC_BUFF_STRUCT;

u8 handshallCode[6] = {0xaa,0x00,0xcc,0x33,0xc3,0x3c};

u8 error_code_old = 0xff,state_old=0xff;

u16 up_pic[6] = {1000,1001,1002,1003,1004,1005};
u16 down_pic[6] = {1005,1004,1003,1002,1001,1000};

extern u8 MainDisFlag;

u8 DuSys_Data[100];
u16 *DuSysBuff = (u16*)DuSys_Data;


/***************************************************************************************************
***************************************************************************************************/
void Display_RTCC(u16 x,u16 y,u8 bit_flash,u8 dot_flash,u8 *pt)
{
  u8 dis_data[31];
  
	static u8 dot_flash_tms=0,bit_flash_tms=0;

	dis_data[0] = ' ';
	dis_data[1] = ' ';
	dis_data[2] = 'D';
	dis_data[3] = 'U';
	dis_data[4] = ' ';

  dis_data[5] = '2';
	dis_data[6] = '0';
	dis_data[7] = (pt[0]/10)+0x30;
	dis_data[8] = (pt[0]%10)+0x30;
	dis_data[9] = '-';
	dis_data[10] = (pt[1]/10)+0x30;
	dis_data[11] = (pt[1]%10)+0x30;
	dis_data[12] = '-';
	dis_data[13] = (pt[2]/10)+0x30;
	dis_data[14] = (pt[2]%10)+0x30;
	dis_data[15] = ' ';
	dis_data[16] = ' ';
	dis_data[17] = (pt[3]/10)+0x30;
	dis_data[18] = (pt[3]%10)+0x30;
	dis_data[19] = ':';
	dis_data[20] = (pt[4]/10)+0x30;
	dis_data[21] = (pt[4]%10)+0x30;
	dis_data[22] = ':';
	dis_data[23] = (pt[5]/10)+0x30;														
	dis_data[24] = (pt[5]%10)+0x30;																						

	dis_data[25] = ' ';
	dis_data[26] = ' ';
	dis_data[27] = ' ';
	dis_data[28] = ' ';
	dis_data[29] = ' ';

	dis_data[30] = 0;
  
	if(bit_flash)
	{
		bit_flash_tms++;
		if(bit_flash_tms>2) bit_flash_tms = 0;

		if(bit_flash_tms==0)
		{
			dis_data[(bit_flash*3)-1] = ' ';
      		dis_data[bit_flash*3] = ' ';      
		}   
	}
  
	if(dot_flash)
	{
		dot_flash_tms++;
		if(dot_flash_tms>3) dot_flash_tms = 0;
		
		if(dot_flash_tms<2)
		{
			dis_data[17] = ' ';
		}	
	}
	
//	TXM_PutText (x, y,0X21,0xd2,0x01,0xffff, BLUE, dis_data); // 
  
  dis_data[2] = 'D';
  dis_data[3] = 'a';
  dis_data[4] = 't';
  dis_data[5] = 'e';
  dis_data[6] = ' ';  
  dis_data[15] = 0;
  TXM_FillTextWidget (301, (void*)&dis_data[2]);
  
  dis_data[12] = 'T';
  dis_data[13] = 'i';
  dis_data[14] = 'm';
  dis_data[15] = 'e';
  dis_data[16] = ' ';
  dis_data[25] = 0;
  TXM_FillTextWidget (302, (void*)&dis_data[12]);
}

/***************************************************************************************************
***************************************************************************************************/
void AppTask_Main(void *p_arg)
{
  u8 start_main_display=0;
  u8 *m_keydata,err=0;
//  u16 i;
//  u32 j;
  
  //u8 ttt = 50;
  
  (void)p_arg;

  //等待显示板握手成功
  while(OSTaskDelReq(TASK_LCM_INIT_PRIO) != OS_ERR_TASK_NOT_EXIST);

/*  
  for(j=0;j<10;j++)
  {     
    for(i=0;i<2048;i++)
    {
      pt_ModBuff[i] = i+1;
    }  
    
    Flash_W25X_Write(ModBuff, j*4096, 4096);
    
    for(i=0;i<4096;i++) ModBuff[i] = 0; 
    
    Flash_W25X_Read(ModBuff,j*4096,4096);
  }  
*/
  
/*  
  //GPIOB->ODR &= ~0x1000;

  //读取参数资料 Index_buff[1024]
  //GPIOB->ODR |= 0x1000;
  for(i=0;i<256;i++)
  {
    buff_temp[i] = i;
  }  
  Flash_W25X_Write(buff_temp,1000,256);
  Flash_W25X_Read(buff_temp,1000,500);
  GPIOB->ODR |= 0x1000;
  for(i=0;i<256;i++)
  {
    buff_temp[i] = i;
  }  
  Flash_W25X_Write(buff_temp,1100,256);
  Flash_W25X_Read(buff_temp,1000,500);
  GPIOB->ODR |= 0x1000;

  
  
  while(1);
*/  

  
  
  esc_bk_init();
  
  
//@ 有效期判断  
  
  if(USER_RIGHT_VALIDITY == 1)
  {
//    u8 TimeBuff[6];
    RTCC_GetTime(TimeBuff);
    
    last_set_date[0] = DuSysBuff[14];
    last_set_date[1] = DuSysBuff[15];
    last_set_date[2] = DuSysBuff[16];
    last_set_date[3] = DuSysBuff[17];
    last_set_date[4] = DuSysBuff[18];
    last_set_date[5] = DuSysBuff[19];
    
    Get_Current_Date(current_set_date, TimeBuff);   
    if(Date_Validity(last_set_date) && Date_Validity(current_set_date))
    {
//      VALIDITY_USE_DATE += Calculate(last_set_date,current_set_date);
      validity_date = 180 - (VALIDITY_USE_DATE + Calculate(last_set_date,current_set_date));
    }
    else
    {
      validity_date = 0;
    }
    
    
    if(validity_date <= 0)
    {
        USER_RIGHT_VALIDITY = 0;
        
        du_sys_data_write();
    }       
    
    //有效期小于1个月，每次开机提醒
    if(validity_date <= 30)
    {
      validity_cfg();
    }
  }
  else
  {
    validity_cfg();
  
  }     
//@end 
  
  
  while(1)
  {
    if(!start_main_display)
    {
      ZTM_FullScreenImageDisp(300);
      OSTimeDlyHMSM(0, 0,0,10);
      start_main_display = 1;
    }  
    //ModBuff[454] = ttt;
//@
//    GPIOB->ODR |= 0x1000;
    main_display();  
//    GPIOB->ODR &= ~0x1000;
//@end    
    OSTimeDlyHMSM(0, 0,0,600);
    
    m_keydata = OSMboxPend(KeyMbox,20,&err);
    /*
    if(m_keydata[0] == KEY_UP)
      {
        ttt++;
      }  
      else if(m_keydata[0] == KEY_DOWN)
      {
        ttt--;
      }  
    else 
    */  
    if(err != OS_ERR_TIMEOUT)
    { 
      start_main_display = 0;
      if(m_keydata[0] == KEY_F3)
      { 
        MainDisFlag = 0;
        
        //进入帮助菜单
        Task_Help();        
      }  
      else if(m_keydata[0] == KEY_F2)
      { 
        MainDisFlag = 0;
        
        //进入菜单
        menu_process();
      }  
      else
      {
        start_main_display = 1;
      }  
    }  
  }  
}

/***************************************************************************************************
***************************************************************************************************/


/***************************************************************************************************
***************************************************************************************************/
