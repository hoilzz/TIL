# 5. Counting Cells in a Blob

## Recursive Thinking

현재 픽셀이 속한 blob의 크기를 카운트 하려면

-

```
// pseudo code
if pixel (x,y)가 grid 밖이라면
  result is 0
else if pixel (x,y)가 image pixel이 아니거나 이미 카운트 됐다면
  result is 0
else
  pixel (x, y)를 이미 카운트 되었다고 표시
  result는 각 인접 셀의 개수에 1개 더한거
```

- 입력 값

```
3
1 0 0
0 1 1
1 1 0
```

```java
using namespace std;

int k;
int arr[100][100];
bool visited[100][100];

int pointX[] = {0, 1, 1, 1, 0, -1, -1, -1};
int pointY[] = {-1, -1, 0, 1, 1, 1, 0, -1};

int countCells(int x, int y) {
    if (x < 0 || y < 0 || y > k || x > k) {
        return 0;
    } else if (arr[x][y] == 0 || visited[x][y]) {
        return 0;
    } else {
        visited[x][y] = true;
        int counting = 1;
        for(int i = 0; i < 8; i++) {
            int temp = countCells(x + pointX[i], y + pointY[i]);
            counting += temp;
        }
        return counting;
    }
}


int main(int argc, const char * argv[]) {
    int startX, startY;

    cin>>k;
    cin>>startX>>startY;
    for(int i = 0; i<k; i++) {
        for (int j = 0; j < k; j++) {
            cin>>arr[i][j];
        }
    }

    cout<<countCells(startY,startX)<<endl;

    return 0;
}

```
