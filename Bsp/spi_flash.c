/* Includes ------------------------------------------------------------------*/
#include "spi_flash.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  FLASH_WriteAddress     0x700000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
#define  M25P64_FLASH_ID        0x00EF4017
#define  BufferSize             (countof(Tx_Buffer)-1)


u16 SPI_FLASH_TYPE = W25Q64;//Ĭ�Ͼ���25Q64

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private variables ---------------------------------------------------------*/
//uint8_t Tx_Buffer[] = "STM32F10x SPI Firmware Library Example: communication with an M25P64 SPI FLASH";
//uint8_t Index, Rx_Buffer[BufferSize];

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FLASH_ID = 0;

/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

u8 aaa[4096];
//u8 buff[10000];
//u16 *ptbuff = (u16*)buff;



/**
  * @brief  Compares two buffers.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  * @param BufferLength: buffer's length
  * @retval : PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
     
  return PASSED;
}

/*******************************************************************************
*******************************************************************************/
uint8_t SPI_W25X_ReadByte(void)
{
  return(SPI_ReadWriteByte(SPI_W25Q, Dummy_Byte));
}

uint8_t SPI_W25X_SendByte(uint8_t byte)
{
  return(SPI_ReadWriteByte(SPI_W25Q, byte));
}

void SPI_W25X_Wait_Busy(void)
{
  uint8_t FLASH_Status = 0;
  
  SPI_W25X_CS_LOW();
  
  SPI_W25X_SendByte(W25X_RDSR1);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_W25X_SendByte(Dummy_Byte);
  }
  while( (FLASH_Status & WIP_Flag) == SET ); /* Write in progress */

  SPI_W25X_CS_HIGH(); 
}
 
//��ȡSPI_FLASH��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8 SPI_W25X_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_W25X_CS=0;                            //ʹ������   
	SPI_W25X_SendByte(W25X_RDSR1);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI1_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	SPI_W25X_CS=1;                            //ȡ��Ƭѡ     
	return byte;   
} 

//дSPI_FLASH״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void SPI_W25X_Write_SR(u8 sr)                   
{   
	SPI_W25X_CS=0;                             //ʹ������   
	SPI_W25X_SendByte(W25X_RDSR1);    //����дȡ״̬�Ĵ�������    
	SPI_W25X_SendByte(sr);                     //д��һ���ֽ�  
	SPI_W25X_CS=1;                             //ȡ��Ƭѡ     	      
}   

//SPI_FLASHд��ֹ 	
//��WEL����  
void SPI_W25X_Write_Disable(void)   
{  
  SPI_W25X_CS=0;    
  
  SPI_ReadWriteByte(SPI1,W25X_WR_DISABLE);    
  
	SPI_W25X_CS=1;                               	      
} 		

/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval : None
  */
void SPI_W25X_Write_Enable(void)
{
  //SPI_FLASH_CS=0;    
  SPI_W25X_CS_LOW();
  
  SPI_ReadWriteByte(SPI1,W25X_WR_ENABLE);
  
  //SPI_FLASH_CS=1;  
  SPI_W25X_CS_HIGH();
}

/*******************************************************************************
*******************************************************************************/
void SPI_W25X_SectorErase(uint32_t SectorAddr)
{
  Flash_W25X_Read(aaa,SectorAddr*4096,4096);

  SPI_W25X_Write_Enable();

  SPI_W25X_CS_LOW();
  SPI_W25X_SendByte(W25X_SE);
  SectorAddr = SectorAddr*4096; 
  SPI_W25X_SendByte((SectorAddr & 0xFF0000) >> 16); 
  SPI_W25X_SendByte((SectorAddr & 0xFF00) >> 8);
  SPI_W25X_SendByte(SectorAddr & 0xFF);
  SPI_W25X_CS_HIGH();

  SPI_W25X_Wait_Busy();
  
  Flash_W25X_Read(aaa,SectorAddr,4096);
}

void SPI_W25X_BlockErase_32K(uint32_t SectorAddr)
{
  SPI_W25X_Write_Enable();

  SPI_W25X_CS_LOW();
  SPI_W25X_SendByte(W25X_BE_32KB);
  SPI_W25X_SendByte((SectorAddr & 0xFF0000) >> 16); 
  SPI_W25X_SendByte((SectorAddr & 0xFF00) >> 8);
  SPI_W25X_SendByte(SectorAddr & 0xFF);
  SPI_W25X_CS_HIGH();

  SPI_W25X_Wait_Busy();
}

