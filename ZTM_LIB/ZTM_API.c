/****************************************Copyright (c)****************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           ZTM_API.c
** Last modified Date:  2011-06-01
** Last Version:        v1.00
** Description:         ZTM驱动库应用层驱动函数
**
**--------------------------------------------------------------------------------------------------------
** Created By:          He Zengfu
** Created date:        2011-06-01
** Version:             v1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         WangWenXiong
** Modified date:       2012-02-24
** Version:             V1.01
** Description:         增加 ZTM_HandOn函数；
**                      增加 ZTM_SetIdleType函数；
**                      增加 ZTM_SetSysMouseDis函数；
**                      修改 ZTM_ClrScreen函数；
**                      删除 ZTM_TouchMode函数；
**                      增加 ZTM_CheckTouchPos函数；
**                      删除 ZTM_BeepOnOff函数；
**                      增加 ZTM_SetBuzzer函数；
**                      修改 ZTM_LightTimeTouch函数；
**                      增加 ZTM_SetBaudrate函数；
**                      增加 ZTM_SetDisplayBuf函数；
**                      增加 ZTM_SetAck函数；
**                      增加 ZTM_SetTouchType函数；
**                      增加 ZTM_SetBuzzerType函数；
**                      增加 ZTM_SetTxtBackgroundType函数；
**                      增加 ZTM_SetSysMouseType函数；
**                      增加 ZTM_SetSumCheckType函数；
**                      增加 ZTM_SetTouchDelay函数；
**                      增加 ZTM_ReadDeviceInfo函数；
**                      增加 ZTM_OptDisBufDirectly函数；
**                      增加 ZTM_FileDownload函数。
**
*********************************************************************************************************/
#include "ZTM.h"

/*********************************************************************************************************
  常量定义
*********************************************************************************************************/
INT8U const __GucFrameHead[1]         = {0xAA};                         /* 帧头 1字节                   */
INT8U const __GucFrameTail[4]         = {0xCC, 0x33, 0xC3, 0x3C};       /* 帧尾 4字节                   */
INT8U const __GucFrameTouchCal[5]     = {0xE4, 0x55, 0xAA, 0x5A, 0xA5}; /* 触摸屏校准命令               */
INT8U const __GucFrameLight[4]        = {0x55, 0xAA, 0x5A, 0xA5};       /* 键控背光命令                 */
INT8U const __GucFrameFileDownload[4] = {0xF2, 0xF2, 0x5A, 0xA5};       /* 字库或配置文件下载命令部分   */
                                                                        /* 参数                         */
INT8U ZtmSendBuff[1500];
INT16U ZtmSendCnt=0;

/*********************************************************************************************************
** 函数名称:  __SendByte
** 函数功能:  单字节发送函数
** 输入参数:  ucData：       数据
** 输出参数： 无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendByte (INT8U ucData)
{
	ZtmSendBuff[++ZtmSendCnt] = ucData;
	
/*	
    if (ZTM_BusyStat()) {                                               // 串口屏忙碌                   
        do {                                                            // 等待直到恢复空闲              
            if (!ZTM_BusyStat()) {
                uartSendChar(ucData);
                break;
            }
            ZTM_Delay(1);
        } while (1);
    } else {                                                            // 串口屏空闲，直接发送          
        uartSendChar(ucData);
    }
*/
}

/*********************************************************************************************************
** 函数名称:  __SendDByte
** 函数功能:  双字节发送函数
** 输入参数:  usData：  数据
** 输出参数： 无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendDByte (INT16U usData)
{
	ZtmSendBuff[++ZtmSendCnt] = usData>>8;
	ZtmSendBuff[++ZtmSendCnt] = usData;
  //  __SendByte((usData>> 8) & 0xFF);                                    /* 发送高8位数据                */
  //  __SendByte(usData & 0xFF);                                          /* 发送低8位数据                */
}

/*********************************************************************************************************
** 函数名称:  __SendByteStr
** 函数功能:  单字节字符串发送函数
** 输入参数:  *pucStr:       要发送的命令字符串指针
**            ulNum:         要发送的数据个数
** 输出参数： 无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendByteStr (INT8U const *pucStr, INT32U ulNum)
{
    INT32U i;

    for (i = 0; i < ulNum; i++) {                                       /* 发送指定字节数据             */
        __SendByte(*pucStr++);
    }
}

/*********************************************************************************************************
** 函数名称:  __SendDByteStr
** 函数功能:  双字节字符串发送函数
** 输入参数:  pucStr：  要发送的命令字符串指针
**            ulNum：   要发送的数据个数
** 输出参数： 无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendDByteStr (INT16U *pucStr, INT32U ulNum)
{
    INT32U i;

    for (i = 0; i < ulNum; i++) {                                       /* 发送指定字节数据             */
        __SendDByte(*pucStr++);
    }
}

/*********************************************************************************************************
** 函数名称:  __SendHead
** 函数功能:  发送命令帧头
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendHead (void)
{
	ZtmSendCnt=0;
	ZtmSendBuff[ZtmSendCnt] = 0XAA;
	
  //  __SendByteStr(__GucFrameHead, 1);
}

/*********************************************************************************************************
** 函数名称:  __SendTail
** 函数功能:  发送命令帧尾
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
static void __SendTail (void)
{
	ZtmSendBuff[++ZtmSendCnt] = 0xCC,
	ZtmSendBuff[++ZtmSendCnt] = 0x33,
	ZtmSendBuff[++ZtmSendCnt] = 0xC3,
	ZtmSendBuff[++ZtmSendCnt] = 0x3C,
	
	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);	
	//__SendByteStr(__GucFrameTail, 4);
}

/****************************** 串口显示终端应用层函数 **************************************************/

/*
 * 握手指令
 */

