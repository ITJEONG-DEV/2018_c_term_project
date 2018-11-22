#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 30
#define MAX_CONTENT_LENGTH 100

#define MAX_MONTH 12
#define MAX_DATE 31

typedef struct Plan
{
   char * title;
   char * content;
} _PLAN;

typedef struct Day
{
   int year;
   int month;
   int day;

   _PLAN * plan;

   struct _DAY * tomorrow;
   struct _DAY * yesterday;
} _DAY;

int isLeapYear(int year); //윤년인지 아닌지를 판단하는 함수
char * getDayoftheWeek(int year, int month, int day); // 년, 월, 일을 넘기면 요일을 반환하는 함수
_DAY * initTargetDay(int monthDay[]); // 오늘 날짜를 받아와서 기준일을 생성하는 함수
void displayDay(_DAY * targetDay); // 해당 날의 정보를 모두 출력하는 함수
void displayPlan(_PLAN * plan); // 해당 날의 일정을 모두 출력하는 함수
_DAY * addDay(_DAY * day, int type, int monthDay[]); // type > 0 then tomorrow else yesterday
_PLAN * addPlanContext(_PLAN * plan); // 실제로 plan에 데이터를 추가하는 함수
_DAY * addPlan(_DAY * day); // plan 데이터를 추가할 공간을 만드는 함수
_DAY * editPlan(_DAY * day); // plan 데이터를 수정하는 함수
_DAY * deletePlan(_DAY * day); // plan 데이터를 삭제하는 함수

int main()
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   _DAY * targetDay = initTargetDay(monthDay);

   char view_Type = 'D'; // Day Week Month 등 뷰 타입 변경
   int onlyRegisteredSchedules = 0; // 일정이 등록된 날짜만 보기

   targetDay = addDay(targetDay, 1, monthDay);

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
   _DAY * targetDay = (_DAY *)malloc(sizeof(_DAY));

   int day;

   while(1)
   {
      printf("년 월 일을 입력하세요. 입력 형태 : 20181105\n> ");
      scanf("%d", &day);
      printf("%d\n", day);

      targetDay->year = day/10000;
      printf("year : %d\n", targetDay->year);
      if( targetDay->year < 0 )
      {
          printf("[error]올바른 년도를 입력하세요. 기원전의 연도는 취급하지 않습니다.\n");
          continue;
      }

      targetDay->month = (day/100)%100;
      printf("month : %d\n", targetDay->month);
      if( targetDay->month < 1 || targetDay->month > 12 )
      {
         printf("[error]올바른 월을 입력하세요.\n");
         continue;
      }

      targetDay->day = day%100;
      printf("day : %d\n", targetDay->day);
      if( targetDay->day < 1 || targetDay->day > monthDay[targetDay->month] )
      {
         printf("[error]올바른 일을 입력하세요.\n");
         continue;
      }

      break;
   }

   return targetDay;
}

void displayPlan(_PLAN * plan)
{
    int sizeofPlan = sizeof(plan);
    int numberofPlan = sizeofPlan / sizeof(_PLAN);
    int i;

    for( i = 0; i < numberofPlan; i++, plan++)

    {
        printf(">%s\n%s\n\n", plan->title, plan->content);
    }
}

void displayDay(_DAY * targetDay)
{
   printf("%4d-%2d-%2d ", targetDay->year, targetDay->month, targetDay->day);
   printf("%s\n", getDayoftheWeek(targetDay->year, targetDay->month, targetDay->day));

   int i = 0;

   displayPlan(targetDay->plan);
}

_DAY * addDay(_DAY * day, int type, int monthDay[])
{
    _DAY * newDay = (_DAY *)malloc(sizeof(_DAY));


    if(type > 0)
    {
        day->tomorrow = newDay;
        newDay->yesterday = day;

        newDay->day = day->day + 1;
        newDay->month = day->month;
        newDay->year = day->year;

        if(newDay->day > monthDay[day->month -1])
        {
            newDay->day = 1;
            newDay->month = newDay->month + 1;
        }

        if(newDay->month > MAX_MONTH)
        {
            newDay->month = 1;
            newDay->year = newDay->year + 1;
        }
    }
    else
    {
        day->yesterday = newDay;
        newDay->tomorrow = day;

        newDay->day = day->day - 1;
        newDay->month = day->month;
        newDay->year = day->year;

        if(newDay->day < 1 )
        {
            newDay->day = monthDay[(newDay->month +10)%12];
            if(newDay->month == 1) newDay->year = newDay->year - 1;
            newDay->month = (newDay->month + 10)%12 + 1;
        }

    }

    return newDay;
}

_PLAN * addPlanContext(_PLAN * plan)
{
    while(1)
    {
        printf("일정의 제목을 입력하세요. 최대 %d자까지 입력.\n", MAX_TITLE_LENGTH );
        if( gets( plan->title ) ) break;
    }

    while(1)
    {
        printf("일정의 내용을 입력하세요. 최대 %d자까지 입력.\n", MAX_CONTENT_LENGTH );
        if( gets( plan->content) ) break;
    }

    printf("입력이 완료되었습니다.\n");
    printf("> %s\n%s", plan->title, plan->content);
}

_DAY * addPlan(_DAY * day)
{
    int sizeofPlan = sizeof(day->plan);
    int sizeof_PLAN = sizeof(_PLAN);
    int numberofPlan = sizeofPlan/sizeof_PLAN;

    _PLAN * tmpPlan = day->plan;

    if( ! ( numberofPlan == 1 && !strcmp( day->plan->title, "\0") ) )
    {
        realloc( day->plan, sizeof(_PLAN) * (numberofPlan + 1));
        tmpPlan += numberofPlan;
    }

    addPlanContext(tmpPlan);
}
