/****************************************Copyright (c)****************************************************
** File Name:           usb_virtual_com_port.c
** Created By:          lisonchen
** Created date:        2015-09-29
** Version:             v1.00
** Descriptions:        usb virtual com port
**
*********************************************************************************************************/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "includes.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
extern __IO  uint32_t packet_sent;
extern __IO  uint32_t packet_receive;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main.
* Descriptioan    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
//usb virtual com port初始化连接
void Connect_To_COM(void)// *p_arg)
{
  
//  (void)p_arg;
   
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  
} 

//数据发送（一次发送的数据不能大于63）
void USB_Send_Data(uint8_t *ptrBuffer, uint8_t Send_length)
{
    if (bDeviceState == CONFIGURED)
    {
          if(Send_length > 63)
          {      
              s8 SendCount = Send_length / 63;
              Send_length = Send_length%63;
              while(SendCount--)
              {
                  CDC_Send_DATA (ptrBuffer,63);
                  ptrBuffer += 63;
                  
                  Delay_us(100);//不加延时，会出现连接有问题
              }
              CDC_Send_DATA (ptrBuffer,Send_length);
          }
          else
          {
              CDC_Send_DATA (ptrBuffer,Send_length);
          }
    }
}


uint32_t USB_Receive_Data(uint8_t *ptrBuffer)
{
    uint32_t  receive_length = 0;
  
    if (bDeviceState == CONFIGURED)
    {
//      CDC_Receive_DATA();

      while (Receive_length  != 0)
      {
          for(uint32_t i = 0; i < Receive_length; i++)
          {
              ptrBuffer[i] = Receive_Buffer[i];

          }
          receive_length += Receive_length;
          
          ptrBuffer += Receive_length;
          
          Receive_length = 0;
          
          CDC_Receive_DATA();//接收完一次数据后就会无法接收，需要再次设置接收生效。发送同理
          
          Delay_us(100);//要有一定延时，否则USB节点没那么快重新接收到数据          
      }
      return receive_length;
    }
    
    return 0;

}

//接收到的数据返回发送回去（测试用，发送的数据不能大于63）
void USB_Receive_Data_Send(void)
{
  
  
    if (bDeviceState == CONFIGURED)
    {
      CDC_Receive_DATA();//usb_endp.c   EP3_OUT_Callback
      /*Check to see if we have data yet */
      while(!packet_receive);
      while(Receive_length  != 0)
      {
          CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);
          Receive_length = 0;
          CDC_Receive_DATA();
      }
      
    }

}
//断开usb virtual com port
void USB_Disconnect(void)
{

  Disconnect_USB_Virtual_COM_Port();
  
}