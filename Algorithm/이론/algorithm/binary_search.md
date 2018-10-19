# Binary Search

- 정렬된 리스트에서 특정값 위치 찾을 수 있는 **`고속 탐색 알고리즘`**
- 이진탐색 이름은 탐색 범위를 1/2 씩 줄여나가기 때문이다.

## How to Work

1. 데이터의 중간 값을 선택
2. 중간 값과 target(찾고자 하는 값) 비교

- `target < 중간 값` : 중간 값 기준 `왼편`에서 검색 수행 ( `end = mid - 1` )
- `target > 중간 값` : 중간 값 기준 `오른편`에서 검색 수행 ( `start = mid + 1` )

3. 위치를 찾을 수 있을 때까지 `1,2`를 반복

- until begin != end

## 장단점

- 단점
  - 검색 원리상 정렬된 리스트에만 사용
- 장점

  - 검색 반복시 목표값 찾을 확률 2 배, 속도 빠른 장점

- 시간복잡도

## 언제 사용할까

1. 특정 값의 위치를 탐색 할 때

- ex. `점수가 929.21인 학생을 찾으시오` : `정렬 + 이진 탐색`

binarySearch.cpp

```python
def find(self, val):
    if (self.findNode(self.root, val) is False):
        return False
    else:
        return True

def findNode(self, currentNode, val):
    if (currentNode is None):
        return False
    elif (val == currentNode.val):
        return currentNode
    elif (val < currentNode.val):
        return self.findNode(currentNode.leftChild, val)
    else:
        return self.findNode(currentNode.rightChild, val)
```

## 시간복잡도

한 번 비교가 이뤄질 때마다 범위는 1/2 로 줄어든다. 데이터 크기가 n 일 때, 반복횟수가 k 라면 `n * (1/2)^k = 1`일 때 `k = log n`

### 잘못한 거

### 1. 종료 시점, 언제까지 수행해야 하나?

- 나는 **`특정 값 위치 찾을 때 종료`** 로 했기 때문에 `while (begin == end)`로 생각
- 위의 **`문제점`**
  - `특정 값이 없을 때`를 골라내지 못한다.
  - 즉 **`끝까지 탐색하지 않은 것`**

#### 개선하기 위해서

- 목표를 확인할 수 있을 때까지, 목표(끝까지 탐색할 때까지)를 정확히 생각하기
- **`목표를 수행할 수 없을 때까지`**
- 목표에 대한 문제점이 발생시, 문제점 해결을 위해 목표를 수정 및 다시 생각했어야 했다.

#### summary

- 특정 값 위치 찾을 때까지 -> 특정 값의 위치를 찾을 수 있다 + 특정 값의 위치를 찾을 수 없다.
