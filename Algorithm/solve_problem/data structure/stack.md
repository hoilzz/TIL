# Stack

- LIFO(Last In First Out) 자료구조
- 리스트를 사용하여 구현
  - 보통 유일하게 알 수 있는 값은 맨 위에 있는 값이다

스택은 맨 위에서 삽입 삭제 연산이 이루어지므로 **연결 리스트**로 구현해야 한다. 
연결리스트로 구현해야 push, pop, top 연산이 모두 `O(1)`이다.

연결 리스트로 구현할 경우 

- head 포인터가 top원소를 가리킨다.
- push : 새로운 노드를 만들어, 그것에 head를 가리키게 한다.
- pop : head 노드 삭제, 그 다음 노드에 head를 가리키게 한다.

C++의 경우 `<stack>` 헤더 파일을 이용할 수 있다.

간단히 구현할 경우 배열 혹은 `<vector>`를 이용할 수 있다

## 기본 연산

- push : 스택에 자료 넣기
- pop  : 스택에서 자료 빼기
- top  : 스택의 가장 위에 있는 자료를 보기
- empty : 스택이 empty 여부 확인
- size : 스택에 저장된 자료의 개수 알아보기


```C
int stackArr[10001];
int topIdx = -1;

void push(int data) {
    stackArr[++topIdx] = data;
}

void pop() {
    if ( topIdx < 0 ) printf("-1\n");
    else {
        printf("%d\n", stackArr[topIdx]);
        topIdx--;
    }
}

void top() {
    if( topIdx < 0)    printf("-1\n");
    else printf("%d\n", stackArr[topIdx]);
}

void empty() {
    if (topIdx < 0) printf("1\n");
    else printf("0\n");
}

void size() {
    printf("%d\n", topIdx+1);
}
```

- `empty` 확인은 `topIdx < 0` 으로 확인
  - `topIdx == 0` 보다 더 확실하다.

## 언제 사용할까?

[괄호의 값](https://www.acmicpc.net/problem/2504)을 스택을 이용하여 풀어보자.

1. 열린 괄호가 나올 때 마다 스택에 push
2. 닫는 괄호가 나올 때 마다 스택의 top과 종류가 맞는지 비교
  - 종류가 맞다면 스택의 top과 종류가 같은 괄호열인지 비교한다. 맞으면 pop
  - 종류가 맞지 않거나, 스택이 비어있으면 틀린 괄호 문자열로 판단
3. 문자열의 마지막 문자까지 비교하여 스택이 비어있다면 옳은 문자열로 판단

- DFS할 때 사용

## 참조
[스택을 구현하는 문제](https://www.acmicpc.net/problem/10828)

## 관련 문제

[스택과 관련된 문제](https://www.acmicpc.net/problem/tag/%EC%8A%A4%ED%83%9D)