#ifndef __IAP_H__
#define __IAP_H__
#include "includes.h"
	

typedef  void (*iapfun)(void);		//����һ���������͵Ĳ���.   
#define FLASH_LOADER_ADDR		0x08000000

void iap_load_app(u32 appxaddr);	//��ת��APP����ִ��
#endif







































