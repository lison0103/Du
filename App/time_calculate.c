#include "includes.h"

u32 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};


//功能:是否为闰年
//参数:
//返回:
//1----成功
//0--失败
//修改:
//备注:
 
 u32 Leap_Year(u32 year)
{
         return  ((year % 400 == 0) || ((year % 4 == 0)&& (year % 100 != 0))) ? 1 : 0;
}

//功能: 将年转化为天
//参数:
//返回:
//sum---转化的天数
//修改:
//备注:
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
//功能:将月转化为天数
//参数:
//返回:
//-----转化完成的天数
//修改:
//备注:
 u32 Month_To_Day(u8 Month[])
{
         u32 i;
         u32 year = 2000 + Month[0]*10 + Month[1];
         u32 mmonth = Month[2]*10 + Month[3];
         u32 day = Month[4]*10 + Month[5];
 
         for (i = 0; i < mmonth - 1; ++i)
         {
                   day = day + month[i];
         }
 
         return (mmonth >= 3) ? day + Leap_Year(year) :  day;
 
}
//功能:计算两个日期之间的差值
//参数:
//begin---起始日期
//end----结束日期
//返回:
//---算出的时间差值
//修改:
//备注:
//且begin <= end
 u32 Calculate(u8 begin[],u8 end[])
{
         return Year_To_Day(begin, end) - Month_To_Day(begin) + Month_To_Day(end);
}
 
