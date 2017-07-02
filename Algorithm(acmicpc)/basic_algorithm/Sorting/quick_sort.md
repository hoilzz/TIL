# Quick sort

## HOW TO WORK
1. 데이터 목록에서 임의의 원소 `피봇`을 고른다
2. 각 데이터들을 피봇과 비교한다. 피봇보다 작은 수는 피봇의 앞에, 피봇보다 큰 수는 피봇의 뒤로 오도록 한다. 필요할 경우 피봇은 움직일 수 있다.
3. 1,2의 과정을 재귀수행한다.

- 1,2의 분할과정, 이를 통해 피봇은 움직일 필요 없이 그 자리에 고정됨. 이를 `분할정복` 알고리즘이라고 함
- 3에서 피봇 선택 후, 분할 이뤄질 때마다 반드시 고정되는 값이 생성되므로 이 알고리즘은 반드시 끝난 다는 것을 보장할 수 있다.

## Code
구현 방법 중 별도의 버퍼를 필요로 하지 않는 `내부분할 퀵소트`를 이용

```C

quickSort(int start, int end, int arr[]) {

  // 퀵정렬 재귀수행시 필요한 기존 start와 end값을 따로 저장
  int l_hold = start;
  int r_hold = end;
  int pivot  = arr[start]; // 0번쨰 원소를 피봇으로 선택

  while(left < right) {
    while(left < right && arr[right] > pivot) right--;

    if (left < right) {
      arr[left] = arr[right]
    }

    while(left < right && arr[left] < pivot) left++;

    if (left < right) {
      arr[right] = arr[left];
      right--;
    }
  }

  // left와 right가 겹친 지점이 pivot의 고정 자리다.
  arr[left] = pivot;

  // 피벗을 고정 자리값으로 변경
  pivot = left;

  // pivot의 위치가 l_hold인 경우 pivot 왼쪽에 퀵소트 할 게 없음
  if (l_hold < pivot) quickSort(l_hold, pivot - 1, arr);

  // pivot의 위치가 r_hold인 경우 pivot 오른쪽에 퀵소트 할 게 없음
  if (r_hold > pivot) quickSort(pivot + 1, r_hold, arr);
}

main(){
  int arr = {3,8,0,2,1,4}
  quickSort(0, arr.strlen() - 1, arr)
}
```


## 시간 복잡도
평균적으로 `O(nlog n)`을 수행, 최악의 경우 `O(n^2)`

## Summary
1. pivot 선정하고
2. right(end) 부터 **pivot보다 작은 값을 찾을 때까지** 1씩 **왼쪽**으로 이동.
  - pivot보다 작은 값 발견시 `arr[left]`(pivot으로 초기화 됨)에 `arr[right]` 값 이동.
3. left(start) 부터 **pivot보다 큰 값 찾을 때까지** 1씩 **오른쪽** 이동
  - pivot보다 큰 값 발견시 `arr[right]`에 `arr[left]` 이동
- 2,3을 **until left < right** 까지 반복
4. **left >= right** 때 퀵소트 종료. `arr[left] = pivot`으로 할당하여 pivot의 고정 자리 값 찾기 완료
5. 만약 l_hold가 pivot보다 작으면, `quick(l_hold, pivot 자리 - 1)`를 재귀수행
6. 만약 r_hold가 pivot보다 크면 `quick(pivot자리 + 1, r_hold)`를 재귀수행