/*********************************************************************************************************
** 函数名称:  ZTM_HandOn
** 函数功能:  发送握手指令
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_HandOn (void)
{
    __SendHead();                                                       /* 发送帧头                     */
	
    __SendByte(0x00);                                                   /* 发送命令                     */
	
    __SendTail();                                                       /* 发送帧尾                     */
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetIdleType
** 函数功能:  终端指令缓存状体引脚（Busy）有效电平设置
** 输入参数:  ucIdleType：终端指令缓存状体引脚有效电平设置参数；0x00——低电平有效，0xFF——高电平有效
** 输出参数:  无
** 返 回 值:  正确返回1，错误返回0
*********************************************************************************************************/
INT8U ZTM_SetIdleType (INT8U ucIdleType)
{
	/*
     *  参数检查
     */
	if ((ucIdleType > 0x00) && (ucIdleType < 0xFF)) {
		return (0);
	}
	
    __SendHead();                                                       /* 发送帧头                     */
	
    __SendByte(0x00);                                                   /* 发送命令                     */
	__SendByte(ucIdleType);                                             /* 发送参数值                   */
	
    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*
 *  显示系统鼠标
 */
/*********************************************************************************************************
** 函数名称:  ZTM_SetSysMouseDis
** 函数功能:  系统鼠标显示设置
** 输入参数:  ucMouseID：系统鼠标图片ID；
**            usX      ：显示起始点的X坐标
**            usY      ：显示起始点的Y坐标
** 输出参数:  无
** 返 回 值:  正确返回1，错误返回0
*********************************************************************************************************/
INT8U ZTM_SetSysMouseDis (INT8U ucMouseID, INT16U usX, INT16U usY)
{
	/*
     *  参数检查
     */
	if ((usX >= ZTM_XADDR_MAX) || (usY >= ZTM_YADDR_MAX)) {
		return (0);
	}
	
	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x21;
	
	ZtmSendBuff[2] = ucMouseID;		/* 发送系统鼠标图片ID           */
	ZtmSendBuff[3] = usX;					/* 发送显示起始点X坐标          */
	ZtmSendBuff[4] = usX;					
	ZtmSendBuff[5] = usY;					/* 发送显示起始点Y坐标          */
	ZtmSendBuff[6] = usY;
	
	ZtmSendCnt = 6;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
	
	return (1);
}

/*
 * 显示参数配置
 */
/*********************************************************************************************************
** 函数名称:  ZTM_SetColor
** 函数功能:  设置调色板
** 输入参数:  usFcolor：     前景色
**            usBcolor：     背景色
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_SetColor (INT16U usFcolor, INT16U usBcolor)
{
	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x40;
		
	ZtmSendBuff[2] = usFcolor>>8;				/* 发送前景色                   */
	ZtmSendBuff[3] = usFcolor;			
	ZtmSendBuff[4] = usBcolor>>8;				/* 发送背景色                   */
	ZtmSendBuff[5] = usBcolor;			
 
	ZtmSendCnt = 5;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetCharDis
** 函数功能:  设置字符显示间距
** 输入参数:  ucDx：         字间距（横向） 0-255
**            ucDy：         行间距（纵向） 0-255
** 输出参数:  正确返回1，否则返回0
** 返 回 值:  无
*********************************************************************************************************/
INT8U ZTM_SetCharDis (INT8U ucDx, INT8U ucDy)
{
	/*
	 *  参数检查
	 */
//	if ((ucDx >= CHAR_XSTEP_MAX) || (ucDy  >= CHAR_YSTEP_MAX)) return (0);
		
	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x41;
		
	ZtmSendBuff[2] = ucDx;				 
	ZtmSendBuff[3] = ucDy;			

	ZtmSendCnt = 3;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);

	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetCursor
** 函数功能:  设置光标显示
** 输入参数:  ucMode：       光标显示模式  0:关   1:开
**            usX：          横坐标（位置）
**            usY：          纵坐标
**            ucWide：       光标宽度，0x01~0x1f
**            ucHeight：     光标高度，0x01~0x1f
** 输出参数:  正确返回1，否则返回0
** 返 回 值:  无
*********************************************************************************************************/
INT8U ZTM_SetCursor (INT8U ucMode, INT16U usX, INT16U usY, INT8U ucWide, INT8U ucHeight)
{
    /*
     * 参数检查
     */
    if ((ucMode > 1) || (usX > ZTM_XADDR_MAX) || (usY > ZTM_YADDR_MAX) || (ucWide > CURSOR_WIDE_MAX) ||
        (ucHeight > CURSOR_HEIGHT_MAX) ) {
            return (0);
    }

		
	ZtmSendBuff[0] = 0xAA;							/* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x44;
		
	ZtmSendBuff[2] = ucMode;				 		/* 发送光标显示模式             */
	
	ZtmSendBuff[3] = usX>>8;						/* 发送x坐标                    */
	ZtmSendBuff[4] = usX;
	ZtmSendBuff[5] = usY>>8;						/* 发送y坐标                    */
	ZtmSendBuff[6] = usY;
	
	ZtmSendBuff[7] = ucWide;						/* 发送光标宽度                 */
	ZtmSendBuff[8] = ucHeight;					/* 发送光标高度                 */

	ZtmSendCnt = 8;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
 
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetFilterColor
** 函数功能:  设置过滤色
** 输入参数:  usFilterColorLow ~ usFilterColorHigh  过滤颜色范围
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_SetFilterColor (INT16U usFilterColorLow, INT16U usFilterColorHigh)
{
	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x10;
		
	ZtmSendBuff[2] = usFilterColorLow>>8;				 
	ZtmSendBuff[3] = usFilterColorLow;				 
	ZtmSendBuff[4] = usFilterColorHigh>>8;;			
	ZtmSendBuff[5] = usFilterColorHigh;			

	ZtmSendCnt = 5;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
}

/*
 *  文本显示
 */
/*********************************************************************************************************
** 函数名称:  ZTM_PutText
** 函数功能:  指定坐标位置(x, y)写汉字、ASCII码字符串
** 输入参数:  usX：          x坐标
**            usY：          y坐标
**            *pucStr：      字符串指针
**            ucType：       字库类型
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_PutText (INT16U usX, INT16U usY, INT8U *pucStr, INT8U ucType)
{
	INT16U i,j;
    /*
     *  参数检查
     */
    if ((usX >= ZTM_XADDR_MAX) || (usY  >= ZTM_YADDR_MAX)) {
        return (0);
    }

	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	
	switch (ucType) /* 字库类型选择                 */
	{                                                   
		case ASC_6x8:
			ZtmSendBuff[1] = 0x53;                                               /* 6*8点阵ASCII码显示           */
			break;

		case GBK_12x12:                                                 /* 12*12点阵字符串显示          */
    	ZtmSendBuff[1] = 0x6E;
			break;

		case GBK_16x16:                                                 /* 16*16点阵字符串显示          */
			ZtmSendBuff[1] = 0x54;
			break;

		case GBK2132_24x24:                                             /* 24*24点阵字符串显示          */
			ZtmSendBuff[1] = 0x6F;
			break;

		case GBK2132_32x32:                                             /* 32*32点阵字符串显示          */
			ZtmSendBuff[1] = 0x55;
			break;

			default:
			break;
	}

	ZtmSendBuff[2] = usX>>8; 		/* 发送x坐标                    */
	ZtmSendBuff[3] = usX;
	ZtmSendBuff[4] = usY>>8; 		/* 发送y坐标                    */
	ZtmSendBuff[5] = usY;
  
	j = strlen((char *)pucStr);	/* 发送显示字符                 */
	for(i=0;i<j;i++)
	{
		ZtmSendBuff[6+i] = pucStr[i];
	}		

	ZtmSendCnt = 5+i;         	/* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;
		
	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
		
	return (1);
}

/*
 *  文本显示
 */
/*********************************************************************************************************
** 函数名称:  ZTM_PutText
** 函数功能:  指定坐标位置(x, y)写汉字、ASCII码字符串
** 输入参数:  usX：          x坐标
**            usY：          y坐标
**            *pucStr：      字符串指针
**            ucType：       字库类型
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U TXM_StringDisplay(u16 tid, INT16U usX, INT16U usY,
      INT8U size,INT8U BCdis,INT16U usFcolor ,INT16U usBcolor, INT8U *pucStr)
{
	INT16U i,j;
  /*
  *  参数检查
  */
  if ((usX >= ZTM_XADDR_MAX) || (usY  >= ZTM_YADDR_MAX)) {
//    return (0);
  }
  
  if(tid)
  {  
    TXM_FillTextWidget (tid, (void*)pucStr);
  
    return(1);
  } 
  
	ZtmSendBuff[0] = 0xAA;	  /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x98;    /* 用户字库                 */

	ZtmSendBuff[2] = usX>>8; 		/* 发送x坐标                    */
	ZtmSendBuff[3] = usX;
	ZtmSendBuff[4] = usY>>8; 		/* 发送y坐标                    */
	ZtmSendBuff[5] = usY;
  
  switch(size)
  {  
    case 12:
      ZtmSendBuff[6] = 0x20;
      ZtmSendBuff[7] = 0x02;
      ZtmSendBuff[8] = 0x00;
      break;
    case 32:
      ZtmSendBuff[6] = 0x23;
      ZtmSendBuff[7] = 0x01;
      ZtmSendBuff[8] = 0x03;
      break;
    case 24:
      ZtmSendBuff[6] = 0x22;
      ZtmSendBuff[7] = 0x01;
      ZtmSendBuff[8] = 0x02;
      break;
    default: //16
      ZtmSendBuff[6] = 0x21;
      ZtmSendBuff[7] = 0x02;
      ZtmSendBuff[8] = 0x01;   
  }
  
  if(BCdis)
  {
    ZtmSendBuff[7] |= 0xd0;
  } 
  else
  {
    ZtmSendBuff[7] |= 0x90;
  }  
  
	ZtmSendBuff[9] = usFcolor>>8; 		/*                      */
	ZtmSendBuff[10] = usFcolor;
	ZtmSendBuff[11] = usBcolor>>8; 		/*                     */
	ZtmSendBuff[12] = usBcolor;
  
	j = strlen((char *)pucStr);	/* 发送显示字符                 */
	for(i=0;i<j;i++)
	{
		ZtmSendBuff[13+i] = pucStr[i];
	}		

	ZtmSendCnt = 12+i;         	/* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;
		
	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
		
	return (1);
}

 

INT8U TXM_DigitDisplay(u16 tid,u16 x,u16 y,u8 size,u8 BCdis,u16 usFcolor,u16 usBcolor,u32 dat,u8 bits,u8 dot,u8 align)
{
  u8 a[20]={0,0,0,0,0,0,0,0,0,0};
	INT16U i,j;
    
	for(i=0;i<bits;i++)
	{		
		a[bits-i-1] = (dat%10) + 0x30;
		dat = dat/10; 
	}
  
  if(dot)
  {
    for(i=0;i<dot;i++)
    {
      a[bits-i] = a[bits-i-1]; 
    }  
    
    a[bits-dot] = '.';
    bits++;
  }  
  
  if(align != ALIGN_ZERO_RIGHT)
  {  
    for(i=0;i<bits-1;i++)
    {
      if((a[i]==0x30) && (a[i+1] != '.'))
      {
        a[i] = 0x20;
      } 
      else
      {
        break;
      }  
    }  
    if(align == ALIGN_LEFT) 
    {
      for(i=0;i<bits-1;i++)
      {
        if(a[0]==0x20)
        {
          //左移一位
          for(j=0;j<bits-1;j++)
          {
            a[j] = a[j+1];
          }    
          a[bits-1] = 0x20;
        }  
        else
        {
          break;
        }  
      }
    }  
  }

  if(tid)
  {  
    TXM_FillTextWidget (tid, (void*)a);
  }
  else
  {  
    TXM_StringDisplay (0,x, y, size, BCdis, usFcolor, usBcolor, a);
  }
  
  return (1);
}

/*
 *  文本控件
 */
/*********************************************************************************************************
** 函数名称:  TXM_FillTextWidget
** 函数功能:  指定坐标位置(x, y)写汉字、ASCII码字符串
** 输入参数:  usX：          x坐标
**            usY：          y坐标
**            *pucStr：      字符串指针
**            ucType：       字库类型
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U TXM_FillTextWidget (INT16U Tid, char *pucStr)
{
	INT16U i,j;
  /*
  *  参数检查
  */
 // if ((usX >= ZTM_XADDR_MAX) || (usY  >= ZTM_YADDR_MAX)) {
//    return (0);
//  }

	ZtmSendBuff[0] = 0xAA;	  /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x97;    /* 功能码                   */

	ZtmSendBuff[2] = Tid>>8; 		 
	ZtmSendBuff[3] = Tid;
  
	j = strlen((char *)pucStr);	/* 发送显示字符                 */
  
  if(j>50)
  {
    while(1);
  }  
  
	for(i=0;i<j;i++)
	{
		ZtmSendBuff[4+i] = pucStr[i];
	}		
	
	ZtmSendCnt = 3+i;         	/* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;
		
	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
		
	return (1);
}



/*
 *  数字显示
 */
/*********************************************************************************************************
** 函数名称:  TXM_DigitDisplay
** 函数功能:  指定坐标位置(x, y)写汉字、ASCII码字符串
** 输入参数:  usX：          x坐标
**            usY：          y坐标
**            *pucStr：      字符串指针
**            ucType：       字库类型
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U TXM_DigitDisplayWidget (INT16U Tid, INT16U len, INT32U dat)
{
	INT16U i,j;
	
	INT8U a[10]={0,0,0,0,0,0,0,0,0,0};
	
	for(i=0;i<len;i++)
	{		
		a[8-i] = dat%10;
		dat = dat/10;
	}
   
	j=8;
	for(i=9-len;i<8;i++)
	{		
		if(a[i] != 0)
		{
			j = i;
			break;
		}	
	}
	
	for(;i<9;i++)
	{		
		a[i] += 0x30;
	}
	
	
	
	TXM_FillTextWidget (Tid, (void*)&a[j]);
		
	return (1);
}



/*
 *  置点
 */
/*********************************************************************************************************
** 函数名称:  ZTM_PutDot
** 函数功能:  指定位置和颜色画点
** 输入参数:  usxAddr：      x轴坐标
**            usyaddr：      y轴坐标
**            usColor：      点填充颜色
** 输出参数:   无
** 返 回 值:      正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_PutDot (INT16U usxAddr, INT16U usyAddr, INT16U usColor)
{
    /*
     *  参数检查
     */
    if ((usxAddr >= ZTM_XADDR_MAX) || (usyAddr  >= ZTM_YADDR_MAX)) {
        return (0);
    }

    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x4F);                                                   /* 发送命令                     */
    __SendDByte(usColor);                                               /* 发送颜色值                   */
    __SendDByte(usxAddr);                                               /* 发送x坐标                    */
    __SendDByte(usyAddr);                                               /* 发送y坐标                    */

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_PutNDot
** 函数功能:  指定位置和颜色画多个点
** 输入参数:  *pusStr：      点坐标指针
**            ulNum：        点个数
**            usColor：      点填充颜色
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
void ZTM_PutNDot (INT16U *pusStr, INT32U ulNum, INT16U usColor)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x4F);                                                   /* 发送命令                     */
    __SendDByte(usColor);                                               /* 发送颜色值                   */
    __SendDByteStr(pusStr, ulNum * 2);                                  /* 发送点坐标                   */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*********************************************************************************************************
