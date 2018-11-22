# c_term_project

## c언어 수업 텀 프로젝트
<br>

### 조건

#### 1. 일정관리 프로그램 만들기
#### 2. 구조체 배열 사용
#### 3. 입력, 삭제, 수정 기능 적용
#### 4. 일간, 주간, 월간단위로 확인 가능하게 적용
#### 5. 윤달적용.
#### 6. 추가기능 구현 시 배운 범위내에서만 구현
#### 7. 수업시간에 금지한 것들 사용금지
##### ex) do-while / go-to / 전역변수 등
<br>

### 코드 설명1

* typedef struct PLAN
  {
      char * title;
      char * content;
  } Plan;
* 일정의 제목과 내용의 길이에 제한이 없도록 함
<br>

* typedef struct DAY
  {
      int year;
      int month;
      int day;
      Plan * plan;
      struct Day * tomorrow;
      struct Day * yesterday;
  } Day;
* 해당 날의 일정을 여러 개 추가할 수 있도록 함
* 주어진 날의 전날/다음날의 정보를 가지고 있도록 함
<br>

* int isLeapYear(int year)
    * 윤년 여부를 1 또는 0으로 반환하도록 함
<br>

* char * getDayoftheWeek(int year, int month, int day)
    * 년/월/일을 입력하면 요일(SUN/MON/TUE/WED/THU/FRI/SAT)을 반환하게끔 함
<br>

* Day * initTargetDay(int monthDat[]);
    * 프로그램 실행 초기에 1회 실행되어, 시작 날짜를 사용자에게 입력받은 후 반환함
<br>

* void displayDay(Day * targetDay);
    * 주어진 날의 정보를 모두 출력하는 함수
    * 출력 예시)
      <pre>2018-11-17 SAT
      >X2O 해커톤 참여
      스태프로 참여
      </pre>
<br>

* void displayPlan(Day * targetDay);
    * 주어진 날의 일정을 모두 출력하는 함수
    * 출력 예시)
      <pre>>X2O 해커톤 참여
      스태프로 참여

* Day * addDay(Day * day, int type, int monthDay[]);
    * 주어진 날의 전날 혹은 다음날의 정보를 추가하는 함수
    * type이 양수면 다음날, 그 외에는 전날의 정보를 추가함
<br>

* Plan * addPlanContext(Plan * plan);
    * 실제로 주어진 plan에 데이터를 추가하는 함수
<br>

* Day * addPlan(Day * day);
    * plan에 데이터를 추가할 공간을 만드는 함수
    * plan이 없다면 새로 만들고, 이미 plan이 있다면 있는 일정들 다음에 추가됨
<br>

* Day * editPlan(Day * day);
    * plan 데이터를 수정하는 함수
<br>

* Day * deletePlan(Day * day);
    * plan 데이터를 삭제하는 함수
<br>

### 핵심 개념
<br>

### 이슈

1. Segmentation fault (core dumped)
    * 리눅스에서 gcc를 돌리면 해당 오류 발생
    * 온라인 컴파일러에서는 발생하지 않음을 확인했음
<br>

### 체크리스트

* 메뉴 선택 함수 구현
    - 타입 변경
    - 일정 추가
    - 일정 삭제
    - 일정 수정
    - 다음/이전 일정으로 넘어가기
<br>
* 타입 변경 함수 구현
    - DAY/WEEK/MONTH VIEW 변경
    - onlyRegisteredSchedules 모드
      ( 일정이 등록된 날짜만 보여주기 )
<br>
* 뷰타입을 변경하는 함수
    - DAY VIEW
    - WEEK VIEW
        - 구조체 배열로 구현( 임시 구조체 7개 만들기)
    - MONTH VIEW
        - 구조체 배열로 구현( 임시 구조체 N(28<=N<=)개 만들기)
<br>
* onlyRegisteredSchedules 모드 구현
    - 이전/다음으로 넘기면 일정이 있는 날만 보여짐
    - 일정이 없으면 onlyRegisteredSchedules 해제됨
<br>
* 일정 추가 확실히 구현
<br>
* 뷰타입 추가
    - WEEK+ VIEW
    - MONTH+ VIEW
<br>
