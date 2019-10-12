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
- pop : 스택에서 자료 빼기
- top : 스택의 가장 위에 있는 자료를 보기
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

## 관련 문제

1. [괄호의 값](https://www.acmicpc.net/problem/2504)

스택 이용 안해도됨. '(`의 개수만 카운트해주면됨.

valid=true를 디폴트로 두고, false인 케이스만 찾아서 대응

false인 케이스

1. 마지막 괄호문자열 검사하기 전에 `)`를 만났을 때 stack이 비었을 경우
2. 모든 괄호문자열 검사 후, stack size가 1이상일 경우

- DFS할 때 사용

2. 스택 2개로 큐 만들기

```C
stack <int> inbox;
stack <int> outBox;

void enqueue(int num) {

    inbox.push(num);
    cout<<"[enqueue] "<<num<<endl;
}

void dequeue() {
    if(outBox.empty()) {
        // 비어있으면
        // 새로 채워주기
        while(!inbox.empty()) {
            outBox.push(inbox.top());
            inbox.pop();
        }
    }
    cout<<"[dequeue] "<<outBox.top()<<endl;

    outBox.pop();
}


int main(int argc, const char * argv[]) {

    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);

    dequeue();
    dequeue();
    dequeue();

    return 0;
}

```

Inbox, outBox로 2개 관리

pop할 때, InBox 아이템들을 전부 pop하여 outBox에 push.
이렇게 할 경우 InBox를 뒤집어서 outBox에 들이 붓는 형태를 생각하자.
그럼 FI(first In) 했던 아이템이 OutBox에서ㅡ FO(First out) 할 수 있는 형태가 된다.

## 참조

[스택을 구현하는 문제](https://www.acmicpc.net/problem/10828)

## 관련 문제

[스택과 관련된 문제](https://www.acmicpc.net/problem/tag/%EC%8A%A4%ED%83%9D)