** 函数名称:  ZTM_BColorPutNDot
** 函数功能:  背景色画多个点(删除点)
** 输入参数:  *pusStr：      点坐标指针
**            ulNum：        点个数
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
void ZTM_BColorPutNDot (INT16U *pusStr, INT32U ulNum)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x50);                                                   /* 发送命令                     */
    __SendDByteStr(pusStr, ulNum * 2);                                  /* 发送点坐标                   */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*********************************************************************************************************
** 函数名称:  ZTM_FColorPutNDot
** 函数功能:  前景色画多个点
** 输入参数:  *pusStr：      点坐标指针
**            ulNum：        点个数
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
void ZTM_FColorPutNDot (INT16U *pusStr, INT32U ulNum)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x51);                                                   /* 发送命令                     */
    __SendDByteStr(pusStr, ulNum * 2);                                  /* 发送点坐标                   */

    __SendTail();                                                       /* 发送帧尾                     */
}


/*
 *  画线段和多边形
 */
/*********************************************************************************************************
** 函数名称:  ZTM_FColorPutLine
** 函数功能:  指定两点(x1, y1)，(x2, y2)用前景色画线
** 输入参数:  usX1：         x1坐标
**            usY1：         y1坐标
**            usX2：         x2坐标
**            usY2：         y2坐标
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_FColorPutLine (INT16U usX1, INT16U usY1, 
			             INT16U usX2, INT16U usY2)
{
    /*
     *  参数检查
     */
    if ((usX1 > ZTM_XADDR_MAX) || (usX2 > ZTM_XADDR_MAX) || (usY1 > ZTM_YADDR_MAX) ||
        (usY2 > ZTM_YADDR_MAX) ) {
            return (0);
        }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x56);                                                   /* 发送命令                     */
    __SendDByte(usX1);                                                  /* 发送点坐标                   */
    __SendDByte(usY1);
    __SendDByte(usX2);
    __SendDByte(usY2);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_BColorPutLine
