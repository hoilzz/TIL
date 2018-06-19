# 우선순위 큐

큐나 스택과 비슷한 자료형이다. 하지만, 각 원소들은 `우선순위`를 가지고 있다. 기본적으로 우선순위가 높을 수록 원소를 먼저 처리한다.


## Heap으로 구현

우선순위 큐의 구현은 보통 `Heap`으로 한다. 힙은 완전 이진 트리에 있는 노드 중에서 키 값이 가장 큰거나 혹은 작은 노드를 찾기 위한 자료구조다. 결론적으로 힙은 이진트리다. 완전이진트리다. **최대 / 최소 값을 빠른 시간 내에 찾기 위해** 고안된 `완전 이진 트리`다.

힙은 다음 특징을 유지해야한다.

- max or min order : 각 노드의 값은 자신의 자식노드가 가진 값보다 크거나 같다 / 작거나 같다. (각각 최대힙과 최소힙)
- complete binary tree: 완전 이진트리 모양을 유지해야 한다.

> 완전이진트리
leaf노드 레벨을 제외하고 모든 노드가 채워진 이진 트리(마지막 레벨을 제외하고 모든 노드가 자식 노드를 2개 가진다). 마지막 레벨의 노드들은 왼쪽으로 채워져있다.

> HeapSort
어떤 원소들을 다 넣고 전체 길이만큼 pop을 하면 정렬된 순서로 원소들이 나온다. 

[!img](https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/Max-Heap.svg/1200px-Max-Heap.svg.png)

최대힙을 통해 자세히 이해해보자. 모든 정점에 대해 성립하는 제일 중요한 성질을 알아보자. **모든 정점은 자신의 자식들보다 우선순위가 높다.** 최대 힙의 경우 A < B 일 때 B의 우선순위가 A보다 높다. 이 기준은 부모-자식 관계에서 성립해야 한다. 

여기서 pop을 하면 나올 원소는? `Root`다. 루트는 힙의 정점에 있기 때문에 다른 노드들보다 우선순위가 높거나 같다. 따라서 (최대힙에서) 최대값이다. **또한, Binary Search Tree와 동일하게 push나 pop 연산을 할 때마다 (최대)힙의 형태를 유지해야 하므로 변형이 일어난다.**

> Heap VS Binary Search Tree
> 힙과 이진탐색트리 모두 이진트리라는 점에서 공통점을 갖는다. 하지만 노드의 위치를 결정할 때 다른 기준을 사용한다. 힙은 각 노드의 값이 자식 노드보다 크다. 이진탐색트리는 왼쪽 자식 노드가 제일 작고 부모노드가 그 다음으로 크고 오른쪽 자식노드가 가장 큰 값을 가진다. **힙은 우선순위 정렬에, 이진 탐색트리는 탐색에 강점을 가진다**

### Heap은 배열로 표현 가능

완전이진트리 성질을 만족하기 때문에 1차원 배열로 표현이 가능하다. 한 노드는 최대 2개의 자식노드를 갖는데, 왼쪽 자식은 `2 * index + 1`, 오른쪽 자식은 `2 * index + 2`다.

### heapify

힙 성질을 만족하도록 하는 연산을 heapify라고 한다. 최대힙 예제를 보자.

