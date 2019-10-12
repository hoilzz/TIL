# 보글 게임

5x5 크기의 알파벳 격자에서 상하좌우/대각선으로 인접한 칸들의 글자들을 이어서 단어를 찾아내는 게임이다. 주어진 칸에서 시작해서 특정 단어를 찾을 수 있는지 확인하는 문제다. 

hasWord(y,x,word)=보글 게임판의 (y,x)에서 시작하는 단어 word의 존재여부를 반환한다.

이 문제의 가장 까다로운 점은 다음 글자가 될 수 있는 칸이 여러 개 있을 때 이 중 어느 글자를 선택해야 할지 미리 알 수 없다는 것이다. 간단한 방법은 완전 탐색을 이용해, 단어를 찾아낼 떄까지 모든 인접한 칸을 시도하는 것이다. 

## 문제의 분할

**hasWord()가 하는 일을 가장 자연스럽게 조각내는 방법은 각 글자를 하나의 조각으로 만드는 것이다.** 함수 호출시 단어의 시작 위치를 정해 주기 때문에 문제의 조각들 중 첫 번째 글자가 해당 조각을 간단하게 해결할 수 있다. 

## 기저 사례의 선택

더 이상의 탐색 없이 간단히 답을 낼 수 있는 다음의 경우들이 기저 사례다.

- y,x에 있는 글자가 원하는 단어의 첫글자가 아닌 경우 실패
- (1번 경우가 아닐 경우) 원하는 단어가 한글자인 경우 무조건 성공

```C
const int dx[8] = [-1,-1,-1,1,1,1,0,0];
const int dy[8] = [-1,0,1,-1,0,1,-1,1];

bool hasWord(int y, int x, const string& word){
  if(!inRange(y,x)) return false;

  if(board[y][x] != word[0]) return false;

  if(word.size() == 1) return true;

  for(int direction = 0; direction < 8; ++direction){
    int nextY = y + dy[direction], nextX = x + dx[direction];

    if(hasWord(nextY, nextX, word.substr(1))){
      return true;
    }
  }
  return false;
}
```

## 오답노트

```
int wordList = {
    {'W', 'B', 'A'}
}...

int moveableLocationX = {0, 1, 1, 1, 0, -1, -1, -1};
int moveableLocationY = {-1, -1, 0, 1, 1, 1, 0, -1};

int wordLocation = {}

findWord(int x, int y, word) {
    
    if(word[0] == wordList[x][y]) {
        return true;
    }

    for(int i = 0; i<8; i++) {
        int newX = x + moveableLocationX[i], newY = y = moveableLocation[i];
        if(findWord(newX, newY, word.substr(1));
    }
}
```