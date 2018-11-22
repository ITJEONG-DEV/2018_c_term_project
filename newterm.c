#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
   char * title;
   char * content;
} Plan;

int isLeapYear(int year); //윤년인지 아닌지를 판단하는 함수
int getDayoftheWeekNum(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 숫자로 반환
char * getDayoftheWeek(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 문자(3)로 반환




int main()
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   _PLAN * day;
   _PLAN ** month;
   _PLAN *** year;
}

int isLeapYear(int year)
{
   if( ( year % 4 ) && !( year % 100 ) || ( year % 400 ) ) return 1;
   else return 0;
}
int getDayoftheWeekNum(int year, int month, int day)
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   int i;
   int date = (year-1900)*365;

   for( i = 1; i < month; i++ )
   {
      if( i == 2 && isLeapYear(year) ) date++;

      date += monthDay[i];
   }

   date += day;

   return date & 7;
}
char * getDayoftheWeek(int year, int month, int day)
{
   char dayoftheWeek[7][4] = { "SUN\0", "MON\0", "TUE\0", "WED\0", "THU\0", "FRI\0", "SAT\0" };

   return dayoftheWeek[getDayoftheWeekNum(year,month,day)];
}