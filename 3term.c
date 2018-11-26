#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char * title;
	char * content;
} Plan;

// basic function
int isLeapYear(int year);
int getDayoftheWeekNum(int year, int month, int day);
char * getDayoftheWeek(int year, int month, int day);

// show data
void showPlan(Plan * plan);
void showDay(int year, int month, int day, Plan * plan);
char showMenu();

// set base date
int setBaseYear();
int setBaseMonth();
int setBaseDay(int isLeap, int monthDay);

// init data
Plan ** initMonth(int i);
Plan *** initYear();
Plan **** initData(int MAX_YEAR);
Plan **** exPandData(int MAX_YEAR);

// delete data
void deleteDay(Plan * data);
void deleteMonth(Plan ** data, int month, int isLeap);
void deleteYear(Plan *** data, int isLeap);
void deleteData(Plan **** data, int maxYear);

int main(void)
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int BASE_YEAR = setBaseYear();
	int BASE_MONTH = setBaseMonth();
	int BASE_DAY = setBaseDay(isLeapYear(BASE_YEAR), monthDay[BASE_MONTH-1]);
	int MAX_YEAR = BASE_YEAR;

	int VIEW_TYPE = 'D';
	int VIEW_ONLY_SCHEDULED_DAYS = 0;

	Plan **** data = initData(MAX_YEAR);


	while(1)
	{
		showDay( BASE_YEAR, BASE_MONTH, BASE_DAY, data[BASE_YEAR-1][BASE_MONTH-1][BASE_DAY-1] );

		switch(showMenu())
			{
				case '0' :
					return;
				case '1' :
				break;
				case '2' :
				break;
				case '3' :
				break;
				case '4' :
				break;
				case '5' :
				break;
				case '<' :
				break;
				case '>' :
				break;
			}
	}
}

// basic function
int isLeapYear(int year)
{
	if( (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) ) return 1;
	else return 0;
}
int getDayoftheWeekNum(int year, int month, int day)
{
	int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int i;

	int date = year*365;

	date += year/4;

	for( i = 1; i < month; i++ )
	{
		if( isLeapYear(year) && i < 3 ) --date;

		date += monthDay[i-1];
	}

	date += day;

	date -= 2;

	printf("\n\nday : %d\n\n", date%7);

	return date % 7;
}
char * getDayoftheWeek(int year, int month, int day)
{
	char dayoftheWeek[7][4] = { "SUN\0", "MON\0", "TUE\0", "WED\0", "THU\0", "FRI\0", "SAT\0" };

	char * tmp;

	strcpy( tmp, dayoftheWeek[getDayoftheWeekNum(year,month,day)]);

	return tmp;
}

// show data
void showPlan(Plan * plan)
{
}
void showDay(int year, int month, int day, Plan * plan)
{
	printf("[ %4d-%2d-%2d %s ]\n", year, month, day, getDayoftheWeek(year,month,day) );
	if(day)
	{

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

// set data
int setBaseYear()
{
	int base;

	while(1)
	{
		printf("기준 년도를 입력하세요.\n> ");
		scanf("%d", &base);

		if(base>0)
			return base;

		printf("올바른 년도를 입력하세요. 기원 전은 취급하지 않습니다.\n");		
	}
}
int setBaseMonth()
{
	int base;

	while(1)
	{
		printf("기준 월를 입력하세요.\n> ");
		scanf("%d", &base);

		if(base>0 && base<13)
			return base;

		printf("올바른 월을 입력하세요. 범위는 1 이상 12 이하입니다.\n");
	}
}
int setBaseDay(int isLeap, int monthDay)
{
	int base;

	while(1)
	{
		printf("기준 일을 입력하세요.\n> ");
		scanf("%d", &base);

		if( monthDay == 28 && isLeap )monthDay++;

		if(base>0 && base<=monthDay)
			return base;

		printf("올바른 월을 입력하세요. 범위는 1 이상 %d 이하입니다.\n", monthDay);		
	}
}

// init data
Plan ** initMonth(int i)
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	Plan ** month = malloc(sizeof(Plan *) * monthDay[i-1]);

	return month;
}
Plan *** initYear()
{
	Plan *** year = malloc(sizeof(Plan **) * 12);
	int i;

	for(i = 0; i < 12; i++)
		year[i] = initMonth(i);

	return year;
}
Plan **** initData(int MAX_YEAR)
{
	Plan **** data = malloc(sizeof(Plan ***) * MAX_YEAR);

	int i;

	for(i = 0; i < MAX_YEAR; i++)
		data[i] = initYear();

	return data;
}

// delete data
void deleteDay(Plan * data)
{
	if(data)
	{
		free(data);
	}
}
void deleteMonth(Plan ** data, int month, int isLeap)
{
   int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   int i;

	for( i = 0; i < monthDay[month-1] + month==2&&isLeap?1:0; i++ )
		deleteDay(data[i]);

	free(data);
}
void deleteYear(Plan *** data, int isLeap)
{
	int i;

	for( i = 0; i < 12; i++ )
		deleteMonth(data[i], i, isLeap);

	free(data);
}
void deleteData(Plan **** data, int maxYear)
{
	int i;

	for( i = 0; i < maxYear; i++ )
		deleteYear(data[i], isLeapYear(i));

	free(data);
}