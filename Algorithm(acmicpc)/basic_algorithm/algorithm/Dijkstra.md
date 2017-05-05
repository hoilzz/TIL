# 다익스트라

출발점과 도착점 사이의 최단경로 문제를 푸는 알고리즘이다.

단, 조건은

	- **어떤 변도 음수 가중치를 갖지 않는다.**
	- **유향그래프**이다.

예를 들어 어떤 그래프에서, 꼭짓점들이 각각 도시를 나타낸다고 하자.

변들이 도시 사이를 이동하는 가중치를 나타낸다면, **다익스트라 알고리즘을 통하여 두 도시 사이의 최단 경로**를 찾을 수 있다.

## 알고리즘의 개요

다익스트라 알고리즘은 `각 꼭짓점 v`에 대해 `시작점 s`에서 v까지의 최단 거리 `d[v]`를 저장하며 작동한다.

시작시 `d[s]=0`이다. 시작점을 제외한 모든 `d[v]=무한대`다. 즉 최단 경로를 모른 다는 표시다.

알고리즘 종료시 `d[v]`는 s에서 v까지의 최단경로를 나타낸다. 만약 경로가 존재하지 않으면 무한대로 남아있다.

> 다익스트라는 변 경감(edge relaxation)이라는 연산을 바탕으로 한다.
s에서 u까지의 최단경로 `d[u]`를 이미 알고 있고, u에서 v까지 가중치가 존재할 때,
s에서 v까지의 최단 경로는 `d[u](u까지의 최단경로) + (u,v)` 를 추가하여 얻을 수 있다.
`MIN(d[u] + (u,v) ,d[v])`를 통해 d[v] 값을 결정한다.
경감 연산은 모든 변 (u,v)에 대해 한번씩 경감이 적용되어 모든 d[v]가 최단 경로 비용을 나타내게 되었을 때 끝난다.


```C
class CompareDist{
public:
    bool operator()(pair <int, int>n1, pair <int, int>n2){
        return n1.first>n2.first;
    }
};

functino Dijkstra(int start){
	vector <pair <int, int>> adj[1001];   		// 가중치, 1000개의 점이 있다고 치자

	for (int i = 0; i < m; i++) {
        scanf("%d %d %d\n", &from, &to, &cost);
        adj[from].push_back(make_pair(to, cost));
    }

	priority_queue <pair<int,int>, vector<pair<int, int>, CompareDist> pq;			// 최단경로가 정해진 점을 저장
	vector<int> d(n + 1, INF);

	d[start] = 0;// 시작점만 0으로


	pq.push(make_pair(가중치, vertex 번호));

	// 큐가 비어있을 때까지
		// 현재 vertex = 큐.top.second;
		// 현재 vertex의 값 = 큐.top.first;
		// 큐.pop()

		// 큐에 저장됐을 시점 이후에 d[v]가 더 최소 비용으로 업데이트 됐을 경우 수행할 필요가 없다.
		if(현재 vertex의 값(큐에 저장된 값) <= d[현재 vertex]){
			for(int i = 0; i < adj[현재노드].size; i++){
				if(현재 노드의 값 + adj[현재노드][i].first((u,v)) < d[adj[현재노드][i].second]){
					d[v] = 현재 노드의 값 + (u,v);
					pq.push(make_pair(d[v], v 번호))
				}
			}
		}
}
```

`priority_queue <pair<int, int>, CompareDist>`

- 우선순위 큐를 이용하여 비교함수 생성하여 최소값을 항상 top에 위치하도록 하였다.

`vector <int> d(n+1, INF)`

- d를 선언시 모두 무한대로 초기화하였다.

`vector <pair <int, int>> adj[1001]`

- 1000개의 점이 있다고 가정하였다.
- adj의 인덱스 값은 출발점
- `adj[vertex][i].first, second` 를 이용하여 값을 비교한다.
