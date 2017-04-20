# list

리스트는 연결 리스트(Linked List)를 템플릿으로 구현한 것.

## 특징

- 길이가 가변적
- 중간에 데이터 삽입, 삭제가 용이
- 랜덤 접근은 용이하지 않다.


## 언제 사용할까

- 중간에 데이터 삽입 및 삭제가 자주 발생할 경우
- 순차적으로 저장된 데이터를 빈번하게 검색하지 않을 경우
- 특정 데이터가 저장된 위치를 파악하여 랜덤 접근 하지 않는 경우

## 다른 자료구조와 비교

- 순차접근은 list, vector 모두 유리하지 않다. map과 set이 유리하다
- `랜덤 접근`을 사용할 경우 list보다 vector를 사용하는게 유리
- 데이터 중간에 삽입, 삭제가 많을 경우 vector보다 list가 유리

*왜 그런지 궁금하면 다음 링크 참조하여 Linked List의 원리를 파악해보자*

[linked list를 구현하고 알아보자-](https://github.com/seaunseen/TIL/blob/master/Algorithm(acmicpc)/basic_algorithm/linked-list.md)

## list의 사용

*type*

> list<자료형> 변수명
> list<자료형>:iterator 변수명 : 반복자 형식
>           :reverse_iterator 변수명

*method*

> begin();
end();
push_front();
pop_front();
push_back();
pop_back();
begin();    // 첫 원소를 가리키는 반복자,
end()       // 끝을 표시하는 반복자, 근데 마지막 원소를 가리키는게 아닌 마지막 원소 다음 부분의 iterator를 반환(사이즈를 나타냄)
front();    // 첫번째 데이터 참조 반환
back();     // 마지막 데이터 참조 반환
clear();    // 모든 데이터 삭제
empty(iterator pos); // pos에 위치한 엘리먼트 제거
intert(위치, 데이터) //  지정된 위치에 삽입
erase(위치)
remove(값) // 해당 값을 가진 모든 원소 지운다.
sort()            // 기본값 : 오름차순
sort(greater<자료형>) // 내림차순


*begin/end 와 front/back의 차이점*

```C
vector<int> v1(5);
v1[0] = 1;
v1[1] = 2;
v1[2] = 3;
v1[3] = 4;
v1[4] = 5;

cout << "백터의 원소들? " << endl;
vector<int>::iterator itor;

for (itor = v1.begin(); itor != v1.end(); itor++) {
    cout << *itor << " "; cout << endl;
}

cout << "벡터의 첫번째 원소는 ? " << v1.front() << endl; cout << "벡터의 마지막 원소는 ? " << v1.back() << endl;
```

- begin,end는 `list<..>::iterator`와 비교될 수 있는 반복자 형식
    - 여기서 end는 마지막 원소가 아닌 마지막 다음 원소

- front와 back은 말 그대로 마지막 원소


*원형 리스트를 구현하여 2바퀴 반복하여 원소를 2번씩 출력해보자*
```C
list <int> LL;

for(int i=0; i<7; i++){
    LL.push_back(i*3);
    printf("i : %d\n", i);
}

list <int>::iterator LL_ptr;

LL_ptr = LL.begin();

for(int i = 0; i<14; i++){

    if(LL_ptr == LL.end()) {
        // 마지막 원소의 다음 원소는 사이즈를 나타낸다.
        // 그러므로 처음으로 초기화 후, continue
        LL_ptr = LL.begin();
        continue;
    }
    printf("%d ", *LL_ptr);
    ++LL_ptr;
}
```

list <int>::iterator LL_ptr은 value type의 양방향 반복자다.

양방향 반복자는 연속된 요소에 접근하는데 사용된다.

```C

X a;
X b(a);
b = a;

a == b
a != b

*a
a->m

역참조 가능하다.

*a = t

++a
a++

역참조 가능한 경우 증가 가능하다.

결과는 역참조 혹은 past-the-end 반복자가 될 수 있다.
```

X는 양방향 반복자 유형이다.

a와 b는 반복자 유형의 객체다. t는 반복자 유형이 가리키는 유형의 객체다.

**list든 vector든 자료구조 끝에 길이 저장??**
