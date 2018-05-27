# 1920 내리막길

출발점에서 도착지까지 내리막길 형태로 갈 수 있는 경로 개수 찾기

내리막길 형태란

	- 각 위치에 대한 값이 주어진다
	- `다음 위치의 값 < 현재 위치의 값` 일 때 내리막길 형태로 이동 할 수 있다.
		- 다음 위치는 상하좌우로 이동 가능

## Solve

경로 개수 찾아야 하니까 DFS, BFS를 떠올릴 수 있다.

동시에 DP를 이용할 수 있다.

각 위치를 `0`으로 초기화 하고, 목적지만 1로 설정한다.

현재 위치에서 상하좌우 위치가 내리막길이라면 DFS 계속 진행한다.

목적지에 도달시, 현재 스택의 함수를 종료 후, 1을 반환한다. (내리막길이 아니기 때문에 목적지에 도달하지 못하면 0을 반환받는다.)

	- 이 때, memoization을 이용하여 경로 개수를 각 위치에서 저장한다.
	- 특정 위치 방문시, 상하좌우로 방문하는게 아닌, DFS로 방문할 때, 경로의 개수가 저장되있다면 DFS 진행하지 않고 그 값을 반환한다.

그래서 이렇게 짜면 시간초과 난다.

---

위에서는 시간초과가 나지 않도록 하기 위해 다음 조건에서 memoization을 사용했다.

	- 해당 위치에서 목적지까지 갈 수 있는 방법이 1가지 이상이라면 DFS 진행하지 않고 반환받는다.

`해당 위치에서 목적지까지 갈 수 있는 경로 개수를 알면 진행하지 않는다` 외에 한 가지를 더 생각했어야 하는데 다음과 같다.

**`해당 위치에서 목적지를 갈 수 없다면 진행하지 않는다.`**

---

이것을 표현하기 위해, 모든 위치를 `-1`로 초기화한다.

방문한 위치는 `0`으로 초기화 한다.

DFS로 위치 방문시, 2가지를 확인한다.

	- 이 위치에서 목적지까지 갈 수 없는지 여부
	- 이 위치에서 목적지까지 갈 수 있는 경로 개수

```
int road[500][500] = {-1}

int DFS(x,y){
	...
	if(road[x][y] >= 0) return road[x][y];
	...
}
```

내리막길.cpp
```C
#include <iostream>
#include <cstdio>
using namespace std;

int map[500][500], row, col, road[500][500] = {0};

int DFS(int x, int y){
    int moveX[4] = {0,1,0,-1};
    int moveY[4] = {-1,0,1,0};

    if (x < 0 || y < 0 || x >= row && y >= col) return 0;

    if(x == row-1 && y == col-1) return 1;

    if(road[x][y] >= 0) return road[x][y];

    road[x][y] = 0;

    for(int i = 0; i <4; i++){
        int tempX = x + moveX[i];
        int tempY = y + moveY[i];

        if(map[tempX][tempY] < map[x][y]){
            road[x][y] += DFS(tempX, tempY);
        }
    }
    return road[x][y];
}

int main() {
    scanf("%d %d", &row, &col);

    road[row-1][col-1] = 1;

    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            scanf("%d", &map[i][j]);
            road[i][j] = -1;
        }
    }

    printf("%d\n", DFS(0,0));
}
```

## summary

- 시간초과를 줄이기 위한 memoization을 생각했다
- memoization에서 조건이 `갈 수 있다`와 같은 `할 수 있다없다`의 조건이라면 `반대`의 조건에 대해서도 메모이제이션 하자
