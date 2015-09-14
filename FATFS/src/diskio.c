/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "includes.h"

//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */

#define SD_CARD	 0  //SD��,���Ϊ0
#define EX_FLASH 1	//�ⲿflash,���Ϊ1

#define FLASH_SECTOR_SIZE 	512			  

#define FLASH_BLOCK_SIZE  	8     //ÿ��BLOCK��8������

u16	 FLASH_SECTOR_COUNT=2048*6;//6M�ֽ�,Ĭ��ΪW25Q64

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
  return(0);
/*  
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case ATA :
		result = ATA_disk_status();

		// translate the reslut code here

		return stat;

	case MMC :
		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
*/  
}

//���ʱ��
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}			 


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
  SPI_FLASH_Init();
	FLASH_SECTOR_COUNT=2048*6;//W25Q64
  return(0);
  /*
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case ATA :
		result = ATA_disk_initialize();

		// translate the reslut code here

		return stat;

	case MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
*/  
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	//DRESULT res;

  for(;count>0;count--)
  {
    SPI_Flash_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
    sector++;
    buff+=FLASH_SECTOR_SIZE;
  }
 
  //������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
  return RES_OK;	  

/*  
	switch (pdrv) {
	case ATA :
		// translate the arguments here

		result = ATA_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
*/  
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
// _USE_WRITE
//#if _READONLY
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
  if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������	
  
  for(;count>0;count--)
  {										    
    SPI_Flash_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
    sector++;
    buff+=FLASH_SECTOR_SIZE;
  }
  
  return RES_OK;	 
  
/*  
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :
		// translate the arguments here

		result = ATA_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
*/  
}
//#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  DRESULT res;
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = FLASH_SECTOR_SIZE;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = FLASH_BLOCK_SIZE;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = FLASH_SECTOR_COUNT;
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
   return res;
/*  
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :

		// Process of the command for the ATA drive

		return res;

	case MMC :

		// Process of the command for the MMC/SD card

		return res;

	case USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
*/  
}
#endif
