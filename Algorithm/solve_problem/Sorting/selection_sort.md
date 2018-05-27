# 선택 정렬
데이터 리스트에서 가장 작은 것 혹은 큰 것을 선택하여 가장 앞 혹은 뒤로 보내는 작업을 반복

## how to work
1. 주어진 리스트의 min 값을 찾는다.
2. 그 값을 맨 앞의 값과 swap 한다.
3. 맨 처음 위치를 뺴고 1,2번을 다시 진행한다.


## 코드

```C
void selectionSort(int arr[], int len) {

    int tempIdx;

    for(int i = 0; i < len; i++) {
            int min = arr[i];
        for (int j = i+1; j < len; j++) {
            if (min > arr[j]) {
                min = arr[j];
                arr[j] = arr[i];
                arr[i] = min;
            }
        }
    }
}
```

## 시간 복잡도
`O(n^2)`


## summary
- 버블소트 반대버전 같다.
- 선택해서 min 값 찾고, 맨 앞으로 보내기,
- 맨 앞의 값 제외하고, 다시 min 찾아서 맨앞으로 보내기 반복