** 函数功能:  指定两点(x1, y1)，(x2, y2)用背景色画线
** 输入参数:  usX1：         x1坐标
**            usY1：         y1坐标
**            usX2：         x2坐标
**            usY2：         y2坐标
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_BColorPutLine (INT16U usX1, INT16U usY1, 
			             INT16U usX2, INT16U usY2)
{
    /*
     *  参数检查
     */
    if ((usX1 > ZTM_XADDR_MAX) || (usX2 > ZTM_XADDR_MAX) || (usY1 > ZTM_YADDR_MAX) ||
        (usY2 > ZTM_YADDR_MAX) ) {
            return (0);
        }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x6D);                                                   /* 发送命令                     */
    __SendDByte(usX1);                                                  /* 发送点坐标                   */
    __SendDByte(usY1);
    __SendDByte(usX2);
    __SendDByte(usY2);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_PutSpectral
** 函数功能:  前景色快速显示频谱
** 输入参数:  usX、usY:      起点坐标
**            usHeightMax:   频谱最大幅值
**            *pusStr:       usHeight0～n——频谱图X轴方向按像素递增对应的频谱幅值
**            ulNum：        频谱线条数
** 输出参数： 无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_PutSpectral (INT16U usX, INT16U usY, 
		              INT16U usHeightMax, INT16U *pusStr, 
		              INT32U ulNum)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x75);                                                   /* 发送命令                     */
    __SendDByte(usX);                                                   /* 发送起点X坐标                */
    __SendDByte(usY);                                                   /* 发送起点Y坐标                */
    __SendDByte(usHeightMax);                                           /* 发送频谱最大幅值             */
    __SendDByteStr(pusStr, ulNum);

    __SendTail();                                                       /* 发送帧尾                     */

}

/*********************************************************************************************************
** 函数名称:  ZTM_PutFoldline
** 函数功能:  前景色快速显示折线图
** 输入参数:  usX：          起点坐标
**            ucXdis：       X轴步进增加量
**            *pusStr：      Y0～Yn——折线图y值指针
**            ulNum：        折线拐点数
** 输出参数： 无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_PutFoldline (INT16U usX, INT8U ucXdis, 
		               INT16U *pusStr, INT32U ulNum)
{
    /*
     *  参数检查
     */
/*	
    if ((usX >= ZTM_XADDR_MAX) || (ucXdis >= ZTM_XADDR_MAX)) {
        return (0);
    }
*/	
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x76);                                                   /* 发送命令                     */
    __SendDByte(usX);                                                   /* 发送起点x坐标                */
    __SendByte(ucXdis);                                                 /* 发送x方向步距                */
    __SendDByteStr(pusStr, ulNum);                                      /* 折线图y坐标值                */

    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*
 *  圆弧或圆域
 */
/*********************************************************************************************************
** 函数名称:  ZTM_Circle
** 函数功能:  画圆
** 输入参数:  ucType：       0x00:前景色反色显示圆弧
**                           0x01:前景色显示圆弧
**                           0x02:前景色反色显示圆域
**                           0x03:前景色显示圆域
**            usx0Addr：     圆心x0坐标
**            usy0Addr：     圆心y0坐标
**            usR：          半径
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_Circle (INT8U ucType, INT16U usx0Addr, 
	              INT16U usy0Addr, INT16U usR)
{
    if ((ucType > 1) || (usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || ((usR * 2)  >= ZTM_YADDR_MAX)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x57);                                                   /* 发送命令                     */
    __SendByte(ucType);                                                 /* 指定type                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usR);                                                   /* 发送直径                     */

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}


/*
 * 画椭圆
 */
/*********************************************************************************************************
** 函数名称:  ZTM_EllipseFill
** 函数功能:  画实心椭圆
** 输入参数:  usx0Addr：     圆心x0坐标
**            usy0Addr：     圆心y0坐标
**            usRL：         长轴
**            usRS：         短轴
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_EllipseFill (INT16U usx0Addr, INT16U usy0Addr, INT16U usRL, INT16U usRS)
{
    if ((usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || ((usRL * 2)  >= ZTM_XADDR_MAX) || ((usRS * 2)  >= ZTM_YADDR_MAX)) {
//        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x60);                                                   /* 发送命令                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usRL);                                                  /* 发送长短轴                   */
    __SendDByte(usRS);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_Ellipse
