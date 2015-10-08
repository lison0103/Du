/****************************************Copyright (c)****************************************************
** File Name:           menu_password_manage.c
** Created By:          lisonchen
** Created date:        2015-09-15
** Version:             v1.00
** Descriptions:        �������˵�
**
*********************************************************************************************************/
#include "includes.h"

#define PASS_DES_MAX  10
#define PASS_LEN      6
  
/*******************************************************************************
*******************************************************************************/

static u8 *PASS_Buff,PASS_Temp[20],Para_Cnum=0; 
static u8 Para_Choice=0,PS_Flag=0;

static char const Password_Code[11] = {"-0123456789"};
                                    
const char Password_Title[2][20]={"��������","Enter Password"}; 
const char input_item[][20]={"����","Input","ȷ��","  OK ","�޸�","Alter","����","Earse","���ڲ�������...","Erasing data...",
"   �������!   "," Erase finish! "," ʣ��ʹ������: ","Validity Date:"}; 

u8 USER_RIGHT_LEVEL = 0;
u8 Temp[] = "------";
u8 Temp1[] = "******";
const u8 *Version = {"V1.0"};
u8 Set_Flag = 0;
u8 EARSE_CHIP = 0;
extern u8 m_buff_temp[3];
/*******************************************************************************
*******************************************************************************/
void menu_password_display(u8 set_bit)
{  
  char i,a[20];
  
  if(set_bit)
  {
    set_bit--;
    for(i=0;i<set_bit;i++)
    {
      a[i] = PASS_Temp[i];
    }  
    a[set_bit] = 0;
    TXM_StringDisplay(0,70,150,32,1,BLACK,LGRAY, (void*)a);  
    
    a[0] = PASS_Temp[set_bit];
    a[1] = 0;
    TXM_StringDisplay(0,70+(set_bit*16),150,32,1,YELLOW,RED, (void*)a);  

    for(;i<PASS_LEN-1;i++)
    {
      a[i-set_bit] = PASS_Temp[i+1];
    }  
    a[i-set_bit] = 0;
    TXM_StringDisplay(0,86+(set_bit*16),150,32,1,BLACK,LGRAY, (void*)a);  
  }
  else
  {  
    PASS_Temp[PASS_LEN] = 0;
    TXM_StringDisplay(0,70,150,32,1,BLACK,LGRAY, (void*)PASS_Temp);
  }  
}

u8 get_password_num(u8 dat)
{
  u8 i,cnt=0;
  
  for(i=0; i<PASS_DES_MAX; i++)
  {
    if(dat == Password_Code[i])
    {
      cnt = i;
      break;
    }            
  }  
  
  return(cnt);
}

/*******************************************************************************
*******************************************************************************/
void menu_password_cfg(void)
{
  u8  i,*m_keydata,err=0;
  
  ZTM_RectangleFill (0,0,239,39,BLUE);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,40,239,279,LGRAY);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,280,239,319,BLACK);
  
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)Password_Title[LANGUAGE]);  
  TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0 + LANGUAGE]);//����
