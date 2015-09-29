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
void Connect_To_COM(void)// *p_arg)
{
  
//  (void)p_arg;
  
  
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  
  while (1)
  {
    if (bDeviceState == CONFIGURED)
    {
      CDC_Receive_DATA();
      /*Check to see if we have data yet */
      if (Receive_length  != 0)
      {
        if (packet_sent == 1)
          CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);
        Receive_length = 0;
      }
    }
//    OSTimeDlyHMSM(0, 0,0,500);
  }
} 


