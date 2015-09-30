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

//数据发送
void USB_Send_Data(uint8_t *ptrBuffer, uint8_t Send_length)
{
    if (bDeviceState == CONFIGURED)
    {
        CDC_Send_DATA (ptrBuffer,Send_length);
    }
}


uint32_t USB_Receive_Data(uint8_t *ptrBuffer)
{
    uint32_t  receive_length = 0;
  
    if (bDeviceState == CONFIGURED)
    {
//      CDC_Receive_DATA();

      if (Receive_length  != 0)
      {
          for(uint32_t i = 0; i < Receive_length; i++)
          {
              ptrBuffer[i] = Receive_Buffer[i];

          }
          receive_length = Receive_length;
          
          Receive_length = 0;
          
          CDC_Receive_DATA();//接收完一次数据后就会无法接收，需要再次设置接收生效。发送同理
          
          return receive_length;
      }
    }
    
    return 0;

}

//接收到的数据返回发送回去（测试用）
void USB_Receive_Data_Send(void)
{
  
    if (bDeviceState == CONFIGURED)
    {
      CDC_Receive_DATA();//usb_endp.c   EP3_OUT_Callback
      /*Check to see if we have data yet */
      while(!packet_receive);
      if (Receive_length  != 0)
      {
          CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);
          Receive_length = 0;
      }
    }

}
//断开usb virtual com port
void USB_Disconnect(void)
{

  Disconnect_USB_Virtual_COM_Port();
  
}