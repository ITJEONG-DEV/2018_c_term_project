#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_YEAR 2100
#define MIN_YEAR 1900
#define MAX_MONTH 12
#define MIN_MONTH 1
#define DAY_31 31
#define DAY_30 30
#define DAY_28 28
#define MIN_DAY 1

typedef struct _Plan
{
   char * title;
   char * content;
} Plan;

// basic function
int isLeapYear(int year);
int getDay(int date);
int getMonth(int date);
int getYear(int date);
int getMonthDay(int month);
int inValidDate(int type);
int getDayoftheWeekNum(int date);
char * getDayoftheWeek(int date);

char showMenu();
char editViewType();

// count
int getPlanCount(int *** planCount, int date);
void setPlanCount(int *** planCount, int num, int date);
int *** resetPlanCount(int *** planCount, int date);
int *** initPlanCountYear();
int ** initPlanCountMonth(int year);
int * initPlanCountDay(int month, int year);

Plan * addPlans(Plan * plans, int date, int *** planCount);
Plan addPlan();
Plan deletePlan(Plan plan);
Plan editPlan();

Plan * returnDay(Plan ** data, int date);
Plan ** returnMonth(Plan *** data, int date);
Plan *** returnYear(Plan **** data, int date);

Plan * initDay();
Plan ** initMonth(int year, int month);
Plan *** initYear(int year);
Plan **** initData();

void freeDay(Plan * data);
void freeMonth(Plan ** data, int year, int month);
void freeYear(Plan *** data, int year);
void freeData(Plan **** data);