** 函数功能:  画空心椭圆
** 输入参数:  usx0Addr：     圆心x0坐标
**            usy0Addr：     圆心y0坐标
**            usRL：         长轴
**            usRS：         短轴
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_Ellipse (INT16U usx0Addr, INT16U usy0Addr, INT16U usRL, INT16U usRS)
{
    if ((usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || ((usRL * 2)  >= ZTM_XADDR_MAX) || ((usRS * 2)  >= ZTM_YADDR_MAX)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x61);                                                   /* 发送命令                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usRL);                                                  /* 发送长短轴                   */
    __SendDByte(usRS);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}


/*
 *  矩形框
 */
/*********************************************************************************************************
** 函数名称:  ZTM_FcolorRectangle
** 函数功能:  前景色显示矩形框
** 输入参数:  usx0Addr：     x0坐标
**            usy0Addr：     y0坐标
**            usx1Addr：     x1坐标
**            usy1Addr：     y1坐标
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U  ZTM_FcolorRectangle (INT16U usx0Addr, INT16U usy0Addr, 
		                    INT16U usx1Addr, INT16U usy1Addr)
{
    if ((usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || (usx1Addr  >= ZTM_XADDR_MAX) || (usy1Addr  >= ZTM_YADDR_MAX)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x59);                                                   /* 发送命令                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usx1Addr);
    __SendDByte(usy1Addr);

    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_Square
** 函数功能:  画正方形
** 输入参数:  usx0Addr：     x0坐标
**            usy0Addr：     y0坐标
**            usWidth：      边长
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_Square (INT16U usx0Addr, INT16U usy0Addr, INT16U usWidth)
{
    ZTM_FcolorRectangle(usx0Addr, usy0Addr, (usx0Addr + usWidth), (usy0Addr + usWidth));
}


/*********************************************************************************************************
** 函数名称:  ZTM_BcolorRectangle
** 函数功能:  背景色显示矩形框
** 输入参数:  usx0Addr：     x0坐标
**            usy0Addr：     y0坐标
**            usx1Addr：     x1坐标
**            usy1Addr：     y1坐标
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U  ZTM_BcolorRectangle (INT16U usx0Addr, INT16U usy0Addr, 
	                        INT16U usx1Addr, INT16U usy1Addr)
{
    if ((usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || (usx1Addr  >= ZTM_XADDR_MAX) || (usy1Addr  >= ZTM_YADDR_MAX)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x69);                                                   /* 发送命令                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usx1Addr);
    __SendDByte(usy1Addr);

    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*
 *  区域操作
 */
/*********************************************************************************************************
** 函数名称:  ZTM_RectangleFill
** 函数功能:  指定区域填充
** 输入参数:  usx0Addr:      x0坐标
**            usy0Addr：     y0坐标
**            usx1Addr：     x1坐标
**            usy1Addr：     y1坐标
**            uiColor:       填充颜色
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_RectangleFill (INT16U usx0Addr, INT16U usy0Addr, 
                         INT16U usx1Addr, INT16U usy1Addr, 
                         INT16U usColor)
{
   u16 y0,y1; 
   y0 = 239-usx1Addr;
   y1 = 239-usx0Addr;
   usx0Addr = usy1Addr;
   usx1Addr = usy0Addr;
   usy0Addr = y0;
   usy1Addr = y1;
   
    if ((usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr  >= ZTM_YADDR_MAX)
    || (usx1Addr  >= ZTM_XADDR_MAX) || (usy1Addr  >= ZTM_YADDR_MAX)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x64);                                                   /* 发送命令                     */
    __SendDByte(usColor);                                               /* 指定颜色                     */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usx1Addr);
    __SendDByte(usy1Addr);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SquareFill
** 函数功能:  填充正方形
** 输入参数:  usx0Addr：     x0坐标
**            usy0Addr：     y0坐标
**            usWidth：      边长
**            usColor：      填充颜色
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_SquareFill (INT16U usx0Addr, INT16U usy0Addr, INT16U usWidth, INT16U usColor)
{
    ZTM_RectangleFill(usx0Addr, usy0Addr, (usx0Addr + usWidth), (usy0Addr + usWidth), usColor);
}

/*
 * 清屏操作
 */
/*********************************************************************************************************
** 函数名称:  ZTM_ClrScreen
** 函数功能:  用指定颜色清屏
** 输入参数:  usColor：      清屏颜色
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_ClrScreen (INT16U usColor)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x52);                                                   /* 发送命令                     */
    __SendDByte(usColor);                                               /* 发送清屏颜色值               */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*
 * 图片图标显示
 */
