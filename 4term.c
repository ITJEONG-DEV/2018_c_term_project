#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_YEAR 9999
#define MIN_YEAR 1900
#define MAX_MONTH 12
#define MIN_MONTH 1
#define MONTH_31 31
#define MONTH_30 30
#define MONTH_28 28
#define MIN_DAY 1

typedef struct
{
   char * title;
   char * content;
} Plan;



// primary function
char editViewType();
int editViewTypeOnlyScheduledDays();
void addPlan(Plan * data);
void deletetPlan(Plan **** data);
void editPlan(Plan **** data);

// show data
void showPlan(Plan * plan);
void showDay(int date, Plan **** data);
char showMenu();

// init data
Plan ** initMonth(int monthy, int isLeap);
Plan *** initYear(int isLeap);
Plan **** initData(int year);

void main(void)
{
   int monthDay[] = { 1, 3, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1 };
   int date = inValidDate(0);
   int NOW_MAX_YEAR = getYear(date);
   int VIEW_TYPE = 'D';
   int VIEW_ONLY_SCHEDULED_DAYS = 0;

   Plan **** data = NULL;

   data = initData(NOW_MAX_YEAR);

   while(1)
   {
      showDay( date, data );

      switch(showMenu())
      {
         case '0' :
            return;
         case '1' :
            VIEW_TYPE = editViewType();
            VIEW_ONLY_SCHEDULED_DAYS = editViewTypeOnlyScheduledDays();
            printf("정상적으로 변경되었습니다.\n");
         break;
         case '2' :
            addPlan(data[getYear(date)-MIN_YEAR][getMonth(date)][getDay(date)]);
         break;
         case '3' :
            printf("3\n");
         break;
         case '4' :
            printf("4\n");
         break;
         case '5' :
            printf("5\n");
         break;
         case '<' :
            printf("<\n");
         break;
         case '>' :
            printf(">\n");
         break;
      }
   }
}


// primary function
char editViewType()
{
   int n;

   while(1)
   {
      printf("일정 보여주기 방식을 변경합니다.\n");
      printf("1. 일 단위로 보여주기\n");
      printf("2. 주 단위로 보여주기\n");
      printf("3. 월 단위로 보여주기\n");

      scanf("%d", &n);

      switch(n)
      {
         case 1:
            return 'd';
         case 2:
            return 'w';
         case 3:
            return 'm';
      }

      printf("잘못 입력하셨습니다.\n");
   }
}
int editViewTypeOnlyScheduledDays()
{
   int n;

   printf("일정이 있는 날만 표시하는 모드입니다.\n");
   printf("적용하시겠습니까? 네-1/아니오-0\n");

   scanf("%d", &n);

   if(n==1)
      return 1;
   else
      return 0;
}
void addPlan(Plan * data)
{
   int size;
   char * tmp1;
   char * tmp2;

   if(data)
   {
      size = sizeof(data)/sizeof(Plan);
      data = realloc(data, sizeof(Plan)*(size+1));
   }
   else
   {
      size = 1;
      data = malloc(sizeof(Plan)*1);
      data[0].title = NULL;
      data[0].content = NULL;
   }

   while(1)
   {
      printf("타이틀을 입력하세요.");
      scanf("%s", tmp1);

      if(tmp1) break;
   }

   while(1)
   {
      printf("내용을 입력하세요.");
      scanf("%s", tmp2);

      if(tmp2) break;
   }

   if(size==1)
   {
      strcpy(data[0].title, tmp1);
      strcpy(data[0].content, tmp2);
   }
   else
   {
      strcpy(data[size].title, tmp1);
      strcpy(data[size].content, tmp2);
   }
}

// show data
void showPlan(Plan * plan)
{
   int lengthOfPlan = sizeof(plan)/sizeof(Plan);
   int i;

   for(i=0;i<lengthOfPlan;i++)
      printf("> %s\n%s\n", plan[i].title, plan[i].content);

}
void showDay(int date, Plan **** data)
{
   int y = getYear(date), m = getMonth(date), d = getDay(date);

   printf("[ %4d-%2d-%2d %s ]\n", y, m, d, getDayoftheWeek(y,m,d));
   if(data[y-MIN_DAY])
   {
      showPlan(data[y][m][d]);
   }
}
char showMenu()
{
	char c;

	while(1)
	{
		printf("\n\n<이전\t\t\t|\t\t\t다음>\n");
		printf("=====================================================\n");
		printf("0. 프로그램 종료\n");
		printf("1. 타입 변경\n");
		printf("2. 일정 추가\n");
		printf("3. 일정 삭제\n");
		printf("4. 일정 수정\n");
		printf("5. 원하는 날짜로 이동\n");
		printf("( 이전 일정을 보려면 '<'를, 다음 일정을 보려면 '>'를 입력하세요.\n>> ");

		scanf(" %c", &c);

	   if( ( c >= '0' && c <= '5' ) || c == '<' || c == '>' )
	   	return c;

   	printf("제대로 된 값을 입력해 주세요.\n");
	}
}

// init data
Plan ** initMonth(int monthy, int isLeap)
{
   Plan ** month = malloc(sizeof(Plan*)*(getMonthDay(monthy)+isLeap));

   return month;
}
Plan *** initYear(int isLeap)
{
   Plan *** year = malloc(sizeof(Plan **)*MAX_MONTH);

   int i;

   for(i = 0; i <MAX_MONTH; i++)
      year[i] = initMonth(i, isLeap);

   return year;
}
Plan **** initData(int year)
{
   Plan **** data = malloc(sizeof(Plan ***)*(year-MIN_YEAR+1));

   int i;

   for(i=MIN_YEAR;i<=year;i++)
      data[i-MIN_YEAR] = initYear(isLeapYear(i));

   return data;
}
