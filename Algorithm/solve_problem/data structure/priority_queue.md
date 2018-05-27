# 우선순위 큐

큐나 스택과 비슷한 자료형이다.

하지만, 각 원소들은 `우선순위`를 가지고 있다.

기본적으로 우선순위가 높을 수록 원소를 먼저 처리한다.


## Heap으로 구현

우선순위 큐의 구현은 보통 `Heap`으로 한다. 
힙은 완전 이진 트리에 있는 노드 중에서 키 값이 가장 큰거나 혹은 작은 노드를 찾기 위한 자료구조다.
결론적으로 힙은 이진트리다. 완전이진트리다.
**최대 / 최소 값을 빠른 시간 내에 찾기 위해** 고안된 `완전 이진 트리`다.

> 완전이진트리
leaf노드 레벨응ㄹ 제외하고 모든 노드가 채워진 이진 트리(마지막 레벨을 제외하고 모든 노드가 자식 노드를 2개 가진다). 마지막 레벨의 노드들은 왼쪽으로 채워져있다.

> HeapSort
어떤 원소들을 다 넣고 전체 길이만큼 pop을 하면 정렬된 순서로 원소들이 나온다. 

1. 최대 힙

- 키 값이 가장 큰 노드를 찾기 위한 완전 이진 트리
- 루트 노드 : 키 값이 가장 큰 노드
- 부모 노드의 키 값 >= 자식 노드 키 값

2. 최소 힙

- 키 값이 가장 작은 노드를 찾기 위한 완전 이진 트리

최대힙을 통해 자세히 이해해보자.
모든 정점에 대해 성립하는 제일 중요한 성질을 알아보자. 
**모든 정점은 자신의 자식들보다 우선순위가 높다.**
최대 힙의 경우 A < B 일 때 B의 우선순위가 A보다 높다. 이 기준은 부모-자식 관계에서 성립해야 한다. 

여기서 top이나 pop을 하면 나올 원소는? `Root`다.
루트는 힙의 정점에 있기 때문에 다른 노드들보다 우선순위가 높거나 같다. 따라서 (최대힙에서) 최대값이다. **또한, Binary Search Tree와 동일하게 push나 pop 연산을 할 때마다 (최대)힙의 형태를 유지해야 하므로 변형이 일어난다.**

### push

그림

10을 푸쉬 해보자. 일단 완전 이진 트리 형태를 유지하기 위해 마지막 레벨의 가장 왼쪽의 빈자리에 새로 자리를 잡는다. 이제 10은 부모와 비교하며 자리를 찾아간다.

그림

부모인 3보다 크니까 자리를 바꾼다.

그림

부모인 6보다 크니까 자리 바꾼다. 루트 보다는 작기 때문에 연산을 멈춘다.

힙은 완전 이진 트리 형태이기 때문에 균형 트리다. 따라서 원소 개수가 N개면 자리 바꾸기도 최대 `O(logN)`번 수행된다.

힙을 직접 구현하기 위해 `배열`을 사용할 수 있다. 여기서 루트 인덱스가 0이 아닌 1을 가지면 계산하기 조금 편해진다. 어떤 정점 i의 부모 인덱스는 i/2이고, `왼쪽 자식 : i*2`, `오른쪽 자식 : i*2 +1`이 된다.


### pop

pop을 해보자

그림

큐(FIFO) 특성상 가장 위에 있는 루트가 사라진다. 또, 완전 이진 트리를 유지하기 위해 가장 마지막 레벨의 가장 오른쪽에 있는 원소를 루트로 옮긴다.

그림