/*********************************************************************************************************
** 函数名称:  ZTM_FullScreenImageDisp
** 函数功能:  显示一幅全屏图像
** 输入参数:  usPictureID：  Flash中图片编号0~(PICTURE_ID_MAX - 1)
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_FullScreenImageDisp (INT16U usPictureID)
{
/*
	if (usPictureID >= PICTURE_ID_MAX) {
        return (0);
	}
*/	
	ZtmSendBuff[0] = 0xAA;					     /* 帧头                     */                                                   
	ZtmSendBuff[1] = 0x70;
		
	ZtmSendBuff[2] = usPictureID>>8;
	ZtmSendBuff[3] = usPictureID;			
 
	ZtmSendCnt = 3;                     /* 发送帧尾                     */
	ZtmSendBuff[++ZtmSendCnt] = 0xcc;
	ZtmSendBuff[++ZtmSendCnt] = 0x33;
	ZtmSendBuff[++ZtmSendCnt] = 0xc3;
	ZtmSendBuff[++ZtmSendCnt] = 0x3c;

	uartSendBuff(ZtmSendBuff,ZtmSendCnt+1);
			
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_PartImageDisp
** 函数功能:  剪切图像的一部分显示
** 输入参数:  usPictureID：  Flash中图片编号0~(PICTURE_ID_MAX - 1)
**            usx0Addr：     图片左上角X坐标
**            usy0Addr：     图片左上角Y坐标
**            usx1Addr：     图片右下角X坐标
**            usy1Addr：     图片右下角Y坐标
**            usxAddrDisp：  图片显示位置左上角坐标
**            usyAddrDisp：  图片显示位置左上角坐标
**            ucType         0:不过滤颜色
**                           1:过滤颜色,透明效果
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_PartImageDisp (INT16U usPictureID, INT16U usx0Addr, 
                         INT16U usy0Addr, INT16U usx1Addr,
                         INT16U usy1Addr, INT16U usxAddrDisp, 
                         INT16U usyAddrDisp, INT8U ucType)
{
    /*
     * 参数检查
     */
/*	
    if ((usPictureID >= PICTURE_ID_MAX)
    || (usx0Addr >= ZTM_XADDR_MAX) || (usy0Addr >= ZTM_YADDR_MAX)
    || (usx1Addr >= ZTM_XADDR_MAX) || (usy1Addr >= ZTM_YADDR_MAX)
    || (usxAddrDisp >= ZTM_XADDR_MAX) || (usyAddrDisp >= ZTM_YADDR_MAX)
    || (ucType >= 2)) {
        return (0);
    }
*/	
    __SendHead();                                                       /* 发送帧头                     */

    if (0 == ucType) {                                                  /* 发送命令                     */
        __SendByte(0x71);
    } else if (1 == ucType) {
        __SendByte(0x9C);
    }

    __SendDByte(usPictureID);                                           /* 发送图片编号                 */
    __SendDByte(usx0Addr);                                              /* 发送坐标                     */
    __SendDByte(usy0Addr);
    __SendDByte(usx1Addr);
    __SendDByte(usy1Addr);
    __SendDByte(usxAddrDisp);
    __SendDByte(usyAddrDisp);

    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_ImageDisp
** 函数功能:  指定位置显示图片
** 输入参数:  usPictureID:   Flash中图片编号0~(PICTURE_ID_MAX - 1)
**            usxAddrDisp:   图片显示位置左上角X坐标
**            usyAddrDisp：  图片显示位置左上角Y坐标
**            ucType：       0:不过滤颜色
**                           1:过滤颜色,透明效果
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_ImageDisp (INT8U usPictureID,INT16U usxAddrDisp,
                     INT16U usyAddrDisp,INT8U ucType)
{
    /*
     * 参数检查
	
    if ((usPictureID >= PICTURE_ID_MAX)
    || (usxAddrDisp >= ZTM_XADDR_MAX)
    || (usyAddrDisp >= ZTM_YADDR_MAX)
    || (ucType >= 2)) {
        return (0);
    }
     */
    __SendHead();                                                       /* 发送帧头                     */

    if (0 == ucType) {                                                  /* 发送命令                     */
        __SendByte(0x9D);
    } else if (1 == ucType) {
        __SendByte(0x9E);
    }
    __SendDByte(usPictureID);
    __SendDByte(usxAddrDisp);                                           /* 发送坐标                     */
    __SendDByte(usyAddrDisp);
    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*
 * 动画功能
 */
/*********************************************************************************************************
** 函数名称:  ZTM_Cartoon
** 函数功能:  按预设时间进行动画显示
** 输入参数:  *pusPictureID：Flash中图片编号0~(PICTURE_ID_MAX - 1)
**            usNum：        动画显示图片张数
** 输出参数： 无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_Cartoon (INT16U *pusPictureID, INT16U usNum)
{
    /*
     * 参数检查
     */
/*	
    if (usNum >= PICTURE_ID_MAX) {
        return (0);
    }
*/	
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x9A);
    __SendDByteStr(pusPictureID, usNum);
    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetCartoon
** 函数功能:  指定参数进行动画显示
** 输入参数:  ucTime：            取值为 0～255，表示每张图片播放的时间长度，单位为 100毫秒。
**            ucType：            0x00：按原图显示，不进行颜色过滤；
**                                0x01：过滤颜色显示，背景为 usColorPicId 图片；
**                                0x02：过滤颜色显示，背景为填充 usColorPicId 颜色
**                                0x04：过滤颜色显示，直接前景显示；
**            usColorOrPicId：    背景填充颜色（16 位色）或背景图片 ID；
**            usFilterColorLow：  颜色过滤低阈值，当显示类型为 00 时，此参数无效；
**            usFilterColorHight：颜色过滤高阈值，当显示类型为 00 时，此参数无效；
**            usX：               动画显示的起始 X坐标；
**            usY：               动画显示的起始 Y坐标；
**            pusPictureID：      Flash中图片编号0~(PICTURE_ID_MAX - 1)
**            usNum：             动画显示图片张数
** 输出参数： 无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetCartoon (INT8U ucTime, INT8U ucType, INT16U usColorOrPicId,
                      INT16U usFilterColorLow, INT16U usFilterColorHight,
                      INT16U usX, INT16U usY,
                      INT16U *pusPictureID, INT16U usNum)
{
    /*
     * 参数检查
     */
/*	
    if ((ucTime > LIGHT_TIME_MAX) || (ucType > 4)
     || (usX > ZTM_XADDR_MAX) || (usY > ZTM_YADDR_MAX)
     || (usNum > PICTURE_ID_MAX)) {
         return (0);
     }
	*/
	
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x9F);
    __SendByte(ucTime);                                                 /* 发送每张播放的时间长度       */
    __SendByte(ucType);                                                 /* 发送过滤色类型               */
    __SendDByte(usColorOrPicId);                                        /* 发送图片ID                   */
    __SendDByte(usFilterColorLow);                                      /* 颜色过滤低阈值               */
    __SendDByte(usFilterColorHight);                                    /* 颜色过滤高阈值               */
    __SendDByte(usX);                                                   /* 发送动画显示X坐标            */
    __SendDByte(usY);                                                   /* 发送动画显示Y坐标            */
    __SendDByteStr(pusPictureID, usNum);
    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*
 * 触摸屏操作
 */
 
/*********************************************************************************************************
** 函数名称:  ZTM_TouchCalibration
** 函数功能:  触摸屏校准(注意只有第一次使用触摸屏时需要校准)
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_TouchCalibration (void)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByteStr(__GucFrameTouchCal, 5);                               /* 发送命令                     */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*********************************************************************************************************
** 函数名称:  ZTM_CheckTouchPos
** 函数功能:  主动查询触摸笔当前位置
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
** 说    明； 2012-02-22
*********************************************************************************************************/
void ZTM_CheckTouchPos (void)
{

    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x73);                                                   /* 发送命令码                   */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*
 * 蜂鸣器操作
 */
/*********************************************************************************************************
** 函数名称:  ZTM_SetBuzzer
** 函数功能:  蜂鸣器操作
** 输入参数:  ucTime ：蜂鸣器鸣响的时间长度，单位是10ms，值为0~255，
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_SetBuzzer (INT8U ucTime)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x79);                                                   /* 发送指令码                   */
    __SendByte(ucTime);                                                 /* 发送时间值                   */
	
    __SendTail();                                                       /* 发送帧尾                     */
}

/*
 * 背光控制
 */
/*********************************************************************************************************
** 函数名称:  ZTM_LightOnOff
** 函数功能:  背光控制
** 输入参数:  ucOnOff：      0:  关背光
**                           1:  开背光
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_LightOnOff (INT8U ucOnOff)
{
    if (ucOnOff > 1) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */
    if (0 == ucOnOff)     {
        __SendByte(0x5E);                                               /* 发送背光开命令               */
    } else if (1 == ucOnOff) {
        __SendByte(0x5F);                                               /* 发送背光关命令               */
    }
    __SendTail();                                                       /* 发送帧尾                     */
    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_LightTimeTouch
** 函数功能:  背光设置
** 输入参数:  ucPWMOn ：背光有效时的亮度
**            ucPWMOff：背光无效时的亮度
**            ucOnTime: 背光有效时间，单位为秒
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_LightTimeTouch (INT8U ucPWMOn, INT8U ucPWMOff, INT8U ucOnTime)
{
	/*
     *  参数检查
     */
    if ((ucPWMOn > LIGHT_PWMLEVEL_MAX) || 
	    (ucPWMOff > LIGHT_PWMLEVEL_MAX)) {
        return (0);
    }
	
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x5E);                                                   /* 发送命令                     */
    __SendByteStr(__GucFrameLight, 4);                                  /* 发送键控背光命令             */
	__SendByte(ucPWMOn);                                                /* 发送背光有效时的亮度         */
	__SendByte(ucPWMOff);                                               /* 发送背光无效时的亮度         */
    __SendByte(ucOnTime);                                               /* 发送背光有效时间             */
	
    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_LightLevel
