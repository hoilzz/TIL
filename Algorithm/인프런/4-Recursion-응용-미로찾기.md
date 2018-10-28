# Recursion 응용 - 미로찾기

![img]('./img/3-1-recursion)

리커시브하게 생각해보자.

현재 위치에서 출구까지 가는 경로가 있으려면

1. 현재 위치가 출구이거나 혹은
2. 이웃한 셀들 중 하나에서 현재 위치를 지나지 않고 출구까지 가는 경로가 있거나

## Decision Problem

**답이 yes or no 인 문제**

- 출구까지 가는 경로가 **있니 없니**

```
boolean findPath(x, y)
    // 1) 현재 위치가 출구거나
    if (x, y) is the exit
        return true;
    // 2)
    else
        // x,y에 이웃한 인접한 셀(최대 4개) 각각에 대해
        for each neighbouring cell (x', y') of (x,y) do
            // wall이 아닌 길이라면
            if (x', y') is on the pathway
                // 이 길에 대해서 다시 findPath
                if findPath(x', y')
                    return true
        return false;
```

Recursion 을 작성시 기본적으로 고려할 것

- **무한루프에 빠지지 않는가**
  - 자기 자신을 계속 호출하기 때문에
  - **recursion 은 basecase 로 수렴한다** 를 성립시켜야함

사실 위 findPath 는 무한루프에 빠질 가능성 있음

- (x,y)가 (x', y')로 갈 경우 (x' = x + 1, y' = y)
  - (x' -1, y)를 리커젼으로 돌 경우 계속 반복됨

#### 해결책은?

- visited 변수로 방문 여부 관리

```
boolean findPath(x, y)
    // 호출된 x,y가 벽이거나 visited면 즉시 false 리턴하고 종료.
    if (x,y) is either on the wall or a visited cell
        return false;
    if (x, y) is the exit
        return true;
    else
        mark (x, y) as a visitied cell;
        for each neighbouring cell (x', y') of (x,y) do
                if findPath(x', y')
                    return true
        return false;
```

basecase

1. (x,y)가
   - 벽이거나
   - 방문했거나
   - 출구라면

## 코드 짜보자

```
static const PATHWAY_COLOUR = 0; // 지나갈 수 있는 길
static const WALL_COLOUR = 1;  // 벽(못지나감)
static const BLOCKED_COLOUR = 2; // 방문했는데 2가지 색 쓸거임. 방문해봤는데 꽝임
static const PATH_COLOUR = 3;  // 방문해봤는데 출구까지 갈 수 있을지 없을지 아직 모름

bool findMazePath(int x, int y) {
    if (x<0 || y<0 || x>=N || y>=N) return false;
    // 벽이거나, 방문했거나(blocked or path)
    else if (maze[x][y] != PATHWAY_COLOUR) {
        return false;
    }
    // 출구
    else if ( x== N-1 && y == N-1) {
        maze[x][y] = PATH_COLOUR;
        return true;
    }
    else {
        maze[x][y] = PATH_COLOUR;
        // 북,동,남,서 순으로 방문
        // 1개라도 true면 나머지 검사할 필요 없음. 그래서 or 적용
        if ( findMazePath(x-1, y) || findMazePath(x, y +1) || findMazePath(x+1, y) || findMazePath(x, y-1)) {
            return true;
        }
        maze[x][y] = BLOCKED_COLOUR; // dead end
        return false;
    }
}

int main() {
    printMaze();
    findMazepath(0,0);
    printMaze();
}
```

북,동,남,서로 이동할 때 움직인 경로

![img](./img/3-2-recursion)
