# Queue

- FIFO (First In First Out)
- 스택은 삽입,삭제가 같은 곳에서 이뤄진다. 하지만, 큐는 서로 다른쪽에서 이뤄진다.
- 값이 들어오는 입구인 rear, 값이 나갈 출구인 front가 존재.

## 언제 사용?

BFS할 때 사용.

## 기본 연산
- push
- pop
- front : 가장 앞의 자료 보기
- back : 가장 뒤의 자료 보기
- empty : 큐의 empty 유무
- size : 자료의 개수 보기

```C
int queueArr[10001];

int front = 0; // pop()에서 사용. front 앞 까지 제거완료
int rear = -1; // push()에서 사용. 증가 시키고 rear

void push(int data) {
    queueArr[++rear] = data;
    //    if (front == -1) front += 1;
    // front를 0으로 해야 empty 했을 때
}

void pop() {
    if (front > rear) printf("-1\n");
    else {
        printf("%d\n", queueArr[front]);
        front += 1;
    }
}

void size() {
    printf("%d\n", rear - front + 1);
}

void empty() {
    if (front > rear) printf("1\n");
    else printf("0\n");
}

void PrintFront() {
    if (front > rear) printf("-1\n");
    else printf("%d\n", queueArr[front]);
}

void PrintBack() {
    if (front > rear) printf("-1\n");
    else printf("%d\n", queueArr[rear]);
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
