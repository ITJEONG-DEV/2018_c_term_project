#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 30
#define MAX_CONTENT_LENGTH 100
#define MAX_STRING_LENGTH 250

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

void setPlan(_PLAN *plan ); // plan 초기 설정
_DAY * initTargetDay(int monthDay[]); // 오늘 날짜를 받아와서 기준일을 생성하는 함수

void displayPlan(_PLAN * plan); // 해당 날의 일정을 모두 출력하는 함수
void displayDay(_DAY * targetDay); // 해당 날의 정보를 모두 출력하는 함수
char displayMenu(); // 메뉴를 출력하는 함수

_DAY * addDay(_DAY * day, int type, int monthDay[]); // type > 0 then tomorrow else yesterday

_PLAN * addPlanContent(_PLAN * plan); // 실제로 plan에 데이터를 추가하는 함수
_DAY * addPlan(_DAY * day); // plan 데이터를 추가할 공간을 만드는 함수
_DAY * editPlan(_DAY * day); // plan 데이터를 수정하는 함수
_DAY * deletePlan(_DAY * day); // plan 데이터를 삭제하는 함수

int main()
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   _DAY * targetDay = initTargetDay(monthDay);

   char view_Type = 'D'; // Day Week Month 등 뷰 타입 변경
   int onlyRegisteredSchedules = 0; // 일정이 등록된 날짜만 보기

   char answer;

   // targetDay = addDay(targetDay., 1, monthDay);
   printf("\n\nTODAY : %s\n\n", getDayoftheWeek(targetDay->year, targetDay->month, targetDay->day));
}

// 
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

   int date = year*365;
   date += year/4;
   date +=day;
   date -= 2;

   for( i = 1; i < month; i++ )
   {
      if( isLeapYear(year) && i < 3 ) --date;
      // if( i == 2 && isLeapYear(year) ) ++date;

      date+=monthDay[i-1];
   }



   char * tmp = malloc(sizeof(char)*3);

   strcpy( tmp, dayoftheWeek[date%7]);

   return tmp;
}

// 
void setPlan(_PLAN * plan)
{   
   plan = (_PLAN * )malloc(sizeof(_PLAN));
   plan->title = NULL;
   plan->content = NULL;
}
_DAY * initTargetDay(int monthDay[])
{
   _DAY * targetDay = (_DAY *)malloc(sizeof(_DAY));

   int day;

   while(1)
   {
      printf("년 월 일을 입력하세요. 입력 형태 : 20181105\n> ");
      scanf("%d", &day);
      // printf("%d\n", day);

      targetDay->year = day/10000;
      // printf("year : %d\n", targetDay->year);
      if( targetDay->year < 0 )
      {
          printf("[error]올바른 년도를 입력하세요. 기원전의 연도는 취급하지 않습니다.\n");
          continue;
      }

      targetDay->month = (day/100)%100;
      // printf("month : %d\n", targetDay->month);
      if( targetDay->month < 1 || targetDay->month > 12 )
      {
         printf("[error]올바른 월을 입력하세요.\n");
         continue;
      }

      targetDay->day = day%100;
      // printf("day : %d\n", targetDay->day);
      if( targetDay->day < 1 || targetDay->day > monthDay[targetDay->month -1 ] )
      {
         printf("[error]올바른 일을 입력하세요.\n");
         continue;
      }

      break;
   }

   targetDay->tomorrow = NULL;
   targetDay->yesterday = NULL;

   setPlan(targetDay->plan);

   return targetDay;
}

// 
void displayPlan(_PLAN * plan)
{
  if(plan)
  {
    int sizeofPlan = sizeof(plan);
    int numberofPlan = sizeofPlan / sizeof(_PLAN);

    int i;

    for( i = 0; i < numberofPlan; i++, plan++)

    {
        printf(">%s\n%s\n\n", plan->title, plan->content);
    }
  }
  else
      printf("등록된 일정이 없습니다.\n\n");
}
void displayDay(_DAY * targetDay)
{
   printf("\n[ %4d-%2d-%2d ", targetDay->year, targetDay->month, targetDay->day);
   printf("%s ]\n\n", getDayoftheWeek(targetDay->year, targetDay->month, targetDay->day));

   int i = 0;

   displayPlan(targetDay->plan);
}
char displayMenu()
{
  char answer;

  printf("<이전\t\t\t|\t\t\t다음>\n");
  printf("=====================================================\n");
  printf("1. 타입 변경\n");
  printf("2. 일정 추가\n");
  printf("3. 일정 삭제\n");
  printf("4. 일정 수정\n");
  printf("0. 프로그램 종료\n");
  printf("( 이전 일정을 보려면 '<'를, 다음 일정을 보려면 '>'를 입력하세요 )\n\n> ");

  while(1)
  {
    scanf("%c", &answer);

    if( ( answer >= '0' && answer <= '4' ) || answer == '<' || answer == '>' )
      break;
  }

  return answer;
}

//
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

    setPlan(newDay->plan);

    return newDay;
}

//
_PLAN * addPlanContent(_PLAN * plan)
{
  char * tmp = (char *)malloc(sizeof(char)*MAX_STRING_LENGTH);

    while(1)
    {
        printf("일정의 제목을 입력하세요. 최대 %d자까지 입력.\n", MAX_TITLE_LENGTH );
        scanf("%s", tmp);
    }

    while(1)
    {
        printf("일정의 내용을 입력하세요. 최대 %d자까지 입력.\n", MAX_CONTENT_LENGTH );
        scanf("%s", tmp);
    }

    printf("입력이 완료되었습니다.\n");
    printf("> %s\n%s", plan->title, plan->content);
}
_DAY * addPlan(_DAY * day)
{
  _PLAN * tmpPlan = day->plan;

  if(day->plan)
  {
    int sizeofPlan = sizeof(day->plan);
    int sizeof_PLAN = sizeof(_PLAN);
    int numberofPlan = sizeofPlan/sizeof_PLAN;

    realloc( day->plan, sizeof(_PLAN) * (numberofPlan + 1));
    tmpPlan += numberofPlan;
  }
  else
  {
    tmpPlan = (_PLAN *)malloc(sizeof(_PLAN));
  }

    addPlanContent(tmpPlan);
}
_DAY * editPlan(_DAY * day)
{
  printf("아직 완성되지 않은 함수입니다.\n");

  return day;
}
_DAY * deletePlan(_DAY * day)
{
  printf("아직 완성되지 않은 함수입니다.\n");

  return day;
}
