u32 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  
//功能: 将年转化为天
//参数:
//返回:
//sum---转化的天数
//修改:
//备注:
//fast_sky@sina.com
 u32 Year_To_Day(u32 year_begin, u32 year_end)
{
         u32 sum = 0;
         u32 number = year_begin;
 
         while(number != year_end)
         {
                   sum = sum + 365 + Leap_Year(year_begin);
                   number++;
         }
 
         return sum;
}
//功能:将月转化为天数
//参数:
//返回:
//-----转化完成的天数
//修改:
//备注:
//fast_sky@sina.com
 u32 Month_To_Day(u32 month)
{
         u32 i, day = 0;
 
         for (i = 0; i < month - 1; ++i)
         {
                   day = day + month[i];
         }
 
         return (month >= 3) ? day + day + Leap_Year(year) :  day + day;
 
}
//功能:计算两个日期之间的差值
//参数:
//begin---起始日期
//end----结束日期
//返回:
//---算出的时间差值
//修改:
//备注:
//fast_sky@sina.com
//且begin <= end
 u32 Calculate(date begin,date end)
{
         return Year_To_Day(begin.year, end.year) - Month_To_Day(begin) + Month_To_Day(end);
}
 
//功能:是否为闰年
//参数:
//返回:
//1----成功
//0--失败
//修改:
//备注:
//fast_sky@sina.com
 
 u32 Leap_Year(u32 year)
{
         return  ((year % 400 == 0) || ((year % 4 == 0)&& (year 0 != 0))) ? 1 : 0;
}