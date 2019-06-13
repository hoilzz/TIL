# 선택 정렬

데이터 리스트에서 가장 작은 것 혹은 큰 것을 선택하여 가장 앞 혹은 뒤로 보내는 작업을 반복한다.

## concepts

선택정렬은 swap 횟수를 줄인 버블 정렬 개선안이다.

버블정렬은 왼쪽값과 오른쪽 값을 비교하여 오른쪽에 있는 값보다 크면 자리를 바꿔가며 이동한다. 반면에 선택정렬은 최대값을 찾은 뒤에 정해진 위치로 보낸다. 비교 횟수는 버블과 동일하게 `O(n^2)`을 갖지만 swap을 버블정렬보다 덜하게 되므로 더 효율적이다.

## how to work

1. 주어진 리스트의 min 값을 찾는다.
2. 그 값을 맨 앞의 값과 swap 한다.
3. 맨 처음 위치를 뺴고 1,2번을 다시 진행한다.

## 코드

```C
void selectionSort(int arr[], int len) {

    int tempIdx;

    for(int i = 0; i < len; i++) {
            int max = arr[i];
        for (int j = 0; j < len - i; j++) {
            if (max > arr[j]) {
                max = arr[j];
                arr[j] = arr[i];
                arr[i] = max;
            }
        }
    }
}
```

## 시간 복잡도

`O(n^2)`

## summary

- 선택해서 min 값 찾고, 맨 앞으로 보내기,
- 맨 앞의 값 제외하고, 다시 min 찾아서 맨앞으로 보내기 반복