int main()
{
   int *** planCount = initPlanCountYear();
   Plan **** data = initData();
   int count;
   int i, j, k, l;
   int y,m,d;

   int VIEW_TYPE = 'd';

   int date = inValidDate(0);


   while(1)
   {
      Plan *** year = returnYear(data, date);
      Plan ** month = returnMonth(year, date);
      Plan * day = returnDay(month, date);

      count = getPlanCount(planCount, date);

      printf("\n\nVIEW_TYPE : %c\n\n", VIEW_TYPE);

      switch(VIEW_TYPE)
      {
         case 'd' :
            if(count==0)
            {
               printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));
            }
            else
            {
               printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));

               for(i=0;i<count;i++)
               {
                  if((day+i)->title == NULL)
                  {
                     planCount = resetPlanCount(planCount,date);
                     for(k=0;k<=i;k++)
                        setPlanCount(planCount,1,date);
                     break;
                  }
                  printf(" > %s\n", (day+i)->title );
                  printf(" %s\n\n", (day+i)->content);
               }
            }
         break;
         case 'w' :
            i = getDayoftheWeekNum(date);
            y = getYear(date);
            m = getMonth(date);
            d = getDay(date) - i;

            if(d<1)
            {
               if(m==1)
               {
                  if(y==MIN_YEAR)
                  {
                     d+=7-i;
                     m=12;
                  }
                  else
                  {
                     y--;
                     m=12;
                  }
               }
               else
               {
                  m--;
               }
               d+=getMonthDay(m);
            }

            for(i=0;i<7;i++)
            {
               date = y * 10000 + m*100 + d;

               year = returnYear(data, date);
               month = returnMonth(year, date);
               day = returnDay(month, date);

               count = getPlanCount(planCount, date);

               if(count>10)
               {
                  planCount = resetPlanCount(planCount,date);
                  count = getPlanCount(planCount, date);
               }

               if(count==0)
               {
                  printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));
               }
               else
               {
                  printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));

                  for(j=0;j<count;j++)
                  {
                     printf(" > %s\n", (day+j)->title );
                     printf(" %s\n\n", (day+j)->content);
                  }
               }

               d++;

               if(d>getMonthDay(m))
               {
                  d=1;

                  if(m==MAX_MONTH)
                  {
                     y++;
                     m=MIN_MONTH;
                  }
                  else
                  {
                     m++;
                  }
               }
            }
         break;
         case 'm' :
            y = getYear(date);
            m = getMonth(date);
            d = 1;
            date = y*10000+m*100+d;

            j = getMonthDay(getMonth(date)) + ((isLeapYear(getYear(date))&&getMonth(date)==2)?1:0);

            for(i=0;i<j;i++)
            {
               count = getPlanCount(planCount, date);

               if(count>10)
               {
                  planCount = resetPlanCount(planCount,date);
                  count = getPlanCount(planCount, date);
               }

               //printf("\n\ncount = %d\n\n", count);

               if(count==0)
               {
                  printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));
               }
               else
               {
                  printf("\n[%4d-%2d-%2d %s]\n", getYear(date), getMonth(date), getDay(date), getDayoftheWeek(date));

                  for(l=0;l<count;l++)
                  {
                     printf(" > %s\n", (day+l)->title );
                     printf(" %s\n\n", (day+l)->content);
                  }
               }
               date++;
            }
            date = getYear(date)*10000+getMonth(date)*100+getMonthDay(getMonth(date));
         break;
      }

      switch(showMenu())
      {
         case '0':
            freeData(data);
            return;
         case '1':
            VIEW_TYPE = editViewType();
            printf("타입이 변경되었습니다.\n");
         break;
         case '2':
            date = inValidDate(1);
            year = returnYear(data, date);
            month = returnMonth(year, date);
            day = returnDay(month, date);
            day = addPlans(day, date, planCount);
            month[getDay(date)-1] = day;
            year[getMonth(date)-1] = month;
            data[getYear(date)-1] = year;
            setPlanCount(planCount, 1, date);
         break;
         case '3':
            date = inValidDate(2);
            year = returnYear(data, date);
            month = returnMonth(year, date);
            day = returnDay(month, date);
            count = getPlanCount(planCount, date);
            if(count==0)
            {
               printf("해당 날짜에는 등록된 일정이 없습니다.");
            }
            else if(count==1)
            {
               day[0] = deletePlan(day[0]);
               setPlanCount(planCount, 0, date);
            }
            else
            {
               int n;

               while(1)
               {
                  printf("삭제할 일정의 번호를 입력하세요.\n");

                  for(i=0;i<count;i++)
                  {
                     printf("[%d]\n", i+1);
                     printf(" > %s\n", (day+i)->title );
                     printf(" %s\n\n", (day+i)->content);
                  }

                  scanf("%d", &n);

                  if(n>0&&n<=count) break;
               }

               for(i=n-1;i<count-1;i++)
               {
                  day[i]=day[i+1];
               }

               day = realloc(day, sizeof(Plan)*(count-1));

               printf("일정이 삭제되었습니다.");
               setPlanCount(planCount, 0, date);
            }
            month[getDay(date)-1] = day;
            year[getMonth(date)-1] = month;
            data[getYear(date)-1] = year;
         break;
         case '4':
            date = inValidDate(2);
            year = returnYear(data, date);
            month = returnMonth(year, date);
            day = returnDay(month, date);
            count = getPlanCount(planCount, date);
            if(count==0)
            {
               printf("해당 날짜에는 등록된 일정이 없습니다.");
            }
            else if(count==1)
            {
               day[0] = editPlan(day[0]);
            }
            else
            {
               int n;

               while(1)
            {
               printf("수정할 일정의 번호를 입력하세요.\n");

               for(i=0;i<count;i++)
               {
                  printf("[%d]\n", i+1);
                  printf(" > %s\n", (day+i)->title );
                  printf(" %s\n\n", (day+i)->content);
               }

               scanf("%d", &n);

               if(n>0&&n<=count) break;
            }
            char c;
            scanf("%c", &c);
            day[n-1] = editPlan(day[n-1]);
         }
         month[getDay(date)-1] = day;
         year[getMonth(date)-1] = month;
         data[getYear(date)-1] = year;
         break;
         case '5':
            date = inValidDate(4);
         break;
         case '>':
            y = getYear(date);
            m = getMonth(date);
            d = getDay(date) + 1;
            if(d>getMonthDay(m)+(isLeapYear(y)&&m==2)?1:0)
            {
               d = 1;
               m++;

               if(m>MAX_MONTH)
               {
                  m = 1;
                  if(y==MAX_YEAR)
                  {
                     printf("%d년 이후로는 조회할 수 없습니다.", MAX_YEAR);
                  }
                  y++;
               }
            }
            date = y*10000 + m*100 + d;
         break;
         case '<':
            y = getYear(date);
            m = getMonth(date);
            d = getDay(date) - 1;
            if(d<1)
            {
               m--;
               if(m<1)
               {
                  if(y==MIN_YEAR)
                  {
                     printf("%d년 이전으로는 갈 수 없습니다.\n", MIN_YEAR);
                     continue;
                  }
                  y--;
                  m = 12;
               }
               d = getMonthDay(m);
            }
            date = y*10000+m*100+d;
         break;
      }

   }

}

