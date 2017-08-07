# 11.3 최소 스패닝 트리

## 스패닝 트리

모든 정점을 포함하는 부분 트리다.

> Tree는 cycle을 갖지 않는 연결 그래프
> Graph는 정점\(vertex\)과 정점을 연결하는 간선\(Edge\)의 집합 \(`G=(V,E)`\)

그래프 G의 스패닝 트리는

* G의 모든 꼭짓점을 포함한다.
* G의 부분 그래프다.

## 최소 스패닝 트리

여기서 `최소` 스패닝 트리는 그래프의 각 간선\(Edge\)에 `비용`이 주어질 경우
각 변의 **비용의 합이 최소가 되는** 부분 그래프인 `트리`다.

요약하면, 최소 신장 트리는
사이클을 형성하지 않으면서 모든 간선이 최소로 연결된 무방향 그래프다.

---

최소 스패닝 트리를 구현할 수 있는 알고리즘은 2가지가 있다.

## 1. Prim 알고리즘

greedy와 비슷하다.

1. 그래프에서 하나의 정점을 선택한다.
2. 선택한 정점의 간선들을 포함하는 집합을 만든다.\(비용 포함\)
3. 이 집합 중에서 가장 작은 비용을 가진 간선을 선택한다.
4. 간선의 목적지 정점을 선택한다.
   * 이 때, 트리의 특성인 `사이클을 형성하지 않는 것`을 만족하지 않으면 3번으로 간다.
5. 2~4번을 스패닝 트리의 간선이 정점-1개가 될 때까지 진행한다.
   * 최소 신장 트리는 모든 정점이 연결되면 종료되기 때문이다.

요약하면,
정점 하나 선택해서 가장 작은 비용을 가진 간선 선택한다.
선택된 간선의 목적지 정점을 선택해서 가장 작은 비용을 가진 간선 선택한다.\(사이클 안만드는 간선을 선택\)