//  TXM_StringDisplay(0,120,290,24,1,RED ,BLACK, (void*)input_item[4 + LANGUAGE]);//�޸�
  
  TXM_StringDisplay(0,5,260,16,0,BLACK ,BLACK, (void*)Version);//�汾
  TXM_StringDisplay(0,50,260,16,0,BLACK ,BLACK, (void*)input_item[12 + LANGUAGE]);//��ʹ������
  

  validity_date = 180 - VALIDITY_USE_DATE;
  m_buff_temp[0] = validity_date/100 + 0x30;
  m_buff_temp[1] = validity_date%100/10 + 0x30;
  m_buff_temp[2] = validity_date%10 + 0x30;
  TXM_StringDisplay(0,170,260,16,0,BLACK ,BLACK, (void*)m_buff_temp);//��

  
  PASS_Buff = Temp;
  
  for(i=0;i<6;i++)
  {
    PASS_Temp[i] = PASS_Buff[i];
  }  
  
  Para_Choice=0;
  PS_Flag=0;  
  
  menu_password_display(Para_Choice);
  
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,60000,&err);
    
    if(err == OS_ERR_TIMEOUT)
    {
      break;
    } 
    else if((!PS_Flag) && (m_keydata[0] == KEY_ESC))
    {
      EARSE_CHIP = 0;
      break;
    }
    //������Ч�ڹ���ļ�������
    else if(EARSE_CHIP == 1)
    {
      if(m_keydata[0]==KEY_F1)
      {       
        EARSE_CHIP = 0;
        TXM_StringDisplay(0,40,220,24,1,YELLOW ,RED, (void*)input_item[8 + LANGUAGE]);//���ڲ�������...
        
        for(u8 i = 0;i<100;i++)
        {
          DuSysBuff[i] = 0;
        }
        du_sys_data_write();
        OSTimeDlyHMSM(0, 0,1,0);        
        
        validity_date = 0;
//        SPI_W25X_ChipErase();

        TXM_StringDisplay(0,40,220,24,1,YELLOW ,RED, (void*)input_item[10 + LANGUAGE]);//�������!
        OSTimeDlyHMSM(0, 0,2,0);
        break;
      }
      
    }
    else 
    {
      if(PS_Flag)
      {
        switch(m_keydata[0])
        {
          case KEY_ESC:
            
            PS_Flag = 0;

            for(i=0;i<PASS_LEN;i++)
            {
              PASS_Temp[i] = PASS_Buff[i];
            }  
            
            Para_Choice=0;
            TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0 + LANGUAGE]);//����
            
            break; 
          case KEY_SET:
          case KEY_F3:  
            PS_Flag = 0;
            Set_Flag = 1;
            Para_Choice=0;
            TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[0 + LANGUAGE]);//����
            

            break; 
          case KEY_UP:
            
            if(Para_Cnum < PASS_DES_MAX) Para_Cnum++; else Para_Cnum=0;
            PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
            break; 
          case KEY_DOWN:
            
            if(Para_Cnum) Para_Cnum--;else Para_Cnum=PASS_DES_MAX;
            PASS_Temp[Para_Choice-1] = Password_Code[Para_Cnum];
            break; 
          case KEY_LEFT:
            if(Para_Choice>1) Para_Choice--; 
            else Para_Choice = PASS_LEN; 
            Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
            break; 
          case KEY_RIGHT:
            if(Para_Choice<PASS_LEN) Para_Choice++;
            else Para_Choice = 1; 
            Para_Cnum = get_password_num(PASS_Temp[Para_Choice-1]);
            break; 
        }  
      } 
      else if((m_keydata[0]==KEY_F3) || (m_keydata[0]==KEY_SET))
      {
        Para_Choice = 1;
        Para_Cnum = get_password_num(PASS_Buff[Para_Choice-1]);
        
        TXM_StringDisplay(0,180,290,24,1,RED ,BLACK, (void*)input_item[2 + LANGUAGE]);//ȷ��
        PS_Flag = 1; 
        
        PASS_Buff = Temp;
        
        for(i=0;i<6;i++)
        {
          PASS_Temp[i] = PASS_Buff[i];
        } 
      }
     
      menu_password_display(Para_Choice);
      
      //��֤�����Ƿ���ȷ
      if(Set_Flag)
      {
        Set_Flag = 0;
        if( PASS_Temp[0] == (1 + 0x30) && PASS_Temp[1] == (2 + 0x30) && PASS_Temp[2] == (3 + 0x30) 
           && PASS_Temp[3] == (4 + 0x30) && PASS_Temp[4] == (5 + 0x30) && PASS_Temp[5] == (6 + 0x30) )
        {
          USER_RIGHT_LEVEL = 2;
          break;
        }
        else if( PASS_Temp[0] == (1 + 0x30) && PASS_Temp[1] == (1 + 0x30) && PASS_Temp[2] == (1 + 0x30) 
                && PASS_Temp[3] == (1 + 0x30) && PASS_Temp[4] == (1 + 0x30) && PASS_Temp[5] == (1 + 0x30) )
        {
          USER_RIGHT_LEVEL = 1;
          break;
        }
        //�򿪲����������ع���
        else if( PASS_Temp[0] == (0 + 0x30) && PASS_Temp[1] == (0 + 0x30) && PASS_Temp[2] == (0 + 0x30) 
                && PASS_Temp[3] == (0 + 0x30) && PASS_Temp[4] == (0 + 0x30) && PASS_Temp[5] == (0 + 0x30) )
        {
            EARSE_CHIP = 1;
            ZTM_RectangleFill (0,280,239,319,BLACK);
            OSTimeDlyHMSM(0, 0,0,10);
            TXM_StringDisplay(0,60,290,24,1,RED ,BLACK, (void*)input_item[6 + LANGUAGE]);//����
        }
        else
        {
          USER_RIGHT_LEVEL = 0;
        }
        Set_Flag = 0;
      }
      
    }  

  }  
}

/*******************************************************************************
*******************************************************************************/
