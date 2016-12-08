# 버블소트
인접 원소를 비교하여 더 `큰 원소`를 뒤로 보내는 방식

## how to work
1. `i(=0)`부터 끝까지 인접 원소를 비교
2. `i`가 `i+1`
  - 보다 크면 `Swap`
  - 작으면 그대로
3. 1,2를 끝까지 반복
4. 3 종료시 이 원소의 가장 큰 값과 그 위치를 찾을 수 있음
5. 1~4를 원소 길이만큼 반복



```C
void bubbleSort(int arr[], int len) {
    int right = len;
    for(int i = 0; i < len; i++) {
        for (int j = 1; j < right - i; j++){

            if (arr[j-1] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1]   = temp;
            }

        }
    }
}

void main() {
    int len, arr[10];
    scanf("%d", &len);
    for(int i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }
    bubbleSort(arr, len);
}
```

## 시간복잡도
`O(n^2)` 개느림

## Summary
- 가장 큰 값을 인접 두 원소끼리 비교 및 찾으면서 범위를 좁혀가기

## 참고