예제는 위키피디아를 [참고](https://ko.wikipedia.org/wiki/프림_알고리즘)하자.

## 시간복잡도

| 최소 변 비용 자료 구조 | 시간 복잡도 |
| :--- | :---: |
| 인접 행렬 | V^2 |
| 이진 힙, 인접 리스트 | O\(\(V+E\)logV\) =  ElogV |
| 피보나치 힙, 인접 리스트 | E + VlogV |

## 구현

[최소 스패닝 트리 구현 문제](https://www.acmicpc.net/problem/1197)를 Prim으로 푼것이다.

```C
#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

int V, E, currentVertex=1, result = 0, initialVertex;

bool isVisited[10001];

vector <pair<int, int> > graph[100001];

class CompareDist{
public:
    bool operator()(pair <int, int> n1, pair <int,int> n2){
        return n1.second > n2.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int> >, CompareDist> pq;

void prim(){
    int connected = 0;
    // pq에 첫번째 간선 정보 추가. initialVertex
    isVisited[initialVertex] = true;

    for(int i = 0; i<graph[initialVertex].size(); i++){
        pq.push(make_pair(graph[initialVertex][i].first, graph[initialVertex][i].second));
    }

        // 첨엔 큐가 비어있을 때까지 반복하였다.
    while(connected < V-1){
        int to = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        if(!isVisited[to]){
            result += cost;
            isVisited[to] = true;
            currentVertex = to;

            connected+=1;

            for(int i = 0; i<graph[currentVertex].size(); i++){
                if(!isVisited[graph[currentVertex][i].first]){
                    pq.push(make_pair(graph[currentVertex][i].first, graph[currentVertex][i].second));
                }

            }
        }
    }
    printf("%d\n", result);
}

int main(){
    scanf("%d %d", &V, &E);
    int from,to,cost;
    for (int i = 0; i<E; i++){
        scanf("%d %d %d", &from, &to, &cost);
        graph[from].push_back(make_pair(to, cost));
        graph[to].push_back(make_pair(from, cost));
        if(i==0) initialVertex = from;
    }
    prim();
    return 0;
}
```

`최소 비용`을 가진 간선을 선택하기 위해 `priority_queue`를 이용하였다.

`2. 선택한 정점의 간선들을 포함하는 집합을 만든다.(비용 포함)의 자료구조 선택`

처음엔 출발점, 도착점, 비용을 갖는 구조체\(`from,to,cost`\)로 구현했다.
하지만, 선택한 정점의 간선을 포함하는 `집합`을 우선순위 큐에 넣기 위해서는 내가 처음에 생각한 구조체로 선택한 간선을 찾을 수 없었다. \(이차원 배열 구조체를 통해 row를 `from`으로 하고 구조체 안의 값은 `to,cost`로 하면 가능했을듯..?\)

여튼 vector 컨테이너 배열을 이용\(타입은 pair\(to, cost\), index를 from\)하였다.
그래서 선택한 정점\(index\)이 가진 모든 간선 정보를 우선순위 큐에 넣어 집합을 관리 하였다.

#### 양방향

틀렸습니다 후, 위키피디아의 예제를 대입했으나 최소가 아닌 값이 나왔다.

문제에서의 그래프는 무방향\(양방향\) 그래프 였다.
vector 자료구조에 `from, to`만\(`to, from` 제외\) 추가하였다. 그래서 방문한 적 없고, 최소 비용임에도 불구하고, 간선 정보가 없기 때문에 우선순위 큐에 추가할 수 없었다..

---

## 2. kruskal

1. 그래프의 정점이 각각 하나의 tree가 되도록 한다.
2. 모든 변을 원소로 갖는 집합 S를 만든다
3. S가 비어있을 때까지
   * 가장 작은 cost를 가진 간선을 빼온다.
   * 이 간선의 두 개의 정점이 다른 tree 집합이라면 연결\(합침\)한다.
   * 만약 같은 tree 집합\(연결된\)이라면 cycle이 발생하므로 해당 간선정보는 버린다

cycle 발생 여부 판단을 위해 tree 집합을 이용한다. 이 때 tree 집합은 `disjoint-set 자료구조`를 이용한다.

## 구현

```C
struct Edge{
    int from,to,cost;
};

bool compareEdge(Edge x, Edge y){
    return x.cost < y.cost;
}

int V,E, parent[10001];

int findParent(int i){
    if(parent[i]==i) return i;

    // 찾으면서 업데이트, 전체 동작 시간복잡도가 O(1)로 : path compression
    parent[i] = findParent(parent[i]);

    return parent[i];
}

// 첫번째 i 집합의 부모를 j로 하여 union
void unionParent(int i, int j){
    parent[findParent(i)] = findParent(j);
    return;
}

int main(){

    scanf("%d %d", &V, &E);
    int connected = 0, result = 0;
    vector <Edge> edges(E);

    for(int i = 0; i<E; i++){
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
    }

    sort(edges.begin(), edges.end(), compareEdge);

    // dispoint-set 집합 초기화
    for(int i = 1; i<=V; i++){
        parent[i] = i;
    }

    // kruskal
    // 가장 작은 값 빼내서
    // 빼온 간선의 정점들 parent 비교

    for (int i = 0; connected<V-1; i++){
        int from = edges[i].from;
        int to   = edges[i].to;
        int cost = edges[i].cost;

        if(findParent(from) != findParent(to)){
            unionParent(from, to);
            result += cost;
            connected+=1;
        }
    }

    printf("%d\n", result);

    return 0;
}
```

## 언제 쓸까?

최소 비용으로 모든 정점을 다 방문해야 할 때. DFS와 BFS와 같은 탐색을 최소 비용으로 방문해야 할 때..?

## 관련 문제

[최소 스패닝 트리](https://www.acmicpc.net/problem/1197)
[네트워크 연결](https://www.acmicpc.net/problem/1922)
[행성 터널](https://www.acmicpc.net/problem/2887)