[!img](http://users.cecs.anu.edu.au/~Alistair.Rendell/Teaching/apac_comp3600/module2/images/Heaps_Heapify.png)

5에 대해서 heapify를 진행한다고 하자

```C
void heapifyDown(int unsortedIdx) {
  if(rear == 0) {
    return;
  }
  
  int leftChild = unsortedIdx * 2 + 1;
  int rightChild = leftChild + 1;
  
  if(bTree[leftChild] > bTree[rightChild]) {
    if(leftChild <= rear && bTree[leftChild] > bTree[unsortedIdx]) {
      swap(bTree[leftChild], bTree[unsortedIdx]);
      heapifyDown(leftChild);
      return;
    }
  }
  if(rightChild <= rear && bTree[rightChild] > bTree[unsortedIdx]) {
    swap(bTree[rightChild], bTree[unsortedIdx]);
    heapifyDown(rightChild);
    return;
  }
}
```

먼저 5의 위치에서 왼쪽/오른쪽 자식노드와의 heapify를 진행한다. 14와 11중 더 큰 숫자가 우선순위를 높게 가져야 하므로 둘을 먼저 비교한다. 더 큰 숫자인 14와 5에 대해 swap 후, 바뀐 위치에서 다시 heapify를 시작한다. 5는 12와 swap을 하고 다시 heapify를 시작한다. 더이상 자식노드가 없으므로 heapify를 종료한다.

heapify는 루트에서 leaf까지 비교해야 하므로 트리의 높이 (h = logN)에 비례한다. 값 비교 및 swap 연산은 O(1)이므로 heapify는 O(logN)이다. 

### push

[!img](http://www.techiedelight.com/wp-content/uploads/2016/11/Push-min-heap.png)

2를 추가한다. 완전이진트리를 유지하기 위해 마지막 노드에 추가한다. 2에 대해 heapify를 시작한다. heapify코드는 다음과 같다. heapify는 최악의 경우 루트까지 비교해야 하므로 트리의 높이에 비례한다. O(h = logN). 값을 비교하거나 바꾸는 연산은 O(1)이므로 heapify는 O(logN)이다.

```C
void heapifyUp(int unsortedIdx) {
  int parentIdx;
  if(rear == 0 || unsortedIdx <= 0) {
    return;
  }
  if(unsortedIdx % 2 == 1) {
    parentIdx = unsortedIdx / 2;
  } else {
    parentIdx = unsortedIdx / 2 - 1;
  }
  
  if(bTree[parentIdx] < bTree[unsortedIdx]) {
    swap(bTree[parentIdx], bTree[unsortedIdx]);
    heapifyUp(parentIdx);
  }
}
```


### pop

pop을 해보자

[!img](https://i2.wp.com/www.techiedelight.com/wp-content/uploads/2016/11/Pop-min-heap.png?fit=1006%2C798)

최소힙에서 루트노드가 pop 되는 예제입니다. 완전이진트리를 유지하기 위해, 루트와 리프노드의 가장 마지막 노드와 swap합니다. 루트노드의 값이 최소힙의 성질을 만족하기 위해 heapify를 진행합니다. 위의 heapifyDown과 동일합니다.

## build heap

임의의 숫자들을 최대힙으로 재구성해봅시다. 

```
[12, 30, 6, 7, 4, 13, 8, 11, 50, 24, 2, 5, 10]
```

위 배열을 가지고 build heap하는 단순한 방법은 비어있는 배열에 대해 push를 하며 heapifyUp하면 됩니다. N개의 노드에 대해 heapifyUp을 진행한다면 O(NlogN)이 소요됩니다. 

## Heap Sort

힙정렬을 수행하기 위해 주어진 데이터를 가지고 최대힙을 구성해야 한다.


## Summary

Heap
- 최대힙과, 최소힙이 있다.
  - 각 노드가 자식보다 크거나 같은 값으로 이뤄진 트리 구조를 가진다.
  - 그래서 Root Node만 빼오면 최대/최소값을 찾을 수 있는데 O(1)이라는 짧은 시간을 가진다.
  - 왜냐면 완전이진트리로 되어있는데, 완전이진트리는 배열로 만들 수 있고 Root Node를 Random Access Memory로 접근 가능하기 떄문이다.
    - 노드가 n개 일 때, k번쨰 노드의 부모의 index는 `k/2`, 왼쪽 자식 index는 `(2k+1)`, 오른쪽 자식 index는`(2k+2)`다.

- 보통 자료구조들과 마찬가지로 insert, remove할 수 있다.
  - insert시 완전이진트리를 유지하기 위해 leaf 레벨의 마지막 노드에 추가되며, 최대/최소값 우선순위를 정하기 위해 부모 노드와 대소를 비교하며 swap된다.(until 부모 노드보다 값이 작거나 root노드에 접근)
  
- 최대값 추출시 heap 성질을 동일하게 유지하기 위해 root노드를 leaf노드와 swap한다. root 노드의 값에 대해 heapify를 진행한다.



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


## 관련 문제

[최대힙](https://www.acmicpc.net/problem/11279)