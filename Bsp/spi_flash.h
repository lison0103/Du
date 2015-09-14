/**
  ******************************************************************************
  * @file SPI/M25P64_FLASH/spi_flash.h 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Header for spi_flash.c file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "includes.h"

#define GPIO_CS                  GPIOA
#define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOA
#define GPIO_Pin_CS              GPIO_Pin_4 

/* Exported macro ------------------------------------------------------------*/
/* Select SPI FLASH: Chip Select pin low  */
#define SPI_W25X_CS_LOW()       GPIO_ResetBits(GPIO_CS, GPIO_Pin_CS)
/* Deselect SPI FLASH: Chip Select pin high */
#define SPI_W25X_CS_HIGH()      GPIO_SetBits(GPIO_CS, GPIO_Pin_CS)

//ZDYZ
#define	SPI_W25X_CS          PAout(4)     //选中FLASH	

////////////////////////////////////////////////////////////////////////////
 
//指令表
#define W25X_WR_ENABLE		      0x06 
#define W25X_WR_DISABLE		      0x04 
#define W25X_RDSR1		          0x05
#define W25X_RDSR2		          0x35
#define W25X_WriteStatusReg		  0x01 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		    0x0B 
#define W25X_FastReadDual		    0x3B 
#define W25X_PageProgram		    0x02 
#define W25X_BlockErase			    0xD8 
#define W25X_SE     	          0x20 
#define W25X_BE_32KB		        0x20 
#define W25X_BE_64KB		        0x20 
#define W25X_CE      			      0xC7 
#define W25X_PowerDown			    0xB9 
#define W25X_ReleasePowerDown	  0xAB 
#define W25X_DeviceID			      0xAB 
#define W25X_ManufactDeviceID	  0x90 
#define W25X_JedecDeviceID		  0x9F 

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16


/* Private typedef -----------------------------------------------------------*/
#define SPI_FLASH_PageSize    0x100

/* Private define ------------------------------------------------------------*/
#define WRITE       0x02  /* Write to Memory instruction */
#define WRSR        0x01  /* Write Status Register instruction */
#define WREN        0x06  /* Write enable instruction */

#define READ        0x03  /* Read from Memory instruction */
#define RDSR1        0x05  /* Read Status Register instruction  */
#define RDID        0x9F  /* Read identification */
//#define SE          0xD8  /* Sector Erase instruction */
#define BE          0xC7  /* Bulk Erase instruction */

#define WIP_Flag    0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte  0xA5




#define SPI_W25Q    SPI1


extern u16 SPI_FLASH_TYPE;		//定义我们使用的flash芯片型号	

/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint16_t SPI_FLASH_ReadID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);

/*----- Low layer function -----*/
uint8_t SPI_W25X_ReadByte(void);
uint8_t SPI_W25X_SendByte(uint8_t byte);
//uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

u8 SPI1_ReadWriteByte(u8 TxData);//SPI2总线读写一个字节


//u16  SPI_Flash_ReadID(void);  	    //读取FLASH ID
//u8	 SPI_Flash_ReadSR(void);        //读取状态寄存器 
void SPI_FLASH_Write_SR(u8 sr);  	//写状态寄存器
void SPI_FLASH_Write_Enable(void);  //写使能 
void SPI_FLASH_Write_Disable(void);	//写保护
void SPI_W25Q_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

//void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
//void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash
void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//扇区擦除
void SPI_W25X_Wait_Busy(void);           //等待空闲
void SPI_Flash_PowerDown(void);           //进入掉电模式
void SPI_Flash_WAKEUP(void);			  //唤醒

void Flash_W25X_Init(void);

void Flash_W25X_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);
void Flash_W25X_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

#endif /* __SPI_FLASH_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
