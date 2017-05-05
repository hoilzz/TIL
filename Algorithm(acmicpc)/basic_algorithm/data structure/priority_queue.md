# 우선순위 큐

큐나 스택과 비슷한 자료형이다.

하지만, 각 원소들은 `우선순위`를 가지고 있다.

기본적으로 우선순위가 높을 수록 원소를 먼저 처리한다.

## Syntax

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


## Heap으로 구현

우선순위 큐의 구현은 보통 힙으로 한다. 힙은 완전 이진 트리에 있는 노드 중에서 키 값이 가장 큰거나 혹은 작은 노드를 찾기 위한 자료구조다.

1. 최대 힙

- 키 값이 가장 큰 노드를 찾기 위한 완전 이진 트리
- 루트 노드 : 키 값이 가장 큰 노드
- 부모 노드의 키 값 >= 자식 노드 키 값

2. 최소 힙

- 키 값이 가장 작은 노드를 찾기 위한 완전 이진 트리


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
