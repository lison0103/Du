
#include "includes.h"
//$PROJ_DIR$\..\Libraries\CMSIS\Core\CM3
//$PROJ_DIR$\..\Libraries\CMSIS\Core\CM3\startup\iar

#include "ff.h"

//@
OS_STK task_WDT_Init_stk[TASK_WDT_INIT_STK_SIZE];
//@end

OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //定义栈

OS_STK task_menu_stk[TASK_MENU_STK_SIZE];		        //定义栈

OS_STK app_task_main_stk[AppTask_COM_STK_SIZE];	  //定义栈
OS_STK app_task_com_stk[AppTask_COM_STK_SIZE];	  //定义栈
OS_STK app_task_key_stk[AppTask_KEY_STK_SIZE];	  //定义栈

OS_STK task_display_stk[TASK_DISPLAY_STK_SIZE];

OS_STK task_LCM_Init_stk[TASK_LCM_INIT_STK_SIZE];

OS_STK task_READ_ECT_stk[TASK_READ_ECT_STK_SIZE];

u8 ModBuff[5800];
u16 *pt_ModBuff = (u16*)&ModBuff[0];

void Task_LCM_Init(void *p_arg);
void Task_READ_ECT(void *p_arg);


/*******************************************************************************
*******************************************************************************/
void Task_Start(void *p_arg)
{
//	static u16 ewrfwe=0;
//  GPIO_InitTypeDef    GPIO_InitStruct;

  (void)p_arg;   // 'p_arg' 并没有用到，防止编译器提示警告
  
  SysTick_init();
	
  //OSStatInit();                     /* 初始化统计任务*/
	
  //sem = OSSemCreate(1);

  //@
    OSTaskCreate(Task_WDT_Init,(void *)0,		  	   
    &task_WDT_Init_stk[TASK_WDT_INIT_STK_SIZE-1], TASK_WDT_INIT_PRIO);
  //@end
    
  OSTaskCreate(Task_LCM_Init,(void *)0,		  	   
    &task_LCM_Init_stk[TASK_LCM_INIT_STK_SIZE-1], TASK_LCM_INIT_PRIO);
  
  OSTaskCreate(Task_Menu,(void *)0,		  	    
    &task_menu_stk[TASK_MENU_STK_SIZE-1], TASK_MENU_PRIO);

	OSTaskCreate(AppTask_Main,(void *)0,		   
	   &app_task_main_stk[AppTask_MAIN_STK_SIZE-1], AppTask_MAIN_PRIO);

	OSTaskCreate(AppTask_COM,(void *)0,	         
	   &app_task_com_stk[AppTask_COM_STK_SIZE-1], AppTask_COM_PRIO);
  
	OSTaskCreate(AppTask_KEY,(void *)0,		   	  
	   &app_task_key_stk[AppTask_KEY_STK_SIZE-1], AppTask_KEY_PRIO);

	OSTaskCreate(Task_Display,(void *)0,		   	 
	   &task_display_stk[TASK_DISPLAY_STK_SIZE-1], TASK_DISPLAY_PRIO);
  
	OSTaskCreate(Task_READ_ECT,(void *)0,		    
	   &task_READ_ECT_stk[TASK_READ_ECT_STK_SIZE-1], TASK_READ_ECT_PRIO);

  while (1)
  {
    // GPIOC->ODR ^= 0X8000;
    // OSTimeDlyHMSM(0, 0,0,500);  
    OSTimeDlyHMSM(0, 0,0,500);   
  }
}

/*******************************************************************************
*******************************************************************************/
void main(void)
{  
//  u16 i,j;
//  u32 k;
 
  //@
  SCB->VTOR = FLASH_BASE | 0x10000;
  //@end
  
  Delay_us(1000);
  
  BSP_Init();  
  
  //spi_flash_q64_init();

  //SPI_FLASH_Init();
  
  /* SD 卡硬件初始化，并初始化盘符为0 */	
	//disk_initialize( 0 );

/*  
  res = f_mount(0, &fs);	
  
  res = f_open(&file, "data.txt", FA_CREATE_NEW); //FA_OPEN_EXISTING | FA_READ
*/  
  

  
  OSInit();

  OSTaskCreate(Task_Start,(void *)0,
              &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);

  OSStart();
 
  while(1);
  //return(0);     
  
}

/*******************************************************************************
*******************************************************************************/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

/**
  * @}
  */ 
#endif

/**
  * @}
  */ 

