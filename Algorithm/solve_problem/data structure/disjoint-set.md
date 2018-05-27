# disjoint-set

크루스칼 알고리즘에서 이용하는 disjoint-set

`union-find` 자료구조라고도 불린다.

- find : 어떤 원소 주어졌을 때, 이 원소가 속한 집합을 반환한다. 이 find를 통해 2개의 원소들 간의 find 결과(대표 원소들)를 비교하여 같은 집합임을 판단한다.

- Union : 만약 find를 통해 집합 대표 노드가 다르다면, 2개의 집합을 하나로 합친다.

위 연산을 정의하기 위해, 집합 표현방법이 필요하다.

```javascript
for(int i = 1; i<=V; i++){
    parent[i] = i;
}

function Find(x){
	if x.parent == x
		return x
	else
	  return Find(x.parent)
}

function Union(x, y){
  xRoot := Find(x)
  yRoot := Find(y)
  xRoot.parent := yRoot
}
```

일단 초기값은 자기 자신이 집합 대표다.

여튼 이 단순한 disjoint-set은 매우 불균형적 트리를 생성한다. 연결리스트와 다를 바가 없다.

그래서 이걸 극복하기 위해 `path compression`이나 `union by rank` 이용한다.

## 1. path compression

이것은 find 연산 수행할 때마다 트리의 구조를 `평평하게` 만드는 방법이다. 이 방법은 **루트 노드까지 순회중 방문한 각 노드들이 직접 루트 노드를 가리키도록 갱신**하는 것으로, 모든 노드들은 같은 대표 노드를 공유하게 된다. 최종적으로 생성된 트리는 보다 평평하며, 이는 대표 노드를 직/간접적으로 참조하는 연산의 속도를 향상시킨다. 다음은 향상된 find 연산이다.

```javascript
function Find(x){
	if x.parent != x
	  x.parent := Find(x.parent)
	return x.parent
}
```

## 2. union by rank

항상 작은 트리를 큰 트리에 붙이는 것이다. 트리의 깊이가 실행시간에 영향을 주기 떄문이다. 만약 깊이가 같을 경우 알고리즘이 멈추므로 `rank`라는 용어를 사용한다.

1개의 원소를 가지는 경우 `rank:0`, 같은 랭크 `r`을 가지는 경우 랭크 `r+1`의 트리가 만들어진다.


## summary

`disjoint-set`을 쓰려면 일단 path compression을 이용하여 구현하자. (간단하다))

## 관련 문제

[집합의 표현](https://www.acmicpc.net/problem/1717)
[친구 네트워크](https://www.acmicpc.net/problem/4195)
