#include "includes.h"

extern u16 SPI_W25X_ReadID(void);

void du_hardware_test(void)
{
    u8  *m_keydata,err=0;

//LCD����

    ZTM_RectangleFill (0,0,239,319,RED);
    OSTimeDlyHMSM(0, 0,1,0);
    ZTM_RectangleFill (0,0,239,319,GREEN);
    OSTimeDlyHMSM(0, 0,1,0);      
    ZTM_RectangleFill (0,0,239,319,BLUE);
    OSTimeDlyHMSM(0, 0,1,0);
    ZTM_RectangleFill (0,0,80,319,WHITE);
    OSTimeDlyHMSM(0, 0,0,10);      
    ZTM_RectangleFill (80,0,160,319,LGRAY);
    OSTimeDlyHMSM(0, 0,0,10); 
    ZTM_RectangleFill (160,0,239,319,DGRAY);
    OSTimeDlyHMSM(0, 0,1,500); 

//    
    ZTM_FullScreenImageDisp(300);
    ZTM_RectangleFill (0,0,127,35,BLUE);
    OSTimeDlyHMSM(0, 0,0,10);
//    ZTM_RectangleFill (0,35,239,319,LGRAY);
//    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,1,2,32,0,WHITE ,0, "Ӳ������");  

//rtc ����    
//    TXM_StringDisplay(0,70,35,24,0,BLACK ,0, "rtc ok!"); //rtc
//    OSTimeDlyHMSM(0, 0,0,10);

//usb ����
//    TXM_StringDisplay(0,70,85,24,0,BLACK ,0, "usb ok!"); //usb  
//    OSTimeDlyHMSM(0, 0,0,10);    

//spi flash����    
    SPI_FLASH_TYPE = SPI_W25X_ReadID();
    if(SPI_FLASH_TYPE==W25Q64)
    {
      TXM_StringDisplay(0,70,60,24,0,BLACK ,0, "flash ok!"); //spi flash
    } 
    else
    {
      TXM_StringDisplay(0,70,60,24,0,BLACK ,0, "flash fail!"); //spi flash
    }
    
    OSTimeDlyHMSM(0, 0,0,10);

//��������    
//    TXM_StringDisplay(0,10,120,24,1,RED ,DGRAY, " P  ");   
//    OSTimeDlyHMSM(0, 0,0,10);   
    TXM_StringDisplay(0,70,120,24,1,RED ,DGRAY, " F1 ");           
    OSTimeDlyHMSM(0, 0,0,10);   
    TXM_StringDisplay(0,130,120,24,1,RED ,DGRAY, " F2 ");            
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,190,120,24,1,RED ,DGRAY, " F3 "); 
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,100,160,24,1,RED ,DGRAY, " �� ");
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,100,240,24,1,RED ,DGRAY, " �� ");            
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,60,200,24,1,RED ,DGRAY, " �� ");            
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,140,200,24,1,RED ,DGRAY, " �� "); 
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,50,280,24,1,RED ,DGRAY, " SET ");            
    OSTimeDlyHMSM(0, 0,0,10);
    TXM_StringDisplay(0,150,280,24,1,RED ,DGRAY, " ESC ");     
    OSTimeDlyHMSM(0, 0,0,10);
  
   while(1)
   {
      m_keydata = OSMboxPend(KeyMbox,100,&err);
      
      if(err == OS_ERR_TIMEOUT)//������Ϣ��ʱ
      {
       
      } 
      else if(m_keydata[0] == KEY_ESC)
      {
          TXM_StringDisplay(0,150,280,24,1,RED ,CYAN, " ESC "); 
          OSTimeDlyHMSM(0, 0,2,0);//��ESC��2s���Ƴ�����
          break;  
      }
      else 
      {
          switch(m_keydata[0])
          {
            case KEY_POWER:             
              TXM_StringDisplay(0,10,120,24,1,RED ,NAVY, " P  ");
              break;
            case KEY_F1:
              TXM_StringDisplay(0,70,120,24,1,RED ,DGREEN, " F1 ");   
              break;               
            case KEY_F2:             
              TXM_StringDisplay(0,130,120,24,1,RED ,DCYAN, " F2 ");   
              break; 
            case KEY_F3:
              TXM_StringDisplay(0,190,120,24,1,RED ,MAROON, " F3 "); 
              break; 
            case KEY_UP:             
              TXM_StringDisplay(0,100,160,24,1,RED ,PURPLE, " �� ");
              break;
            case KEY_DOWN:
              TXM_StringDisplay(0,100,240,24,1,RED ,OLIVE, " �� ");  
              break;               
            case KEY_LEFT:             
              TXM_StringDisplay(0,60,200,24,1,RED ,MAGENTA, " �� ");    
              break; 
            case KEY_RIGHT:
              TXM_StringDisplay(0,140,200,24,1,RED ,YELLOW, " �� "); 
              break;
            case KEY_SET:             
              TXM_StringDisplay(0,50,280,24,1,RED ,GREEN, " SET ");   
              break; 
//            case KEY_ESC:
//              TXM_StringDisplay(0,150,280,24,1,RED ,CYAN, " ESC "); 
//              break;              
          }  
       } 

     
   }

}
