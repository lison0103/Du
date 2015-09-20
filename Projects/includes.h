/*
*********************************************************************************************************
*
*
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   IAR STM32 
*
* Filename      : includes.h
* Version       : v1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include "stm32f10x.h" 

#include "bsp_usart.h" 

#include "ucos_ii.h" //uC/OS-II系统函数头文件 

#include "ZTM.h"

#include "BSP.h" //与开发板相关的函数
#include "app.h" //用户任务函数 
//#include "led.h" //LED驱动函数 

#include "key.h"

#include "crc16.h"

#include "display.h"
#include "lcd_text.h"

#include "spi_flash.h"

#include "diskio.h"		/* FatFs lower layer API */

#include "spi.h"
#include "string.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define ECT_A_VERSION   ModBuff[5450] 




#define LANGUAGE              DuSysBuff[5] 

#define RECORD_ESC_NUMBER     DuSysBuff[10]

//@使用有效期需要保存的数据

#define FIRST_FLAG               DuSysBuff[15]  

#define VALIDITY_FLAG            DuSysBuff[20]

#define VALIDITY_USE_DATE        DuSysBuff[25]

#define VALIDITY_LAST_DATE       DuSysBuff[30]

//@end

typedef struct errordescripitem
{
	u16 ucID; 
	
	char  *UpperString[2];
	char  *LowerString[2];
	
} ErrorDescripItem;

typedef struct 
{
  
  u8 esc_sn[16];
  
} Struct_EscInfo;


extern u8 ModBuff[5800],buff_temp[4096];
extern u16 *pt_ModBuff;
extern u8 main_loop;

extern u16 DisplayPictureNumber,DisplayPictureNumberPre;

void AppTask_Main(void *p_arg);
void AppTask_COM(void *p_arg);
void AppTask_KEY(void *p_arg);
void Task_Menu(void *p_arg);

void Task_Display(void *p_arg);

void spi_flash_q64_init(void);

u8 modbus_read(USART_TypeDef* USARTx, u16 start_addr, u16 len);
u8 modbus_write(USART_TypeDef* USARTx, u16 start_addr, u16 len);

void lcd_dis_record_error(u8 errcode);

void menu_process(void);

void menu_statistic(void);
void menu_para_base(void);
void menu_para_io(u8 item);

void menu_para_restore(void);
void menu_para_backup(void);

void menu_sn_cfg(void);
void menu_error_cfg(void);

void main_display(void);
void time_display(u16 dw,u16 tw,u8 *tb);
void time_display_oneline(u16 dw,u16 x,u16 y, u8 *tb, u8 flash_bit);

void get_error_descrip(u8 errcode, char *pstr);

void display_error_descrip(u16 wid_num,u8 errcode);

u16 esc_bk_pos_check(u8 *sn);
void esc_bk_init(void);

void Task_Help(void);

u8 get_esc_bk_item_index(u16 num,u8 *buff);

void menu_comm_cfg(void);

void menu_language_cfg(void);

void du_sys_data_write(void);

void esc_sn_display(u16 x,u16 y,u8 *buff,u8 set_bit);
u16 esc_bk_pos_write(u8 *sn,u16 num);

void menu_time_set(void);

extern const ErrorDescripItem ErrorCodeDescripItem[];

extern OS_EVENT *Mutex_Modbus;

extern u8 DuSys_Data[100];
extern u16 *DuSysBuff;

extern u8 TimeBuff[6];

//// @add by lisonchen  
void menu_password_cfg(void);

extern u8 USER_RIGHT_LEVEL;

void validity_cfg(void);

u8 * Get_Current_Date(u8 *tb);

extern u8 USER_RIGHT_VALIDITY;

extern u8 validity_date,already_usedate;
extern u8 last_set_date[6],current_set_date[6];

#if 0
//第一次写入标志
#define V_FLAG_ADDR ((2*1024 + 512)*1024)
//已获得有效期使用标志
#define V_VLDT_ADDR (((2*1024 + 512)*1024) + 1)
//还剩余有效期天数
#define V_AUDE_ADDR (((2*1024 + 512)*1024) + 2)
//上次激活或更改记录的日期
#define V_LSDE_ADDR (((2*1024 + 512)*1024) + 3)

#endif

 u32 Calculate(u8 begin[],u8 end[]);

void SPI_W25X_ChipErase(void);
//// @end

#endif //__INCLUDES_H__