** 函数功能:  背光亮度等级
** 输入参数:  ucPWMLevel：   0-100
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_LightLevel (INT8U ucPWMLevel)
{
    if (ucPWMLevel >= LIGHT_PWMLEVEL_MAX) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0x5F);
    __SendByte(ucPWMLevel);
    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*
 * 参数配置
 */
/*********************************************************************************************************
** 函数名称:  ZTM_SetPara
** 函数功能:  参数配置
** 输入参数:  ulBaud：             串口波特率：             1200-3152000bps
**            ucTouchType：        触摸屏数据上传格式:      0x72或0x73
**            ucBackLightType：    背光控制模式:            0x5E或0x5F
**            ucTxtBackgroundType：文本背景显示模式         0:文本背景色为系统背景色(默认)
**                                                          1:文本背景色为透明
**            INT8U ucMouseType：  点击触摸屏时鼠标显示模式 0:不显示鼠标(默认)
**                                                          :显示鼠标
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetPara (INT32U ulBaud, INT8U ucTouchType, INT8U ucBackLightType,
                   INT8U ucTxtBackgroundType, INT8U ucMouseType)
{
    if (((ulBaud < 1200) && (ulBaud > 3152000))
    || (ucTxtBackgroundType > 1)
    || (ucMouseType > 1)) {
        return (0);
    }
    __SendHead();                                                       /* 发送帧头                     */


    __SendByte(0xE0);
                                                                        /* 1.发送波特率值               */
    __SendByte((ulBaud >> 24) & 0xFF);
    __SendByte((ulBaud >> 16) & 0xFF);
    __SendByte((ulBaud >> 8) & 0xFF);
    __SendByte(ulBaud & 0xFF);
                                                                        /* 2.发送触摸屏数据上传格式     */
    __SendByte(ucTouchType);
                                                                        /* 3.发送背光控制模式           */
    __SendByte(ucBackLightType);
                                                                        /* 4.发送文本背景显示模式       */
    __SendByte(ucTxtBackgroundType);
                                                                        /* 5.发送鼠标显示模式           */
    __SendByte(ucMouseType);

    __SendTail();                                                       /* 发送帧尾                     */

    return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetBaudrate
** 函数功能:  设置通信波特率
** 输入参数:  ulBaud：串口波特率，1200-3152000bps
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetBaudrate (INT32U ulBaud)
{
	/*
     *  参数检查
     */
	if ((ulBaud < 1200) || (ulBaud > 3152000)) {
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE000);                                                /* 发送指令码                   */                                                                   
    __SendByte((ulBaud >> 24) & 0xFF);                                  /* 发送波特率值                 */
    __SendByte((ulBaud >> 16) & 0xFF);
    __SendByte((ulBaud >> 8) & 0xFF);
    __SendByte(ulBaud & 0xFF);

    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetDisplayBuf
** 函数功能:  设置显示缓存属性
** 输入参数:  ucDisplayBuf：目标显示缓存属性值
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_SetDisplayBuf (INT8U ucDisplayBuf)
{
	/*
     *  参数处理
     */
	ucDisplayBuf &= 0xF0;                                               /* 截断作为保留位的低4位        */
	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE001);                                                /* 发送指令码                   */                                                                   
    __SendByte(ucDisplayBuf);                                           /* 发送目标显示缓存属性值       */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetAck
** 函数功能:  设置串口屏应答功能
** 输入参数:  ucAckEn：应答功能设置值，0——禁能命令应答；1——使能命令应答
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetAck (INT8U ucAckEn)
{
    /*
     *  参数检查
     */
	if (ucAckEn > 1) {
	
		return (0);
    }
	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE002);                                                /* 发送指令码                   */                                                                   
    __SendByte(ucAckEn);                                                /* 发送应答功能设置值           */

    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetTouchType
** 函数功能:  设置触摸屏响应类型
** 输入参数:  ucTouchType：触摸屏响应类型值，0x72——非触控模式下，触摸笔抬起时，上传坐标数据
**                                           0x73——非触控模式下，触摸笔按下时，上传坐标数据
**                                           0x74——非触控模式下，触摸笔移动时，上传坐标数据
**                                           0x78——触控模式下，触摸笔抬起时，上传预设触控键码
**                                           0x79——触控模式下，触摸笔按下时，上传预设触控键码
**                                           0x7A——触控模式下，触摸笔按下和抬起时，上传预设触控键码
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetTouchType(INT8U ucTouchType)
{
	/*
     *  参数检查
     */
	if (!((ucTouchType == 0x72) ||
		  (ucTouchType == 0x73) ||
		  (ucTouchType == 0x74) ||
		  (ucTouchType == 0x78) ||
		  (ucTouchType == 0x79) ||
		  (ucTouchType == 0x7A))  ) {
	
		return (0);
    }
	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE003);                                                /* 发送指令码                   */                                                                   
    __SendByte(ucTouchType);                                            /* 发送触摸屏响应类型值         */

    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetBuzzerType
** 函数功能:  设置蜂鸣器配置
** 输入参数:  ucBuzzerType：蜂鸣器配置值
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetBuzzerType (INT8U ucBuzzerType)
{
	/*
     *  参数检查
     */
	if (ucBuzzerType > 1) {
	
		return (0);
    }
	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE004);                                                /* 发送指令码                   */                                                                   
    __SendByte(ucBuzzerType);                                           /* 发送蜂鸣器配置值             */

    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetTxtBackgroundType
** 函数功能:  设置文本控件显示背景类型
** 输入参数:  ucTxtBackgroundType：文本显示背景类型值，0——文本的背景色为系统的背景色（默认）
**                                                     1——文本的背景色为透明
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetTxtBackgroundType(INT8U ucTxtBackgroundType)
{
	/*
     *  参数检查
     */
	if (ucTxtBackgroundType > 1) {
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */
	
	__SendDByte(0xE005);                                                /* 发送指令码                   */
	__SendByte(ucTxtBackgroundType);                                    /* 发送文本显示背景类型值       */
	
	__SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetSysMouseType
** 函数功能:  设置点击触摸屏时系统鼠标是否显示
** 输入参数:  ucSysMouseType：指示点击触摸屏时系统图标是否显示，0——不显示（默认）
**                                                              1——显示
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetSysMouseType(INT8U ucSysMouseType)
{
	/*
     *  参数检查
     */
	if (ucSysMouseType > 1) {
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */
	
	__SendDByte(0xE006);                                                /* 发送指令码                   */
	__SendByte(ucSysMouseType);                                         /* 发送文本显示背景类型值       */
	
	__SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetSumCheckType
** 函数功能:  设置通信和校验类型
** 输入参数:  ucSumCheckype：通信和校验类型值，0——无校验（默认）
**                                             1——8位和校验
**                                             2——16位和校验
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetSumCheckType (INT8U ucSumCheckType)
{
	/*
     *  参数检查
     */
	if (ucSumCheckType > 2) {
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */
	
	__SendDByte(0xE007);                                                /* 发送指令码                   */
	__SendByte(ucSumCheckType);                                         /* 发送通信和校验类型值         */
	
	__SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*********************************************************************************************************
** 函数名称:  ZTM_SetTouchDelay
** 函数功能:  设置触摸屏动作响应时间
** 输入参数:  ulTouchDly：触摸屏动作响应时间
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_SetTouchDelay (INT32U ulTouchDly)
{
	/*
     *  参数检查
     */

	
	__SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE010);                                                /* 发送指令码                   */                                                                   
    __SendByte((ulTouchDly >> 24) & 0xFF);                              /* 发送触摸屏动作响应时间       */
    __SendByte((ulTouchDly >> 16) & 0xFF);
    __SendByte((ulTouchDly >> 8) & 0xFF);
    __SendByte(ulTouchDly & 0xFF);

    __SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*
 * 器件信息
 */
/*********************************************************************************************************
** 函数名称:  ZTM_ReadDeviceInfo
** 函数功能:  发送读取串口屏器件信息
** 输入参数:  无
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_ReadDeviceInfo (void)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendByte(0xA0);                                                   /* 发送命令                     */

    __SendTail();                                                       /* 发送帧尾                     */
}

/*
 *  直接显存操作
 */
/*********************************************************************************************************
** 函数名称:  ZTM_OptDisBufDirectly
** 函数功能:  直接显存操作
** 输入参数:  usX0         ：操作区域起始点X坐标；
**            usY0         ：操作区域起始点Y坐标；
**            usX1         ：操作区域结束点X坐标；
**            usY1         ：操作区域结束点Y坐标；
**            usXRef       ：操作区域内参考点X坐标；
**            usYRef       ：操作区域内参考点Y坐标；
**            ulNBytes     ：填充颜色值字节数；
**            pucColorValue：填充的颜色值数据
** 输出参数:  无
** 返 回 值:  成功返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_OptDisBufDirectly (INT16U usX0, 
							 INT16U usY0,
							 INT16U usX1,
							 INT16U usY1,
							 INT16U usXRef,
							 INT16U usYRef,
							 INT32U ulNBytes,
							 INT8U *pucColorValue) {

	INT32U ulColorBytesIdx;
	
	/*
     *  参数检查
     */
	if ((usX0   >= ZTM_XADDR_MAX) ||
	    (usX1   >= ZTM_XADDR_MAX) ||
		(usXRef >= ZTM_XADDR_MAX) ||
		(usY0   >= ZTM_YADDR_MAX) ||
	    (usY1   >= ZTM_YADDR_MAX) ||
		(usYRef >= ZTM_YADDR_MAX)   ) {
		
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */
	
	__SendByte(0xC3);                                                   /* 发送指令码                   */
	__SendDByte(usX0);                                                  /* 发送操作区域起始点X坐标      */
	__SendDByte(usY0);                                                  /* 发送操作区域起始点Y坐标      */
	__SendDByte(usX1);                                                  /* 发送操作区域结束点X坐标      */
    __SendDByte(usY1);                                                  /* 发送操作区域结束点X坐标      */
	__SendDByte(usXRef);                                                /* 发送操作区域内参考点X坐标    */
	__SendDByte(usYRef);                                                /* 发送操作区域内参考点Y坐标    */
	__SendByte((ulNBytes >> 24) & 0xFF);                                /* 发送填充颜色值字节数         */
    __SendByte((ulNBytes >> 16) & 0xFF);
    __SendByte((ulNBytes >> 8) & 0xFF);
    __SendByte(ulNBytes & 0xFF);
	
	/*
     *  发送填充区域的颜色值数据
     */
	for (ulColorBytesIdx = 0; ulColorBytesIdx < ulNBytes; ulColorBytesIdx++) {
		__SendByte(pucColorValue[ulColorBytesIdx]);
	}
	
	__SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}

/*
 *  字库或配置文件下载
 */
/*********************************************************************************************************
** 函数名称:  ZTM_FileDownload
** 函数功能:  字库或配置文件下载
** 输入参数:  ucType     ：下载文件类型值；
**            ulSize     ：下载文件长度；
**            pucOption  ：可选参数列表指针；
**            ucOptNBytes：可选参数列表长度。
** 输出参数:  无
** 返 回 值:  正确返回1，否则返回0
*********************************************************************************************************/
INT8U ZTM_FileDownload (INT8U ucType, INT32U ulSize, INT8U *pucOption, INT8U ucOptNBytes)
{
	INT8U ucOptByteIdx;
	
	/*
     *  参数检查
     */
	if (ucOptNBytes > 24) {
		return (0);
	}
	
	__SendHead();                                                       /* 发送帧头                     */
	
	__SendByte(0xF2);                                                   /* 发送指令码                   */
	__SendByteStr(__GucFrameFileDownload, 4);                           /* 发送其他命令码               */
	__SendByte(ucType);                                                 /* 发送下载文件类型值           */
	__SendByte((ulSize >> 24) & 0xFF);                                  /* 发送文件长度值               */
    __SendByte((ulSize >> 16) & 0xFF);
    __SendByte((ulSize >> 8) & 0xFF);
    __SendByte(ulSize & 0xFF);
	
	/*
     *  发送可选参数
     */
	for (ucOptByteIdx = 0; ucOptByteIdx < ucOptNBytes; ucOptByteIdx++) {
		__SendByte(pucOption[ucOptByteIdx]);
	}
	
	__SendTail();                                                       /* 发送帧尾                     */
	
	return (1);
}
/*********************************************************************************************************
** 函数名称:  ZTM_DisBufSwitch
** 函数功能:  显示缓存操作指令
** 输入参数:  ucCmd：操作命令，组合值
** 输出参数:  无
** 返 回 值:  无
*********************************************************************************************************/
void ZTM_DisBufSwitch (INT8U ucCmd)
{
    __SendHead();                                                       /* 发送帧头                     */

    __SendDByte(0xE001);                                                /* 发送命令                     */
    
    __SendByte(ucCmd);                                                  /* 发送参数                     */

    __SendTail();                                                       /* 发送帧尾                     */
}
/*******************************************************************************
功能：图层显示
参数：
*******************************************************************************/
void Framebuffer_display(u16 x1, u16 y1, u16 x2, u16 y2, u8 size, u16 usFcolor ,u16 usBcolor, const u8 *buf1, const u8 *buf2, u16 tms)
{    
    ZTM_DisBufSwitch(0x00);                                             /* 取消自动缓存管理             */
    ZTM_DisBufSwitch(0x20);                                             /* 写指针指向备用缓存           */
    
    TXM_StringDisplay(0,x1,y1,size,1,usFcolor ,usBcolor,(void*)buf1);
    TXM_StringDisplay(0,x2,y2,size,1,usFcolor ,usBcolor,(void*)buf2);
    
    ZTM_DisBufSwitch(0x40);                                             /* 将显示缓存设置为备用缓存     */
    ZTM_Delay(tms);
    
    ZTM_DisBufSwitch(0x20);                                             /* 写指针指向主缓存             */
    ZTM_DisBufSwitch(0x40);                                             /* 将显示缓存设置为主缓存       */
    ZTM_DisBufSwitch(0x10);                                             /* 使能自动缓存管理             */   
}
/*********************************************************************************************************
end of file
*********************************************************************************************************/