// basic function
int isLeapYear(int year)
{
   if((year%4==0)&&(year%100!=0)||(year%400==0)) return 1;
   else return 0;
}
int getDay(int date)
{
   return date%100;
}
int getMonth(int date)
{
   return (date/100)%100;
}
int getYear(int date)
{
   // 20181125
   return date/10000;
}
int getMonthDay(int month)
{
   switch(month)
   {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
         return 31;
      case 4:
      case 6:
      case 9:
      case 11:
         return 30;
      case 2:
         return 28;
   }

   return 0;
}
int inValidDate(int type)
{
    int date, y, m, d;
    while(1)
    {
        switch(type)
        {
            case 0:
                printf("기준 날짜를 입력하세요. 입력예시 : 20181130\n > ");
            break;
            case 1:
                printf("일정을 추가할 날짜를 입력하세요. 입력예시 : 20181130\n > ");
            break;
            case 2:
                printf("일정을 삭제할 날짜를 입력하세요. 입력예시 : 20181130\n > ");
            break;
            case 3:
                printf("일정을 수정할 날짜를 입력하세요. 입력예시 : 20181130\n > ");
            break;
            case 4:
               printf("일정을 변경할 날짜를 입력하세요. 입력예시 : 20181130\n > ");
            break;
        }
        scanf("%d", &date);
        y = date/10000;
        if(y<MIN_YEAR||y>MAX_YEAR)
        {
            printf("잘못된 년도입니다. 다시 입력해주세요.\n");
            continue;
        }
        m=(date/100)%100;
        if(m<1||m>MAX_MONTH)
        {
            printf("잘못된 월입니다. 다시 입력해주세요.\n");
            continue;
        }
        d=date%100;
        if(d<1||d>getMonthDay(m)+(isLeapYear(y)&&m==2?1:0))
        {
            printf("잘못된 일입니다. 다시 입력해주세요.\n");
            continue;
        }
        char c;
        scanf("%c",&c);
        return date;
    }
}
int getDayoftheWeekNum(int date)
{
    int i;
    int year = getYear(date);
    int month = getMonth(date);
    int day = getDay(date);
    int d = year*365;

    d += year/4;

    for(i=1;i<month;i++)
    {
        if(isLeapYear(year)&&i<3)--d;
        d += getMonthDay(i);
    }

    d += day;

    d -= 2;

    return d%7;
}
char * getDayoftheWeek(int date)
{
    char dayoftheWeek[7][4] = { "SUN\0", "MON\0", "TUE\0", "WED\0", "THU\0", "FRI\0", "SAT\0" };

    char * tmp;

    return strcpy(tmp, dayoftheWeek[getDayoftheWeekNum(date)]);
}

