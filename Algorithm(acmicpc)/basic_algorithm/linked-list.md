# linked list

자료구조는

	1. 삽입
	2. 삭제
	3. 탐색

이 3가지 연산을 빨리 하기 위해 각 상황에 맞는 자료구조들이 있다.

많은 자료구조 중 리스트는 순서가 존재하는 값들을 가진 자료구조다. 흔히 `배열`과 `연결 리스트`로 나누어진다.


---


`배열`은 같은 타입의 자료형이 연속된 주소에 존재하는 것이다.

배열의 장점은 index값을 통해 요소에 `O(1)`에 접근 할 수 있다. 하지만, `요소 이동`, `배열의 길이 변화`가 어렵기 때문에, 새로운 요소를 추가할 때 `최악의 경우 O(N)`이 걸릴 수 있다. (배열 새로 할당하고, 삽입된 위치부터 원소를 하나씩 밀어야한다.)


---


Linkedlist 를 이용하면 크기 변화가 어렵다는 단점을 극복할 수 있다.

`LinkedList`는 요소들이 **포인터를 이용하여 한 줄로 연결**되어있기 때문이다.

---


## insert

37 값을 가진 노드를 삽입해보자.

![insert in linked list](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/CPT-LinkedLists-addingnode.svg/474px-CPT-LinkedLists-addingnode.svg.png)

`head` 포인터는 첫번째 노드를 가리킨다.

`node`는 요소값(data), 다음 노드를 가리키는 포인터(next)로 이루어져있다.
	- 가장 마지막 노드의 next는 null이다.

*function insert*

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

삽입,삭제는 `O(N)`이 걸린다.

head 포인터만 가질 때, 첫번쨰 노드부터 next 포인터를 통해 하나하나 찾아야기 때문이다.

하지만 head 포인터를 통해 첫번째 요소에 추가,삭제 하는 것은 `O(1)`이다.

마지막 값을 가리키는 tail 포인터를 사용하면 마지막 요소도 `O(1)`이 소요된다.

> 배열은 추가할 때, 값을 다 한칸씩 밀어줘야 하므로 O(1)이 될 수 없다.
> 하지만 배열의 장점이 있다. 연결리스트에는 없는 `random access`를 할 수 있다.
> K번째 요소 찾아가려면 배열은 `arr[K]`로 `O(1)`만에 참조한다.
> 연결리스트는 next pointer를 K번 거쳐야 하므로 `O(K)` 걸린다.

---

배열은 random access 할 때 사용
연결리스트는 삽입/삭제가 많이 이루어질 떄 사용

```C
#include <iostream>
using namespace std;

class ListNode{
public:
    int value;
    ListNode *next; // 마지막 노드 null

    // 생성자
    ListNode(): next(nullptr){}
    ListNode(int value1, ListNode *next1): value(value1), next(next1){}
};

class LinkedList{
public:
    ListNode *head;
    int size;

    // 생성자
    LinkedList(): size(0), head(nullptr){}

    // 소멸자
    ~LinkedList(){
        ListNode *t1 = head, *t2;
        while(t1 != nullptr){
            t2 = t1->next;
            delete t1;
            t1 = t2;
        }
    }

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
