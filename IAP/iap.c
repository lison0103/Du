#include "iap.h"
	

iapfun jump2app; 
u16 iapbuf[1024];   

//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	                        //���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		                //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
                __set_PSP(*(volatile unsigned int*) appxaddr);                  //�������ý���PSP��ջ��ַ
                __set_CONTROL(0);                                               //����CONTROL�Ĵ�����ֵ��������ʲôδ֪???
                __set_MSP(*(volatile unsigned int*) appxaddr);                  //�������ý���MSP��ջ��ַ
                jump2app();							//��ת��APP.
	}
}		 














