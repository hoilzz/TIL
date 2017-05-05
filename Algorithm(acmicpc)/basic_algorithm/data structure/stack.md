# Stack
- FILO (First In Last Out)

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


## 참조
[스택을 구현하는 문제](https://www.acmicpc.net/problem/10828)

## 관련 문제
[괄호](https://www.acmicpc.net/problem/9012)
[쇠막대기](https://www.acmicpc.net/problem/10799)
[오아시스 재결합](https://www.acmicpc.net/problem/3015)
