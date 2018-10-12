# BFS

시작 정점을 방문한 후 시작 정점에서 갈 수 있는 모든 정점들을 우선 방문하는 방법이다.
더 이상 방문하지 않은 정점이 없을 때까지 방문하지 않은 모든 정점들에 대해서도 넓이 우선 검색을 적용한다

## 장점

- DFS와 다르게, 출발-목표 노드까지 최단 길이 경로 보장한다.

## 단점

- 경로가 매우 길 경우 탐색할 노드 수가 급격히 증가해서, 보다 많은 공간을 차지한다.

## 수행 과정

1. 현재 정점에서 갈 수 있는 모든 정점을 큐에 모두 넣는다.
 	- **큐에 넣을 때마다 방문 체크** 한다.
2. 큐의 front 값에서 다시 1번을 수행한다.
3. 큐가 empty가 될 때까지 1,2번 수행한다.

## 구현

```C
void BFS(int start){
  // 시작점에서 갈 수 있는 모든 정점 큐에 담기
  // 큐 가장 앞에 있는 얘로 BFS 다시 시작.
  // BFS는 큐가 비어있을 때까지..

  qu.push(start);
  isVisited[start] = true;

  while(!qu.empty()){
    int from = qu.front();
    qu.pop();
    printf("%d ", from);

    for(int i = 0; i<graph[from].size(); i++){
      int to = graph[from][i];
      if(!isVisited[to]){
        qu.push(to);
        isVisited[to] = true;
      }
    }
  }
}

void main(){
	int from, to, start;

  scanf("%d %d %d", &N, &M, &start);

  for (int i = 0; i<M; i++){
    scanf("%d %d", &from, &to);
    graph[from].push_back(to);
    graph[to].push_back(from);
  }

  // fill_n(isVisited, 1001, false);

  BFS(start);
}
```


## Issue

- 큐에 정점 추가시 매번 방문 체크(isVisited=true)한다. 또한 정점 추가 전에 방문 체크 확인한다.
