# linked list

자료구조는

  1. 삽입
  2. 삭제
  3. 탐색

이 3가지 연산을 빨리 하기 위해 각 상황에 맞는 자료구조들이 있다.

많은 자료구조 중 `리스트`는 **순서가 존재하는 값들을 가진** 자료구조다. 흔히 `배열`과 `연결 리스트`로 나누어진다.

---

`배열`은 같은 타입의 자료형이 연속된 주소에 존재하는 것이다.

배열의 장점은

- index 값을 통해 요소에 `O(1)`에 접근 가능하다. 즉, random access가 가능하다.

배열의 단점은 

- 특정 인덱스의 원소를 삭제할 경우 배열의 연속적인 특징이 깨지게 된다. 즉 빈 공간이 생기게 된다. 따라서 삭제한 원소보다 더 큰 인덱스를 갖는 원소들을 `shift` 해줘야 하는 비용이 생긴다. 이것은 O(n)이 소요된다. 

- 삽입도 마찬가지다. 특정 인덱스에 원소 추가시 추가된 인덱스부터 끝까지 1씩 `shift` 해줘야 한다.

---

Linkedlist 를 이용하면 `Array의 크기 변화`가 어렵다는 단점을 극복할 수 있다. `LinkedList`는 요소들이 **포인터를 이용하여 한 줄로 연결**되어있기 때문이다. 즉, 각 원소들은 자신 다음에 어떤 원소인지 기억하고 있기 때문에, 이 부분만 다른 값으로 바꿔주면 삭제와 삽입을 O(1)만에 해결할 수 있다.

하지만 다른 문제를 가지고 있다. 삽입/삭제할 경우 원하는 위치를 검색해야 하는데 첫번째 원소부터 확인해봐야 한다. Array와 달리 논리적 저장 순서와 물리적 저장 순서가 일치 하지 않기 때문이다. 이 과정 때문에 어떤 원소를 추가/삭제할 경우 그 원소를 찾기 위해 O(n)의 시간이 발생한다.

결국 linked list 자료구조는 search도 O(N)을 가지고, 삽입 삭제 에서도 O(n)을 갖는다. Array보다 더 단점이 많아보이지만 tree 구조의 근간이 되며, Tree에서 사용시 그 유용성이 드러난다.

---

배열은 random access 할 때 사용
연결리스트는 삽입/삭제가 많이 이루어질 떄 사용


## 언제 사용할까?

연결리스트는 다양한 구조를 가진다.

1. 원형 연결 리스트 : 마지막 노드의 next가 다시 첫번째 노드를 가리켜 cycle 구조를 갖는다.
2. 이중 연결 리스트 : 각 노드가 next 포인터 뿐만 아니라, 이전 노드를 가리키는 prev 포인터를 추가로 갖는 구조다. 

## insert

37 값을 가진 노드를 삽입해보자.

![insert in linked list](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/CPT-LinkedLists-addingnode.svg/474px-CPT-LinkedLists-addingnode.svg.png)

`head` 포인터는 첫번째 노드를 가리킨다.

`node`는 요소값(data), 다음 노드를 가리키는 포인터(next)로 이루어져있다.
  - 가장 마지막 노드의 next는 null이다.

```javascript
function insertAfter(Node node, Node newNode){
  newNode.next = node.next
  node.next    = newNode
}
```

## delete

99값을 가진 노드를 지워보자.

![delete in linked list](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d4/CPT-LinkedLists-deletingnode.svg/380px-CPT-LinkedLists-deletingnode.svg.png)

```javascript
function removeAfter(Node node){
     tempNode = node.next
     node.next = node.next.next
     destroy obsoleteNode
}
```

---



```C
#include <iostream>
using namespace std;

class ListNode{
public:
    int value;
    ListNode *next; // 마지막 노드 null
    ListNode *prev;

    // 생성자
    ListNode(): next(nullptr), prev(nullptr){}
    ListNode(int value1, ListNode *prev, ListNode *next): value(value1), prev(prev), next(next){}
};

class LinkedList{
public:
    ListNode *head;
    int size;

    // 생성자
    LinkedList(): size(0), head(nullptr){}

    void insert(int k, int value){ // k번째 원소 앞에 새 원소 삽입
        if(k == 0){ // 처음에 삽입
            // 기존의 head를 새로 생성된 노드의 next로 설정
            // 반환된 노드가 LinkedList.head 에 재정의
            head = new ListNode(value, head);
        }
        else{ // k번째 원소 앞에 삽입
            ListNode *dest = head;
            for(int i=0; i<k-1; i++) dest = dest->next;
            dest->next = new ListNode(value, dest->next);
        }
        size++;
    }

    void erase(int k){ // k번째 원소를 제거
        if(k == 0){ // head를 삭제
            ListNode *temp = head->next;
            delete head;
            head = temp;
        }
        else{ // k번째 원소 삭제
            ListNode *dest = head, *temp;
            for(int i=0; i<k-1; i++) dest = dest->next;
            temp = dest->next->next;
            delete dest->next;
            dest->next = temp;
        }
        size--;
    }

    int search(int value){ // 값을 찾아 첫번째 인덱스 리턴, 없으면 -1 리턴
        ListNode *temp = head;
        for(int i=0; i<size; i++){
            if(temp->value == value) return i;
            temp = temp->next;
        }
        return -1; // 못 찾음
    }
};


int main(){
    LinkedList<int> linkedlist;
    linkedlist.insert(0, 1);
    linkedlist.insert(1, 2);
    linkedlist.insert(2, 3);
    linkedlist.insert(0, 4);
    linkedlist.insert(0, 5);
    linkedlist.insert(5, 6);
    linkedlist.insert(4, 7);
    linkedlist.insert(1, 8);
    linkedlist.erase(4);
    linkedlist.erase(0);
    linkedlist.erase(5);
    linkedlist.insert(3, 9);
    linkedlist.erase(1);
    linkedlist.insert(1, 10);

    ListNode *temp = linkedlist.head;
    for(int i = 0 ; i<linkedlist.size;i++){
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}
```

## 관련 문제

[조세퍼스](https://www.acmicpc.net/problem/1158)
