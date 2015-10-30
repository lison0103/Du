#include "iap.h"
	

iapfun jump2app; 
u16 iapbuf[1024];   

//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	                        //检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		                //用户代码区第二个字为程序开始地址(复位地址)		
                __set_PSP(*(volatile unsigned int*) appxaddr);                  //重新设置进程PSP堆栈地址
                __set_CONTROL(0);                                               //设置CONTROL寄存器的值，作用是什么未知???
                __set_MSP(*(volatile unsigned int*) appxaddr);                  //重新设置进程MSP堆栈地址
                jump2app();							//跳转到APP.
	}
}		 














