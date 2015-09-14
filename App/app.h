
#ifndef _APP_H_
#define _APP_H_

#define MB_COM_PORT       USART1
#define LCM_COM_PORT      USART2
#define PC_COM_PORT       USART3

typedef struct
{
  u16 ID;
  u16 menuType;  
  u16 picNumber;
  
//  u16 textBar[10];  
  
}MENU_STRUCT_DEF;


void Task_Start(void *p_arg);



void para_setup(u8 paraitem);

void error_record(void);

extern OS_EVENT *msgEvent_MCLCM;

extern const u16 HelpArrayPictureIndex[];
extern const u16 MenuArrayPictureIndex[];

extern u16 menuItemNumber;
extern u16 menu_flag;

#endif //_APP_H_
