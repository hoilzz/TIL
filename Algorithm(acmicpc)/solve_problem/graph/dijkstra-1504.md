# 1504 특정한 최단 경로

N은 정점 개수다.
(1,N)까지의 최단 거리를 구해야 한다.
단, 입력받은 2개의 정점을 꼭 통과해야한다.
만약 최단경로가 없다면 -1을 출력한다.

## Solution

### fail

최단경로면서, 가중치 값이 양인 것을 보고 다익스트라를 떠올렸다.
이 때, 2개의 정점을 꼭 통과해야 했다.
이에 대한 해결책으로

```
// A, B : 통과해야 할 2개의 정점
dijkstra(1,N);
if(dist[A] < dist[B]) 최단 거리 경로 : 1-A-B-N
else									최단 거리 경로 : 1-B-A-N
```

위와 같이 단순하게 생각했다.

다익스트라로 최단경로 구할 시, 출발지는 0으로 초기화 후, 도착지까지 최단경로를 구한다. 즉, `1-A VS 1-B` 에서 A가 더 최단거리일지라도 A-B-N 보다 B-A-N이 더 최단거리일 수 있다.

### success

출발지에 따라 사용할 수 있는 간선이 달라지기 때문에 모든 출발지-도착지에 대해 비용을 비교해야한다.

```C
shortestCost = min(dijkstra(1,A) + dijkstra(A,B) + dijkstra(B,N),
		dijkstra(1,B) + dijkstra(B,A) + dijkstra(A,N))
```

### fail

위와 비슷한 맥락이다.
최단경로는 출발지(`cost=0`)에 따라 달라진다.
두번째 경로(ex. A-B)에 대한 최단경로 구할 때, 첫번째 경로(ex. 1-A)의 각 정점에 대한 최단경로(`dist[vertex]`)를 초기화 하지 않았다. 출발지가 달라졌을 때 모든 최단경로가 달라질 것이라고 생각하지 못했다.

이외에도 최단경로를 가진 정점을 먼저 방문하기 위한 우선순위 큐도 초기화해야한다.


```C
#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long ll;

class CompareCost{
public:
    bool operator()(pair<int, ll> n1, pair<int, ll> n2){
      return n1.second > n2.second;
    }
};

const int INF = 800001;
vector <pair <int, ll> > edges[801];
priority_queue <int, vector<int>, greater<ll> > mustPass;

bool isVisited[801];
ll dist[801];
int N;

void dijkstra(int start, int dst){

  fill_n(dist, N+1, INF);
  fill_n(isVisited, N+1, false);
  dist[start] = 0;

  priority_queue <pair <int, int>, vector <pair <int, int> >, CompareCost> pq;

  pq.push(make_pair(start, dist[start]));

  while(!pq.empty()){
    int current;

    do {
      current = pq.top().first;
      pq.pop();
    }while(!pq.empty() && isVisited[current]);

    if(current == dst) return;

    isVisited[current] = true;

    for(int i = 0; i<edges[current].size(); i++){
      int to    = edges[current][i].first;
      ll cost   = edges[current][i].second;

      if(dist[to] > dist[current] + cost){
        dist[to] = dist[current] + cost;
        pq.push(make_pair(to, dist[to]));
      }
    }
  }
}

int main() {

  int M, mustPassArr[2];
  ll result1 = 0, result2 = 0;

  scanf("%d %d", &N, &M);

  for(int i = 0; i<M; i++){
    int from, to, cost;
    scanf("%d %d %d", &from, &to, &cost);
    edges[from].push_back(make_pair(to, cost));
    edges[to].push_back(make_pair(from, cost));
  }

  scanf("%d %d", &mustPassArr[0], &mustPassArr[1]);

  for (int i=0; i<2; i++) mustPass.push(mustPassArr[i]);

  dijkstra(1, mustPassArr[0]);
  result1 += dist[mustPassArr[0]];

  dijkstra(mustPassArr[0], mustPassArr[1]);
  result1 += dist[mustPassArr[1]];

  dijkstra(mustPassArr[1], N);
  result1 += dist[N];

  dijkstra(1, mustPassArr[1]);
  result2 += dist[mustPassArr[1]];

  dijkstra(mustPassArr[1], mustPassArr[0]);
  result2 += dist[mustPassArr[0]];

  dijkstra(mustPassArr[0], N);
  result2 += dist[N];

  ll result = min(result1, result2);

  if(result >= INF)printf("-1\n");
  else{
    printf("%lld\n", result);
  }

  return 0;
}
```


## Issue

- `방향성이 없는 그래프가 주어졌다` 라는 내용을 보고 양방향 그래프라는 걸 떠올렸어야 했는데 그러지 못했다.


## Summary

그래프에서 각 정점에 대한 최단경로는 같은 그래프 일지라도 시작점에 따라 달라진다. 따라서, 시작점이 달라질 때마다 각 정점에 대한 최단경로, 최단경로를 가진 정점을 먼저 파악하기 위한 우선순위 큐는 모두 초기화해야한다.
