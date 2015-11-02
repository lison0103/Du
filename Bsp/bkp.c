#include "bkp.h"

void BKP_Init(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);

}

void BKP_Write(u16 addr, u16 data)
{
    PWR_BackupAccessCmd(ENABLE);
    BKP_WriteBackupRegister(addr, data);
    PWR_BackupAccessCmd(DISABLE);
}

u16 BKP_Read(u16 addr)
{

    return BKP_ReadBackupRegister(addr);
  
}