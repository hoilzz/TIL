## INDEX

인덱스는 *특정 칼럼 값* 을 가지고 있는 열을 빠르게 찾기 위해 사용된다.

####기존에 MYSQL이 찾는 방법

1 FTS(Full Table Scan)
- 테이블의 처음 부터 끝까지 검색
- 이로 인해 테이블이 클수록 비용이 엄청 증가

2 Index Scan
- 인덱스를 검색하여 해당 자료의 테이블을 access
- 만약 테이블이 쿼리에 있는 컬럼에 대한 index 가지고 있다면, 모든 데이터 조사하지 않고 데이터 파일의 중간에서 검색위치를 빠르게 잡아낸다
- 대부분의 MySQL 인덱스는 B-트리에 저장된다.


#### Index의 종류
: 칼럼의 수와 칼럼의 종류에 의한 인덱스의 구성

1 Single Column Index
: 1개의 칼럼으로 생성된 인덱스

2 Composite Index
: 2개 이상의 칼럼으로 생성된 Index (최대 32개까지 조합 가능, 10개 이하가 일반적)

3 Unique Index
: 모든 Unique 및 기본 키 제약조건 생성시 자동으로 생성

4 Non-Unique Index
: 중복된 컬럼을 가질 수 있는 Index

5 Function-based Index
: 인덱스에 포함된 1개 이상의 컬럼이 함수 또는 수식을 사용하여 생성된 경우 인덱스 저장 전에 값이 계산된다.


#### Index 왜 사용할까

- where 구문과 일치하는 열 빨리 찾기
- 특정 열을 고려 대상에서 빨리 없애기
- join 실행시 다른 테이블에서 열을 추출하기 위해서
- 특정하게 인덱스된 컬럼을 위한 MIN() or MAX()값 찾기
- 사용할 수 있는 key의 leftmost prefix를 가지고 정렬 및 그룹화 하기 위해서
- 데이터 열을 참조하지 않는 상태로 값을 추출하기 위해 쿼리를 최적화.

#### 언제 사용할까

- 데이터 양이 많고 검색이 변경보다 많을 때
- 인덱스를 걸고자 하는 필드의 값이 다양한 값을 가지는 경우

#### Index 설계 시 유의사항

1 인덱스 개수를 최소화 한다

- 현재 인덱스로 Range Scan이 가능한지 여부를 사전에 체크
- 인덱스도 서버 자원 소모하는 자료구조 이므로 성능에 영향을 줌

2 인덱스 칼럼은 분포도를 고려하여 선정

- 인덱스 칼럼 데이터의 중복이 줄어들수록 인덱스는 최대의 효과를 가짐
- 하단 쿼리 결과 값이 1에 가까울수록 (0.9이상 권고) 인덱스 컬럼으로 적합

>SELECT count(distinctINDEX_COLUMN)/count( * ) FROM TABLE


#### index in rails

- 자동 생성된 id column에 자동으로 index 추가


#### 해보자

1 timetable에서 time_item은 매번 검색해야한다.
2 time_items 에서 timetable_id에 index 추가

+ timetable semester default 값 제거
+ timetable validates semester validates


























## Refer
DB 클러스터
  : 기본적인 DB 구축은 1개의 서버로 하나의 DB를 구축해서 운용하는 형태다.
  이외에 하나의 DB를 여러개의 서버가 나눠서 처리하도록 하는 형태가 늘어나고 있다.
  DB 클러스터라 함은 하나의 DB를 복수개의 서버상(가상서버)에 구축되는 경우를 말한다.

B 트리
  : 방대한 양의 저장된 자료를 검색해야 하는 경우 검색어와 자료를 일일이 비교하는 방식은 비효율적이다. B-트리는 자료를 정렬된 상태로 보관하고, 삽입 및 삭제를 대수 시간으로 할 수 있다. 대부분의 이진 트리는 항목이 삽입될 때 하향식으로 구성되는 데 반해, B-트리는 일반적으로 상향식으로 구성된다.