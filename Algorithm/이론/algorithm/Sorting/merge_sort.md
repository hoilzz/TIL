# 머지 소트
전체 원소를 **하나의 단위로 분할**한 후 분할한 원소를 **다시 병합**하는 정렬 방식.

## concepts

divide and conquer를 이용한 정렬 방식이다. 데이터를 쪼갤 수 있을 때까지 쪼개고, 둘 씩 크기를 비교해 정렬한다. 더이상 합칠 array가 없을 때까지 반복한다.

N개의 데이터가 있을 때, 절반씩 쪼개기 때문에(divide, n/2)

## how to work
1. 리스트의 길이가 1이하면 정렬된 것으로 본다. 그렇지 않은 경우

2. 정렬되지 않은 리스트를 절반으로 잘라 분할한다.

3. 분할된 리스트 크기가 2 이하가 될 때까지 분할한다.
  - 크기가 2일 경우 두 원소를 비교하여 swap한다.

4. 각 분할된 리스트를 합병 및 정렬한다.

## code
```C
#include <iostream>
#include <stdio.h>
int a[1000000];
int b[1000000];
void swap(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}
void merge_sort(int start, int end) {
    if (start == end) {
        return;
    } else if (start + 1 == end) {
        if (a[start] > a[end]) {
            swap(a[start], a[end]);
        }
        return;
    }
    int mid = (start+end)/2;
    merge_sort(start, mid);
    merge_sort(mid+1, end);
    int i = start;
    int j = mid+1;
    int k = 0;

    // 임시 저장소에 저장하기.
    while (i <= mid && j <= end) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    // 위 정렬에서 반영 안된 것들 반영하기.
    while (i <= mid) {
        b[k++] = a[i++];
    }
    while (j <= end) {
        b[k++] = a[j++];
    }

    // 임시 저장소에 있는 것 실제 저장소에 반영하기
    for (int i=start; i<=end; i++) {
        a[i] = b[i-start];
    }
}
int main() {
    int n;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    merge_sort(0, n-1);
    for (int i=0; i<n; i++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
```

## 시간 복잡도

분할시 `log n`번 호출, 병합시 `n`번 호출 = `n log n`

## 회고

1. 크기가 2이하로 분할된 리스트들은 미리 정렬 되기 때문에 아래 병합 정렬에서 무한 루프를 돈다.
  - 아래 코드에 의해 크기가 2로 분할된 리스트는 미리 정렬된다.

  ```C
  else if (start + 1 == end) {
    if (a[start] > a[end]) {
        swap(a[start], a[end]);
    }
    return;
  }
  ```

  - 병합정렬을 하지 않기 위해 **`return`** 을 추가

2. 크기가 2이하로 분할된 리스트들을 병합 정렬 후, 병합되지 않은 리스트 간 병합 정렬시 정렬이 제대로 되지 않음
  - 병합 정렬 후, 배열에 반영하지 않음.
  - **배열 변수를 새로 만들어**, 그곳에 정렬된 배열을 만들고 기존 배열에 할당하는 것으로 해결


## summary
- 원소들을 하나 혹은 두개 원소 단위로 분할 후, 병합 정렬을 반복

