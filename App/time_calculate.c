/****************************************Copyright (c)****************************************************
** File Name:           time_calculate.c
** Created By:          lisonchen
** Created date:        2015-09-21
** Version:             v1.00
** Descriptions:        ����ʱ�����
**
*********************************************************************************************************/

#include "includes.h"

u8 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/*******************************************************************************
//����:�Ƿ�Ϊ����
//����: 1 ���� 0 ������
*******************************************************************************/
u8 Leap_Year(u32 year)
{
         return  ((year % 400 == 0) || ((year % 4 == 0)&& (year % 100 != 0))) ? 1 : 0;
}

/*******************************************************************************
//����: ����ת��Ϊ��
//����: sum ת��������
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
//����:����ת��Ϊ����
//����:ת����ɵ�����
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
//����:������������֮��Ĳ�ֵ
//����:begin ��ʼ����  end �������ڣ���begin <= end
//����:�����ʱ���ֵ
*******************************************************************************/
 u32 Calculate(u8 begin[],u8 end[])
{
         u32 number_begin = begin[0]*100000 + begin[1]*10000 + begin[2]*1000 + begin[3]*100 + begin[4]*10 + begin[5];
         u32 number_end = end[0]*100000 + end[1]*10000 + end[2]*1000 + end[3]*100 + end[4]*10 + end[5];
         
         if(number_begin > number_end)
         {
            return -1;
         }
         else if(number_begin = number_end)
         {
            return 0;
         }
         else
         {
           return Year_To_Day(begin, end) - Month_To_Day(begin) + Month_To_Day(end);
         }  
         
}

/*******************************************************************************
//����:�ж����ڵ���Ч��
//����:��Ч 1�� ��Ч 0
*******************************************************************************/
u32 Date_Validity(u8 Date[])
{

         u32 year = 2000 + Date[0]*10 + Date[1];
         u32 mmonth = Date[2]*10 + Date[3];
         u32 day = Date[4]*10 + Date[5];
 
         if(year > 2099 || year < 2015)
         {
            return 0;
         }
         else if(mmonth > 12 || mmonth < 1)
         {
            return 0;
         }
         else if(mmonth == 2 && Leap_Year(year))
         {
              if(day > 29 || day < 1)
              {
                  return 0;
              }
              else
              {
                  return 1;
              }
         }
         else if(day > month[mmonth] || day < 1)
         {           
           return 0;
         }
         else
         {
            return 1;
         }
         
 
}

/*******************************************************************************
//����:��ʾʱ�Ӵ���
*******************************************************************************/
void Rtc_Error_display(void)
{

    ZTM_RectangleFill (0,0,239,319,LGRAY);
    OSTimeDlyHMSM(0, 0,0,10);
    
    
    TXM_StringDisplay(0,50,150,24,1,BLACK ,RED, " ʱ���쳣����"); 
     
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500); 
    
    OSTimeDlyHMSM(0, 0,2,0);

}

/*******************************************************************************
//����:��ʾδ֪�쳣
*******************************************************************************/
void Unknow_Error_display(void)
{

    ZTM_RectangleFill (0,0,239,319,LGRAY);
    OSTimeDlyHMSM(0, 0,0,10);
    
    
    TXM_StringDisplay(0,50,150,24,1,BLACK ,RED, " δ֪�쳣����"); 
     
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500);
     ZTM_SetBuzzer(30);
     OSTimeDlyHMSM(0, 0,0,500); 
    
    OSTimeDlyHMSM(0, 0,2,0);

}