char showMenu()
{
	char c;

	while(1)
	{
		printf("\n<이전\t\t\t|\t\t\t다음>\n");
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

// count
int getPlanCount(int *** planCount, int date)
{
   int ** planCount2 = planCount[getYear(date)-MIN_YEAR];
   int * planCount3 = planCount2[getMonth(date)-1];
   int planCount4 = planCount3[getDay(date)-1];

   return planCount4;
}
void setPlanCount(int *** planCount, int num, int date)
{
   int ** planCount2 = planCount[getYear(date)-MIN_YEAR];
   int * planCount3 = planCount2[getMonth(date)-1];

   if(num) planCount3[getDay(date)-1]++;
   else
   {
      if(planCount3[getDay(date)-1]==0) planCount3[getDay(date)-1] = 0;
      else planCount3[getDay(date)-1]--;
   }
}
int *** resetPlanCount(int *** planCount, int date)
{
   int ** planCount2 = planCount[getYear(date)-MIN_YEAR];
   int * planCount3 = planCount2[getMonth(date)-1];
   planCount3[getDay(date)-1] = 0;
   planCount2[getMonth(date)-1] = planCount3;
   planCount[getYear(date)-MIN_YEAR] = planCount2;

   return planCount;
}
int *** initPlanCountYear()
{
   int *** planCount = malloc(sizeof(int **)*(MAX_YEAR-MIN_YEAR+1));
   int i;

   for(i=MIN_YEAR;i<=MAX_YEAR;i++)
   {
      planCount[i-MIN_YEAR]=initPlanCountMonth(i);
   }
   return planCount;
}
int ** initPlanCountMonth(int year)
{
   int ** planCount = malloc(sizeof(int *)*(MAX_MONTH));
   int i;

   for(i=0;i<MAX_MONTH;i++)
   {
      planCount[i]=initPlanCountDay(i,year);
   }

   return planCount;
}
int * initPlanCountDay(int month, int year)
{
   int day = (getMonthDay(month)+(isLeapYear(year)&&month==2)?1:0);
   int * planCount = malloc(sizeof(int)*day);
   int i;

   for(i=0;i<day;i++)
      planCount[i]=0;

   return planCount;
}


// 0
void showPlan(Plan plan)
{
   printf("> %s\n%s\n\n", plan.title, plan.content);
}
Plan * addPlans(Plan * plans, int date, int *** planCount)
{
   int num = getPlanCount(planCount, date);

   if(num)
   {
      plans = realloc(plans, sizeof(Plan)*(++num));
   }
   else
   {
      plans = malloc(sizeof(Plan)*(++num));
   }

   plans[num-1] = addPlan();

   return plans;
}
Plan addPlan()
{
   Plan data;
   char tmp[250];
   while(1)
   {
      printf("타이틀 입력(최대100자)\n: ");

      gets(tmp);
      //scanf("%s", tmp);

      if(strlen(tmp))
      {
         data.title = malloc(sizeof(char)*strlen(tmp));
         strcpy(data.title, tmp);
         break;
      }

      printf("잘못 입력하셨습니다.\n");
   }

   while(1)
   {
      printf("내용 입력(최대100자)\n: ");

      gets(tmp);
      //scanf("%s", tmp);

      if(strlen(tmp))
      {
         data.content = malloc(sizeof(char)*strlen(tmp));
         strcpy(data.content, tmp);
         break;
      }

      printf("잘못 입력하셨습니다.\n");
   }

   return data;
}
Plan editPlan()
{
   Plan plan;

   char tmp[100];
   while(1)
   {
      printf("수정할 타이틀 입력\n: ");

      gets(tmp);
      //scanf("%s", tmp);

      if(strlen(tmp))
      {
         plan.title = malloc(sizeof(char)*strlen(tmp));
         strcpy(plan.title, tmp);
         break;
      }

      printf("잘못 입력하셨습니다.\n");
   }

   while(1)
   {
      printf("수정할 내용 입력\n: ");

      gets(tmp);
      //scanf("%s", tmp);

      if(strlen(tmp))
      {
         plan.content = malloc(sizeof(char)*strlen(tmp));
         strcpy(plan.content, tmp);
         break;
      }

      printf("잘못 입력하셨습니다.\n");
   }

   printf("일정이 다음과 같이 수정되었습니다.\n");
   showPlan(plan);

   return plan;
}
Plan deletePlan(Plan plan)
{
   free(plan.title);
   free(plan.content);
}



Plan * returnDay(Plan ** data, int date)
{
   return data[getDay(date)-1];
}
Plan ** returnMonth(Plan *** data, int date)
{
   return data[getMonth(date)-1];
}
Plan *** returnYear(Plan **** data, int date)
{
   return data[getYear(date)-MIN_YEAR];
}

// init
Plan * initDay()
{
   Plan * plan = malloc(sizeof(Plan)*1);

   return plan;
}
Plan ** initMonth(int year, int month)
{
   int day = (getMonthDay(month) + month==2&&isLeapYear(year)?1:0);
   Plan ** data = malloc(sizeof(Plan *)*day);
   int i;

   for(i=0;i<day;i++)
      data[i]=initDay();

   return data;
}
Plan *** initYear(int year)
{
   Plan *** data = malloc(sizeof(Plan **)*12);
   int i;

   for(i=0;i<12;i++)
      data[i]=initMonth(year, i+1);

   return data;
}
Plan **** initData()
{
   Plan **** data = malloc(sizeof(Plan ****)*(MAX_YEAR-MIN_YEAR));
   int i;

   for(i = MIN_YEAR; i <= MAX_YEAR; i++)
      data[i-MIN_YEAR] = initYear(i);

   return data;
}

// free
void freeDay(Plan * data)
{
   free(data);
}
void freeMonth(Plan ** data, int year, int month)
{
   int day = (getMonthDay(month) + month==2&&isLeapYear(year)?1:0);
   int i;

   for(i=0;i<day;i++)
      freeDay(data[i]);

   free(data);
}
void freeYear(Plan *** data, int year)
{
   int i;

   for(i=0;i<12;i++)
      freeMonth(data[i], year,i);

   free(data);
}
void freeData(Plan **** data)
{
   int i;

   for(i = MIN_YEAR; i <= MAX_YEAR; i++)
      freeYear(data[i-MIN_YEAR],i);

   free(data);
}
