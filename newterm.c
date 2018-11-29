#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 30
#define MAX_CONTENT_LENGTH 100

#define MAX_YEAR 2500
#define MAX_MONTH 12
#define MAX_DATE 31

typedef struct
{
   char * title;
   char * content;
} Plan;

int isLeapYear(int year); //윤년인지 아닌지를 판단하는 함수
int getDayoftheWeekNum(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 숫자로 반환
char * getDayoftheWeek(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 문자(3)로 반환
Plan **** initialSet(Plan **** plan, int monthDay[]); // 처음의 기준 날짜를 만들어주는 함수
Plan **** createYear(Plan **** plan, int numberofYear);
Plan *** createMonth(Plan *** plan);
Plan ** createDay(Plan ** plan, int numberofDay);

int main()
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   Plan **** year = NULL;

   year = initialSet(MAX_YEAR, monthDay);

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

   char * tmp;

   strcpy( tmp, dayoftheWeek[getDayoftheWeekNum(year,month,day)-1]);

   return tmp;
}

Plan **** initialSet(Plan **** plan, int monthDay[])
{
    int date;
    int year, month, day;

    while(1)
    {
        printf("기준 날짜를 입력하세요. 예시)20181125\n\n> ");
        scanf("%d", &date);

        year = date/10000;
        if( year < 0 )
        {
            printf("ERROR001:올바른 년도를 입력하세요. 기원전의 연도는 취급하지 않습니다.\n");
            continue;
        }

        month = (date/100)%100;
        if( month < 1 || month > 12 )
        {
            printf("ERROR002:올바른 월을 입력하세요. 1월부터 12월 사이만 유효합니다.\n");
            continue;
        }

        day = date%100;
        if( day < 1 || day > monthDay[month-1] )
        {
            printf("ERROR003:올바른 일을 입력하세요. %d월은 1일부터 %d일까지 있습니다.\n", month, monthDay[month-1]);
            continue;
        }

        break;
    }

    return createYear(plan, year);
}

Plan **** createYear(Plan **** plan, int numberofYear)
{
    if (plan)
    {
        plan = ( Plan **** )realloc( plan, sizeof( Plan *** ) * (numberofYear));
    }
    else
    {
        plan = ( Plan **** )malloc( sizeof( Plan *** ) * numberofYear);
    }

    return plan;
}

Plan *** createMonth(Plan *** plan)
{
    int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (!plan)
    {
        plan = ( Plan *** )malloc( sizeof( Plan ** ) * 12 );

        int i;

        for(i = 0; i < 12; i++)
            plan[i] = createDay(monthDay[i] + )
    }

    return plan;
}

Plan ** createDay(int numberofDay)
{
    if (!plan)
    {
        plan = ( Plan ** )malloc( sizeof( Plan * ) * numberofDay );
    }

    return plan;
}
