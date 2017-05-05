# Data Structure

## 1. 적은양의 자료일 경우 사용할 컨테이너들

### Array

배열 자료구조

장점
- 적은양의 데이터에 유리

단점
- 크기 변경 불가

### vector

가변배열 자료구조

장점
- 적은양의 자료에 유리
- 크기 변경 가능
- 순차 접근 가능
- random access 가능

단점
- 중간에 삽입 및 삭제 할 때 최대 O(N) 소요. 왜냐하면 모든 원소를 한칸씩 이동 시켜야 하기 때문이다.
- 검색이 느리다
- 많은 양의 자료에 불리하다.


### LIST

더블 링크드 리스트(DLL)로 구현되어있다.

장점
- 중간에 삽입 삭제가 빠르다. O(1), 포인터의 이동만 요구하기 때문이다.
- 크기가 변경 가능하다
- 적은양의 자료에 유리하다
- 순차 접근 가능하다.

단점
- 검색 느리다
- 특정 원소에 접근하려면 선형 탐색 해야 한다. random access 지원 안한다.



### summary

- 중간 삽입 삭제가 없고 랜덤 접근이 많다 : vector
- 중간 삽입 삭제가 있고 랜덤 접근이 없다 : list
- 데이터 개수가 적은 경우 vector가 더 좋다.



## 많은 양의 데이터 + 검색 활발

- 검색 시에 유리하다
- 단점은 원소 값을 직접 수정할 수 없다.
- 삭제 후 삽입으로 원소 값을 수정한다.

### map

- 이진탐색트리 기반
- 균형이진트리
- key:value

장점
- 많은 양의 자료에 유리
- 검색 속도 빠름
- key:value 따로 저장
- 자동 정렬

단점
- 적은양엔 오버헤드로 인해 손해



### set

이진탐색트리 기반, 게임에서는 많이 안쓴다.

장점
- 많은 양의 자료에 유리
- 검색 속도 빠름
	- find() 알고리즘이 아닌 find() 멤버함수를 사용하자. 
- key: value
- 자동 정렬

단점
- 적은양엔 오버헤드로 인해 손해
- 양방향 반복자 이므로 랜덤 access 반복자를 요구하는 알고리즘 사용 불가. (예 : 정렬 알고리즘)