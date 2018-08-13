# disjoint-set(서로소 집합 자료구조)

disjoint set은 서로 중복되지 않는 부분 집합들이다.

다음 개념들을 사용한다

- set: 원소들의 집합 (순서 고려 X)
- subset: 셋 A의 모든 원소가 셋 B에 포함될 때
- superset: 위 예시에서 B는 A의 superset이다
- mutually disjoint: A와 B가 공유하는 원소가 없을 때
- partition(분할): 임의의 셋을 분할하는 것은 다음 2가지 속성을 만족하는 disjoint-set이 되도록 셋을 쪼개는 것을 의미한다.
  - 분할된 부분집합을 합치면 원래의 셋이 된다.
  - 파티션된 부분집합 끼리는 mutually disjoint를 만족한다.


다음 연산들을 제공한다.

- find(x): x가 속한 셋의 루트노드 값을 반환
- union(x, y): x가 속한 셋과 y가 속한 셋을 합친다.
- makeset(x): x를 원소로 하는 새로운 셋을 만든다.


## 배열로 구현

![disjoint-1](../img/disjoint-1.png)

find의 시간복잡도는  disjoint-set의 원소가 n개 일 때 O(logN)이다. leaf노드 부터 루트까지 올라가야 하기 때문이다. find 연산을 좀 더 효율적으로 수행하기 위해 **path compression**에 대해 뒤에서 알아보자.

또한 union의 방법에는 **union-by-size**, **union-by-height**가 있다.

## union

![disjoint-2](../img/disjoint-2.png)

2개의 disjoint set을 합칠 때,

- union-by-size : 원소수가 적은 셋을 많은 셋의 서브 트리로 합치는 것이 효율적이다. - union-by-height : 또한, 트리의 높이가 작은 셋을 큰 셋의 서브트리로 합쳐야한다.

위와 같이 합칠 경우, find 연산의 효율을 높여준다.

구현하는 방법은 배열 rootNodeIndex의 루트 노드 정보를 바꾸며 된다. 루트노드일 때 0인 값을 inputArr에서 root노드의 index로 변경한다.

위 2가지 union의 시간복잡도는 O(1)이다. find에서 이미 루트노드를 찾았기 때문에 인덱스만 변경해주면 된다.

## path compression

![disjoint-3](../img/disjoint-3.png)

path compression은 아래 그림과 같이 모든 노드가 루트를 가리키도록 만드는 것이다. rootNodeIndex에 부모노드 인덱스 대신에 루트노드를 저장하는 방식이다. find 연산을 수행시 트리의 높이만큼 거슬러 올라가야 루트노드를 찾는데, 이 비효율성을 완화하는 것이다.

## 언제 쓸까?

서로소 집합 자료구조라는 이름 그대로, 전체 집합에서 원소들이 겹치지 않도록 분할(partition)하는데 자주 쓰인다.

