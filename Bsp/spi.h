
#ifndef __SPI_H
#define __SPI_H

void SPI_HV_Init(SPI_TypeDef* SPIx);
u8 SPI_ReadWriteByte(SPI_TypeDef* SPIx,u8 TxData);

#endif // __SPI_H