void SPI_W25X_BlockErase_64K(uint32_t SectorAddr)
{
  SPI_W25X_Write_Enable();

  SPI_W25X_CS_LOW();
  SPI_W25X_SendByte(W25X_BE_64KB);
  SPI_W25X_SendByte((SectorAddr & 0xFF0000) >> 16); 
  SPI_W25X_SendByte((SectorAddr & 0xFF00) >> 8);
  SPI_W25X_SendByte(SectorAddr & 0xFF);
  SPI_W25X_CS_HIGH();

  SPI_W25X_Wait_Busy();
}

void SPI_W25X_ChipErase(void)
{
  SPI_W25X_Write_Enable();

  SPI_W25X_CS_LOW();
  SPI_W25X_SendByte(W25X_CE);
  SPI_W25X_CS_HIGH();

  SPI_W25X_Wait_Busy();
}

/*******************************************************************************
*******************************************************************************/
//�������ģʽ
void SPI_W25X_PowerDown(void)   
{ 
  SPI_W25X_CS=0;                             //ʹ������   
  SPI1_ReadWriteByte(W25X_PowerDown);         //���͵�������  
	SPI_W25X_CS=1;                             //ȡ��Ƭѡ     	      
}   

//����
void SPI_W25X_WakeUp(void)   
{  
  SPI_W25X_CS=0;                                //ʹ������   
  SPI1_ReadWriteByte(W25X_ReleasePowerDown);    //  send W25X_PowerDown command 0xAB    
	SPI_W25X_CS=1;                                //ȡ��Ƭѡ     	      
}   

/*******************************************************************************
*******************************************************************************/
uint32_t SPI_W25X_ReadJID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_W25X_CS_LOW();

  /* Send "RDID " instruction */
  SPI_ReadWriteByte(SPI_W25Q,0x9F);

  /* Read a byte from the FLASH */
  Temp0 = SPI_ReadWriteByte(SPI_W25Q,Dummy_Byte);
  Temp1 = SPI_ReadWriteByte(SPI_W25Q,Dummy_Byte);
  Temp2 = SPI_ReadWriteByte(SPI_W25Q,Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_W25X_CS_HIGH();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
} 

//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64   	  
u16 SPI_W25X_ReadID(void)
{
	u16 Temp = 0;	  
  
	SPI_W25X_CS=0;				    
	SPI_ReadWriteByte(SPI_W25Q,0x90);    
	SPI_ReadWriteByte(SPI_W25Q,0x00); 	    
	SPI_ReadWriteByte(SPI_W25Q,0x00); 	    
	SPI_ReadWriteByte(SPI_W25Q,0x00); 	 			   
	Temp |= SPI_ReadWriteByte(SPI_W25Q,0)<<8;  
	Temp |= SPI_ReadWriteByte(SPI_W25Q,0);	 
	SPI_W25X_CS=1;			
  
	return Temp;  
}   	

/*******************************************************************************
*******************************************************************************/
void Flash_W25X_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;   										  
  
  //ʹ������   
	SPI_W25X_CS=0;  

  SPI_W25X_SendByte(W25X_ReadData);         //���Ͷ�ȡ����   
  SPI_W25X_SendByte((u8)((ReadAddr)>>16));  //����24bit��ַ    
  SPI_W25X_SendByte((u8)((ReadAddr)>>8));   
  SPI_W25X_SendByte((u8)ReadAddr);   
  for(i=0;i<NumByteToRead;i++)
	{ 
    pBuffer[i] = SPI_ReadWriteByte(SPI_W25Q, 0XFF);  //ѭ������  
  }
  
  SPI_W25X_CS=1;  				    	      
}  

/*******************************************************************************
*******************************************************************************/
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void SPI_W25Q_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
  SPI_W25X_Write_Enable();                      //SET WEL 
  
	SPI_W25X_CS=0;                                //ʹ������   
  SPI_W25X_SendByte(W25X_PageProgram);         //����дҳ����   
  
  SPI_W25X_SendByte((u8)((WriteAddr)>>16));    //����24bit��ַ    
  SPI_W25X_SendByte((u8)((WriteAddr)>>8));   
  SPI_W25X_SendByte((u8)WriteAddr);   
  for(i=0;i<NumByteToWrite;i++) SPI_W25X_SendByte(pBuffer[i]);  //ѭ��д�� 
  
	SPI_W25X_CS=1;                            //ȡ��Ƭѡ 
	SPI_W25X_Wait_Busy();					          //�ȴ�д�����
} 

//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void SPI_W25Q_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		SPI_W25Q_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	
  
  SPI_W25X_Wait_Busy();					          //�ȴ�д�����
} 

//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
u8 SPI_FLASH_BUFFER[4096];		 

