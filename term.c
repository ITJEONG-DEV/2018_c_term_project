#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE_LENGTH 30
#define MAX_CONTENT_LENGTH 100

#define MAX_MONTH 12
#define MAX_DATE 31

typedef struct
{
   char *title;
   char *content;
} _PLAN;

typedef struct
{
   int year;
   int month;
   int day;

   _PLAN *plan;

   struct _DAY *tomorrow;
   struct _DAY *yesterday;
} _DAY;

int isLeapYear(int year); //윤년인지 아닌지를 판단하는 함수
char * getDayoftheWeek(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 반환하는 함수
_DAY * initTargetDay(int monthDay[]); // 오늘 날짜를 받아와서 기준일을 생성하는 함수
void displayDay(_DAY * targetDay);

int main()
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   _DAY * targetDay = initTargetDay(monthDay);

   char view_Type = 'D'; // Day Week Month
   int onlyRegisteredSchedules = 0;

   targetDay->plan = (_PLAN*)malloc(sizeof(_PLAN));
   targetDay->plan->title = (char*)malloc(sizeof(char * MAX_TITLE_LENGTH));
   targetDay->plan->title = "test title yeah";
   targetDay->plan->content = (char*)malloc(sizeof(char * MAX_CONTENT_LENGTH));
   targetDay->plan->content = "test content yeah";

   displayDay(targetDay);
}

int isLeapYear(int year)
{
   if( !(year % 4) && (year % 100) || !(year % 400) ) return 1;
   else return 0;
}

char * getDayoftheWeek(int year, int month, int day)
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   char dayoftheWeek[7][4] = { "SUN\0", "MON\0", "TUE\0", "WED\0", "THU\0", "FRI\0", "SAT\0" };

   // 1900년 1월 1일은 월요일
   // 일월화수목금토 0 ~ 6

   int i;

   int date = (year-1900)*365;

   for( i = 1; i < month; i++ )
   {
      if( i == 2 && isLeapYear(year) )
         ++date;

      date+=monthDay[i];
   }

   date+=day;

   char * tmp = malloc(sizeof(char)*3);

   strcpy( tmp, dayoftheWeek[date&7]);

   return tmp;
}

_DAY * initTargetDay(int monthDay[])
{
   _DAY * targetDay;

   int day;

   while(1)
   {
      printf("년 월 일을 입력하세요. 입력 형태 : 20181105\n> ");
      scanf("%d", &day);

      targetDay->year = day/10000;
      targetDay->month = (day/100)%100;
      if( targetDay->month < 1 || targetDay->month > 12 )
      {
         printf("[error]올바른 월을 입력하세요.\n");
         continue;
      }
      targetDay->day = day%100;
      if( targetDay->day < 1 || targetDay->day > monthDay[targetDay->month] )
      {
         printf("[error]올바른 일을 입력하세요.\n");
         continue;
      }

      break;
   }

   return targetDay;
}

void displayDay(_DAY * targetDay)
{
   printf("%4d-%2d-%2d ", targetDay->year, targetDay->month, targetDay->day);
   printf("%s\n", getDayoftheWeek(targetDay->year, targetDay->month, targetDay->day));

   int i = 0;

   while( targetDay->plan )
   {
      printf("> %s\n", targetDay->plan->title );
      printf("%s\n\n", targetDay->plan->content );

      ++i;
   }
}