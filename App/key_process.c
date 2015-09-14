
#include "includes.h"

OS_EVENT *KeyMbox;

u16 key_scan(void);
void key_init(void);

u8 KeyDataMsg=0;
u8 ResetKeyPin = 0;
u16 ResetTms=0;

/***************************************************************************************************
***************************************************************************************************/
void AppTask_KEY(void *p_arg)
{
  (void)p_arg;   
  
  u8 key_temp=0,key_valid=0,key_data=0,key_state=0;
  u16 key_cnt=0,key_dlyms1=0,key_speed_up=0;

  key_init();   
  
  KeyMbox = OSMboxCreate((void*)&KeyDataMsg);
  
  OSTimeDlyHMSM(0, 0,1,0); 
  
  while (1)
  {
    //GPIOB->ODR |= 0x1000;
    key_temp = key_scan();
    key_data = 0;
    //GPIOB->ODR &= ~0x1000;
    
    if(key_temp == KEY_F1)
    {
      ResetKeyPin = 1;
      if(ResetTms<10000) ResetTms++; 
    }   
    else
    {  
      ResetKeyPin = 0;
    }  
    
    switch(key_state)
    {
      case 0:
        if(key_temp==0) 
        {
          if(++key_cnt>5) key_state=1; 
        }  
        else 
        {
          key_cnt=0;
        }
        break;
      case 1:
        if(key_temp)
        {
          if(++key_cnt>1) 
          {
            key_state=2;
            key_cnt = 0;
            key_dlyms1=0;
            key_speed_up=0;
            
            key_data = key_temp;
          }  
        }  
        else 
        {
          key_cnt = 0;
        }  
        break;
      case 2:
        if(key_temp)
        {
          if(key_cnt<10000) key_cnt++;
          if(key_cnt > 50)
          {
            if((key_temp==KEY_UP) || (key_temp==KEY_DOWN))
            { 
              key_dlyms1++;
              if((key_cnt < 800) && (key_dlyms1>100))
              {
                 key_dlyms1 = 0;  
                 key_speed_up=1;
              }  
              else if((key_cnt < 1500) && (key_dlyms1>60))
              {
                 key_dlyms1 = 0;  
              }  
              else if((key_dlyms1>30))
              {
                 key_dlyms1 = 0;  
              }
              if(key_dlyms1 == 0) 
              {
                key_data = key_temp;
//                OSSemPost(msg_key);
              }  
            }  
          }  
        }  
        else
        {
          key_state=3;
        }  
        break;
      case 3:
        if(key_speed_up==0) 
        {
          key_data = key_valid;   
        }
        key_state = 0;
        break;        
    }  
    
    if(key_data)
    {
      KeyDataMsg = key_data;
      OSMboxPost(KeyMbox,(void *)&KeyDataMsg);
    }  
    
    OSTimeDlyHMSM(0, 0,0,5);  
  }   
}

/***************************************************************************************************
***************************************************************************************************/