자식들 중 가장 큰 얘와 자리를 바꾼다.(아무나 바꾸면 또 루트와 자식간 비교를 해야한다다

그림
또 자리를 바꾼다. 

그림

또 자리를 바꿔서 leaf노드까지 왔다.

## 예제

[최대 힙](https://www.acmicpc.net/problem/11279) 문제를 풀어보자.

```C
#include <iostream>
#include <stdio.h>
using namespace std;

int tree[100001];
int rear = 1;

void push(int x){
  // x 가장 말단에 넣기
  int newValue = x;
  int tempRear = rear;
  tree[rear++] = newValue;

  while(newValue > tree[tempRear/2] && tempRear > 1){
    swap(tree[tempRear], tree[tempRear/2]);
    tempRear = tempRear/2;
  }
}

int pop() {
  if (rear <= 1) {
    return 0;
  }
  int rootValue = tree[1];

  int lastValue = tree[--rear];
  tree[rear] = 0;
  tree[1] = lastValue;

  for (int i = 1; i * 2 <= rear;) {
    if (tree[i] >= tree[i * 2] && tree[i] >= tree[i * 2 + 1]) {
      break;
    }
    if (tree[i * 2] > tree[i * 2 + 1]) {
      swap(tree[i], tree[i * 2]);
      i *= 2;
    } else {
      swap(tree[i], tree[i * 2 + 1]);
      i = i * 2 + 1;
    }
  }
  return rootValue;
}

int main() {

  int commandLen, value;
  cin>>commandLen;

  for(int i = 0; i<commandLen; i++){
    cin>>value;
    if(value==0){
      printf("%d\n", pop());
    }
    else{
      push(value);
    }
  }

  return 0;
}
```


## Syntax

C++의 `<queue>`에서 제공하는 priority_queue를 사용해서 풀 수도 있다.

```C
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```

개발자가 제공한 비교 기능을 사용하여 우선순위를 변경할 수 있다. 예를 들어, `std::greater<T>`를 사용하면 가장 작은 요소가 top()에 위치한다.

`priority_queue`로 작업하는 것은 임의의 액세스 컨테이너에서 힙을 관리하는 것과 비슷하다.

class T
: 저장될 엘리먼트의 타입이다.

class Container = std::vector<T>
: 엘리먼트를 저장하기 위해 사용할 컨테이너의 타입. 컨테이너는 SequenceContainer의 요구사항을 만족해야한다. 그리고 그것의 iterator는 `RandomAccessIterator`를 만족해야한다. 게다가 다음 함수를 제공해야한다.

`front()`, `push_back()`, `pop_back()`

표준 컨테이너인 `std::vector` 와 `std::deque`가 이러한 요구사항을 만족한다.

Compare
: strict weak ordering을 제공하는 Compare type이다.

오름차순 `greater<T>`, 내림차순 `less<T>`을 이용하여 굳이 사용자 정의를 하지 않아도 된다.

## Example

`priority_queue`를 직접 활용한 예제를 보며 마무리하자.

```C
#include <queue>

class CompareDist{
public:
    bool operator()(pair <int, int>n1, pair <int, int>n2){
        return n1.first>n2.first;
    }
};

int main() {

    // 내림차순이 우선순위 큐의 default comp
    priority_queue <int> pq;

    priority_queue <int, vector<int>, greater<int>> pq1;

    priority_queue <pair<int,int>, vector<pair<int,int>>, CompareDist> pq2;

    pq.push(5);
    pq.push(3);
    pq.push(8);
    pq.push(2);

    for(int i = 0; !pq.empty(); i++) {
        printf("%d ", pq.top());
        pq.pop();

    }

    printf("\n");

    pq1.push(5);
    pq1.push(3);
    pq1.push(1);
    pq1.push(8);
    pq1.push(2);

    for(int i = 0; !pq1.empty(); i++) {
        printf("%d ", pq1.top());
        pq1.pop();
    }

    printf("\n");

    pq2.push(make_pair(5,1));
    pq2.push(make_pair(2,3));
    pq2.push(make_pair(6,2));
    pq2.push(make_pair(11,7));
    pq2.push(make_pair(12,9));

    for(int i = 0; !pq2.empty(); i++) {
        printf("%d, %d\n", pq2.top().first, pq2.top().second);
        pq2.pop();
    }

    return 0;
}
```

#### 사용자 정의 비교함수

```C
public:
    bool operator()(pair <int, int>n1, pair <int, int>n2){
        return n1.first>n2.first;
    }
};
```
최소 힙과 같이 가장 작은 원소를 루트로 올리려고 한다.

부모와 자신의 값을 비교하여 부모가 더 크면(**비교 연산자에 부모와 자신을 넣고 비교했을 때 true가 리턴되면**) 자식을 위로 올린다.
