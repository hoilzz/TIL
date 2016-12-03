# Queue
- FIFO (First In First Out)

## 기본 연산
- push
- pop
- front : 가장 앞의 자료 보기
- back : 가장 뒤의 자료 보기
- empty : 큐의 empty 유무
- size : 자료의 개수 보기

```C
int queueArr[10001];

int front = 0;
int back = -1;

void push(int data) {
    queueArr[++back] = data;
    //    if (front == -1) front += 1;
    // front를 0으로 해야 empty 했을 때
}

void pop() {
    if (front > back) printf("-1\n");
    else {
        printf("%d\n", queueArr[front]);
        front += 1;
    }
}

void size() {
    printf("%d\n", back - front + 1);
}

void empty() {
    if (front > back) printf("1\n");
    else printf("0\n");
}

void PrintFront() {
    if (front > back) printf("-1\n");
    else printf("%d\n", queueArr[front]);
}

void PrintBack() {
    if (front > back) printf("-1\n");
    else printf("%d\n", queueArr[back]);
}
```

## 회고

### empty
```C
   // 초기화 코드 back = 0, front = 0

   // front를 0으로 초기화하여
   // 아래와 같이 처음 숫자 추가시, 예외코드 삽입
   if (front == -1) front += 1;

   void empty() {
       if (front > back) printf("1\n");
       else printf("0\n");
   }

```
- 큐는 `pop`으로 인해 `front`가 `back`보다 커질 때 비어있다.

- front를 생각없이 0으로 초기화.
  - 첫 데이터 삽입 전에 `empty()` **호출시 비어있지 않다고 출력**

- 즉, 큐는 초기화시 비어있으므로
   - `front = 0`, `back = -1`
- `back`  : 가리키는 `index`에 data 있음, every `push()`마다 증가
- `front` : 가리키는 `index-1` 까지 제거, every `pop()` 마다 증가,


## 참고
[큐](https://www.acmicpc.net/problem/10845)