void Flash_W25X_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * SPI_FLASH_BUF;	  
  
  SPI_FLASH_BUF=SPI_FLASH_BUFFER; 	     
 	secpos=WriteAddr/4096;//������ַ   
	secoff=WriteAddr%4096;//�������ڵ�ƫ�� 
	secremain=4096-secoff;//����ʣ��ռ��С    
  
 	if(NumByteToWrite<=secremain) secremain=NumByteToWrite; //������4096���ֽ�
  
	while(1) 
	{	
		Flash_W25X_Read(SPI_FLASH_BUF,secpos*4096,4096); //������������������
    
		for(i=0;i<secremain;i++)//У������ 
		{
			if(SPI_FLASH_BUF[secoff+i] != 0XFF) break;  //��Ҫ����  	  
		}
    
		if(i<secremain) //��Ҫ����
		{
			SPI_W25X_SectorErase(secpos);         //�����������
      
			for(i=0;i<secremain;i++)	            //����
			{
				SPI_FLASH_BUF[i+secoff] = pBuffer[i];	  
			}
      
			SPI_W25Q_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//д����������  
          
		}
    else 
    {  
      SPI_W25Q_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
    }
    
    Flash_W25X_Read(aaa,1000,100);
    
    if(NumByteToWrite==secremain)
    {
      break;  //д�������
    }
    else  //д��δ����
    {
      secpos++;//������ַ��1
      secoff=0;//ƫ��λ��Ϊ0 	 
      
      pBuffer+=secremain;  //ָ��ƫ��
      WriteAddr+=secremain;//д��ַƫ��	   
      NumByteToWrite-=secremain;				//�ֽ����ݼ�
      if(NumByteToWrite>4096)
      {
        secremain=4096;	//��һ����������д����
      }
      else
      {
        secremain=NumByteToWrite;			//��һ����������д����
      }
    }   
  };
}

/*******************************************************************************
*******************************************************************************/
void Flash_W25X_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  __IO uint32_t FLASH_ID = 0;
  
  SPI_FLASH_TYPE = 0;

    /* Enable SPI1 and GPIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CS, ENABLE);

  /* Configure I/O for Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_CS, &GPIO_InitStructure);
  /* Deselect the FLASH: Chip Select high */
  SPI_W25X_CS_HIGH();
  
  SPI_HV_Init(SPI1);
  
  FLASH_ID = SPI_W25X_ReadJID();     //��ȡFLASH ID.
  
  /* Get SPI Flash ID */
  SPI_FLASH_TYPE = SPI_W25X_ReadID();
 
  /* Check the SPI Flash ID */
  if (FLASH_ID == M25P64_FLASH_ID)
  {
    /* OK: Set GPIO_LED pin 6 */
//    GPIO_WriteBit(GPIO_LED, GPIO_Pin_6, Bit_SET);
  }
  else
  {
    /* Error: Set GPIO_LED pin 7 */
//    GPIO_WriteBit(GPIO_LED, GPIO_Pin_7, Bit_SET);
  }
  
  
/*
  Flash_W25X_Read(buff,0,1000);

  for(FLASH_ID=0;FLASH_ID<2500;FLASH_ID++)
  {
    ptbuff[FLASH_ID] = FLASH_ID;
  }
  Flash_W25X_Write(buff,0,4000);

  for(FLASH_ID=0;FLASH_ID<2500;FLASH_ID++)
  {
    ptbuff[FLASH_ID] = 0;
  }
  Flash_W25X_Read(buff,0,4000);
*/  
}

/*******************************************************************************
*******************************************************************************/

















/*******************************************************************************
*******************************************************************************/
#ifdef jbvkssfvlsdf

  /* Perform a write in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Write Tx_Buffer data to SPI FLASH memory */
  SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);

  /* Read data from SPI FLASH memory */
  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

  /* Check the corectness of written dada */
  TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
  /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
     are the same */
  /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
     are different */

  /* Perform an erase in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Read data from SPI FLASH memory */
  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

  /* Check the corectness of erasing operation dada */
  for (Index = 0; Index < BufferSize; Index++)
  {
    if (Rx_Buffer[Index] != 0xFF )
    {
      TransferStatus2 = FAILED;
    }
  }  

/*******************************************************************************
*******************************************************************************/
/**
  * @brief  Writes block of data to the FLASH. In this function, the
  *         number of WRITE cycles are reduced, using Page WRITE sequence.
  * @param pBuffer : pointer to the buffer  containing the data to be
  *                  written to the FLASH.
  * @param WriteAddr : FLASH's internal address to write to.
  * @param NumByteToWrite : number of bytes to write to the FLASH.
  * @retval : None
  */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize; //256
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}


#endif
