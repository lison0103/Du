u32 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  
//����: ����ת��Ϊ��
//����:
//����:
//sum---ת��������
//�޸�:
//��ע:
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
//����:����ת��Ϊ����
//����:
//����:
//-----ת����ɵ�����
//�޸�:
//��ע:
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
//����:������������֮��Ĳ�ֵ
//����:
//begin---��ʼ����
//end----��������
//����:
//---�����ʱ���ֵ
//�޸�:
//��ע:
//fast_sky@sina.com
//��begin <= end
 u32 Calculate(date begin,date end)
{
         return Year_To_Day(begin.year, end.year) - Month_To_Day(begin) + Month_To_Day(end);
}
 
//����:�Ƿ�Ϊ����
//����:
//����:
//1----�ɹ�
//0--ʧ��
//�޸�:
//��ע:
//fast_sky@sina.com
 
 u32 Leap_Year(u32 year)
{
         return  ((year % 400 == 0) || ((year % 4 == 0)&& (year 0 != 0))) ? 1 : 0;
}