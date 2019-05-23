# 서비스명-문제번호-문제명
[1987 알파벳](https://www.acmicpc.net/problem/1987)

알파벳을 값으로 가지는 2차원 배열이 있다.

(0,0)에서 시작하여 상하좌우로 움직일 수 있다. 

이때, 중복된 알파벳을 방문하지 않으며 최대로 방문할 수 있는 경우의 수는?

_문제 설명_

## 내가 해결한 방법

DFS를 통해 방문할 수 있는 경우의 수를 비교하며 최대값 찾으려고함.

1. basecase에 해당하면 해당 count 바로 리턴
2. 상하좌우 방문(재귀)하며 더이상 방문하지 못했을 경우 리턴된 count 비교

```C
char board[20][20];

int R,C;
int directionRow[4] = {-1, 0, 1, 0};
int directionCol[4] = {0, 1, 0, -1};

int DFS(int row, int col, int count, bool visited[]) {
    // basecase : 보드 영역 밖
    if(row < 0 || col < 0 || row >= R || col >= C) {
        return count - 1;
    }
    char alphabet = board[row][col];
    int indexByAlphabet = (int)(alphabet - 'A');
    
    int finalCount = count;
    
    // basecase : 이미 방문한 알파벳일 경우
    if(visited[indexByAlphabet]) {
        return count - 1;
    }
    
    visited[indexByAlphabet] = true;
    
    for(int i = 0; i<4; i++) {
        int nextRow = row + directionRow[i];
        int nextCol = col + directionCol[i];
        int tempCount;
        
        // 재귀 고고
        tempCount = DFS(nextRow, nextCol, count + 1, visited);
        
        if(tempCount > finalCount) {
            finalCount = tempCount;
        }
    }
    
    // 이번 재귀 호출에서 방문한 알파벳 다시 미방문으로 리셋
    visited[indexByAlphabet] = false;
    
    return finalCount;
}

int main(int argc, const char * argv[]) {
    
    
    bool visited[26];
    fill_n(visited, 26, false);
    
    cin>>R>>C;
    
    for(int i =0; i<R; i++) {
        for(int j = 0; j<C; j++) {
            cin>>board[i][j];
        }
    }
    
    int result = DFS(0,0,1,visited);
    
    cout<<result<<endl;
    
    return 0;
}

```

### 시간복잡도

### 공간복잡도


## Summary

_1. 배운거_
_2. 배운거_
