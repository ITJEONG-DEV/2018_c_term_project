# c_term_project

## c언어 수업 텀 프로젝트
<br>

<br>

## 기술 스택

| C |
| :--------: |
|   <img src="https://raw.githubusercontent.com/ITJEONG-DEV/README/46a37ee1c7ef889704bffa1b71ebdfe6b4400ee4/.images/c.svg" width="180" height="180"/>   |


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
* onlyScheduledDays 모드 구현
    - 이전/다음으로 넘기면 일정이 있는 날만 보여짐
    - 일정이 없으면 onlyScheduledDays 해제됨
<br>
* 일정 추가 확실히 구현
<br>
* 뷰타입 추가
    - WEEK+ VIEW
    - MONTH+ VIEW
<br>

## 라이센스

MIT &copy; [ITJEONG](mailto:derbana1027@gmail.com)
