//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : app_cfg.h
//*
//* 文件描述 : 系统配置文件
//*
//* 作    者 : 
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

#include "ucos_ii.h"
//#include "stm32f10x_lib.h"

//#ifdef   OS_GLOBALS
//#define  OS_EXT
//#else
//#define  OS_EXT  extern
//#endif

//#include "Task_includes.h"


//*********************************************************************************************************
//*****************************************    系统升级记录     *******************************************
//*********************************************************************************************************
//---------------------------------------------------------------------------------------------------------
// 本系统软件版本和升级记录
//---------------------------------------------------------------------------------------------------------
// 工程样机第一版
//#define Software_Versions         (100)
//---------------------------------------------------------------------------------------------------------
#define Software_Versions           (101)
//---------------------------------------------------------------------------------------------------------
// 本系统所能支持的硬件版本和升级记录
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
// 工程样机第一版
//#define Hardware_Versions           (100)
//---------------------------------------------------------------------------------------------------------
#define Hardware_Versions           (100)



//*********************************************************************************************************
//*****************************************    函数声明    ************************************************
//*********************************************************************************************************
//void CreateMultiTask (void);
//void CreateEvents(void);
//void OS_CPU_SysTickInit (void);
//void Target_Init(void);

#endif
