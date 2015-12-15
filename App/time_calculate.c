/****************************************Copyright (c)****************************************************
** File Name:           time_calculate.c
** Created By:          lisonchen
** Created date:        2015-09-21
** Version:             v1.00
** Descriptions:        日期时间计算
**
*********************************************************************************************************/

#include "includes.h"

const u8 *Time_Calculate_Descrip[][2] = 
{
  {" 时钟异常！！"," RTC ERROR!!"},
  {" 未知异常！！"," UNKNOW ERROR!!"}
};


u8 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/*******************************************************************************
//功能:是否为闰年
//返回: 1 闰年 0 非闰年
*******************************************************************************/
u8 Leap_Year(u32 year)
{
         return  ((year % 400 == 0) || ((year % 4 == 0)&& (year % 100 != 0))) ? 1 : 0;
}

/*******************************************************************************
//功能: 将年转化为天
//返回: sum 转化的天数
*******************************************************************************/
 u32 Year_To_Day(u8 year_begin[], u8 year_end[])
{
         u32 sum = 0;
         u32 number_begin = 2000 + year_begin[0]*10 + year_begin[1];
         u32 number_end = 2000 + year_end[0]*10 + year_end[1];
 
         while(number_begin != number_end)
         {
                   sum = sum + 365 + Leap_Year(number_begin);
                   number_begin++;
         }
 
         return sum;
}

/*******************************************************************************
//功能:将月转化为天数
//返回:转化完成的天数
*******************************************************************************/
u32 Month_To_Day(u8 Date[])
{
         u32 i;
         u32 year = 2000 + Date[0]*10 + Date[1];
         u32 mmonth = Date[2]*10 + Date[3];
         u32 day = Date[4]*10 + Date[5];
 
         for (i = 0; i < mmonth - 1; ++i)
         {
                   day = day + month[i];
         }
 
         return (mmonth >= 3) ? day + Leap_Year(year) :  day;
 
}

/*******************************************************************************
//功能:计算两个日期之间的差值
//参数:begin 起始日期  end 结束日期，且begin <= end
//返回:算出的时间差值
*******************************************************************************/
s32 Calculate(u8 begin[],u8 end[])
{
         u32 number_begin = begin[0]*100000 + begin[1]*10000 + begin[2]*1000 + begin[3]*100 + begin[4]*10 + begin[5];
         u32 number_end = end[0]*100000 + end[1]*10000 + end[2]*1000 + end[3]*100 + end[4]*10 + end[5];
         
         if(number_begin > number_end)
         {
            return -1;
         }
         else if(number_begin == number_end)
         {
            return 0;
         }
         else
         {
           return Year_To_Day(begin, end) - Month_To_Day(begin) + Month_To_Day(end);
         }  
         
}

/*******************************************************************************
//功能:判断日期的有效性
//返回:有效：0， 无效:不为0
*******************************************************************************/
u8 Date_Validity(u8 Date[])
{

         u32 year = 2000 + Date[0]*10 + Date[1];
         u32 mmonth = Date[2]*10 + Date[3];
         u32 day = Date[4]*10 + Date[5];
 
         if(year > 2099 || year < 2015)
         {
            return 1;
         }
         else if(mmonth > 12 || mmonth < 1)
         {
            return 2;
         }
         else if(mmonth == 2 && Leap_Year(year))
         {
              if(day > 29 || day < 1)
              {
                  return 3;
              }
              else
              {
                  return 0;
              }
         }
         else if(day > month[mmonth - 1] || day < 1)
         {           
           return 4;
         }
         else
         {
            return 0;
         }
         
 
}

/*******************************************************************************
//功能:提示时钟错误
*******************************************************************************/
void Rtc_Error_display(void)
{

    ZTM_RectangleFill (0,0,239,319,LGRAY);
    OSTimeDlyHMSM(0, 0,0,10);
    
    
    TXM_StringDisplay(0,50,150,24,1,BLACK ,RED, (void*)Time_Calculate_Descrip[0][LANGUAGE]); 
     
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500); 
    
    OSTimeDlyHMSM(0, 0,2,0);

}

/*******************************************************************************
//功能:提示未知异常
*******************************************************************************/
void Unknow_Error_display(void)
{

    ZTM_RectangleFill (0,0,239,319,LGRAY);
    OSTimeDlyHMSM(0, 0,0,10);
    
    
    TXM_StringDisplay(0,50,150,24,1,BLACK ,RED, (void*)Time_Calculate_Descrip[1][LANGUAGE]); 
     
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500); 
    
    OSTimeDlyHMSM(0, 0,2,0);

}
