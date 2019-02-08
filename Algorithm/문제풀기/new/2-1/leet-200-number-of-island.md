# 200. number of island

백준에서도 풀어봤던 문제다. 조금 다른건 leetcode 방식으로 풀어야된다...

섬이 몇개인지 구하기.

각 셀에 대해 dfs를 진행
- 재귀함수
  - task : 셀 방문
  - 위,오른쪽,아래,왼쪽 순으로 재귀(dfs)를 진행하여 basecase에 도달하면 dfs 중단.
- basecase
  - 현재 방문한 셀이 섬이 아니거나
  - 이미 방문 해봤거나
  - 영역에서 벗어났거나

```C
class Solution {
public:
    int dirX[4] = {0,1,0,-1};
    int dirY[4] = {-1,0,1,0};
    int result;
    bool isFirst;
    
    // 셀 방문하기
    // - 해당 셀이 0이면 return;
    // - 방문했으면 return;
    // 1이면 여기서부터 다시 for i<4; 재귀 방문
    // 카운팅 어케?
    void visitCell(int row, int col, vector<vector<bool>>& visited, vector<vector<char>>& grid) {
        // basecase
        // 영역 벗어나면
        if(row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) {
            return;
        }
        // 방문 했으면 return;
        if(visited[row][col]) {
            return;
        }
        visited[row][col] = true;
        // 해당 셀이 0이면 return
        // if(!strcmp(grid[row][col], "0")) {
        if(grid[row][col] == '0'){
            return;
        }
        
        if(this->isFirst) {
            this->isFirst = false;
            this->result += 1;
        }
        
        for(int i = 0; i<4; i++) {
            int nextRow = row + dirX[i];
            int nextCol = col + dirY[i];
            
            visitCell(nextRow, nextCol, visited, grid);
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() == 0) {
            return 0;
        }
        // 방문 여부 벡터
        int rowLen = grid.size();
        int colLen = grid[0].size();
        vector<vector<bool>> visited(rowLen);
        
        // 방문값 초기화
        for(int i = 0; i<rowLen; i++) {
            for(int j = 0; j<colLen; j++) {
                visited[i].push_back(false);
            }
        }
        
        for(int i = 0; i<grid.size(); i++) {
            for(int j = 0; j<grid[i].size(); j++) {
                this->isFirst = true;
                visitCell(i,j,visited, grid);
            }
        }
        return this->result;
    }
};

```

## 배운거

2차원 vector를 함수에 전달하기 vs 2차원 배열 함수에 전달하기
(2차원 vector를 _call by value로 vector 전달받았다가 계속 틀림.._)

[참고](https://hashcode.co.kr/questions/764/2%EC%B0%A8%EC%9B%90-%EB%B0%B0%EC%97%B4%EC%9D%84-%ED%95%A8%EC%88%98%EB%A1%9C-%EC%A0%84%EB%8B%AC%ED%95%A0-%EC%88%98%EA%B0%80-%EC%97%86%EC%8A%B5%EB%8B%88%EB%8B%A4)

```C
void funcV(vector<vector<int>>& v) {
    v[0].push_back(10);
}

void funcA(int a[][10]) {
    a[0][1] = 11;
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> v(1);
    
    v[0].push_back(1);
    
    funcV(v);
    
    cout<<v[0][0]<<endl;
    cout<<v[0][1]<<endl<<endl;
    
    int a[0][10];
    
    a[0][0] = 5;
    funcA(a);
    cout<<a[0][0]<<endl;
    cout<<a[0][1]<<endl;

    return 0;
}
```