# Quick sort

평균적으로 O(nlogn) 이 수행된다. 최악의 경우 O(n^2) 수행된다. 커다란 문제를 일정한 크기의 작은 문제로 쪼갠다.(DNC, 분할정복) 그리고 나중에 이것들을 다시 하나로 모으기 때문에 `nlogn`이 소요된다. 만약 나눌 때마다 절반씩 분할될 경우 평균 수행 시간을 가진다.
하지만 나눌 때마다 1개와 나머지로 분할 될 경우 n^2 시간을 가진다.

## HOW TO WORK

1. 주어진 데이터 에서 임의의 원소를 `pivot`이라 한다.
2. pivot을 기준으로
  - pivot 앞 : pivot 보다 작은 데이터
  - pivot 뒤 : pivot 보다 큰 데이터

분할과정을 거친다. 분할이 종료된 뒤 pivot의 위치가 결정된다. 이것을 분할 정복 알고리즘이라고 한다. 

- 1,2의 과정을 재귀 수행한다. pivot이 선택되어 분할이 이뤄지면 고정되는 값이 생성되어 언젠가 알고리즘이 종료된다.

## Code

```C

quickSort(int start, int end, int arr[]) {

  // 퀵정렬 재귀수행시 필요한 기존 start와 end값을 따로 저장
  int l_hold = start;
  int r_hold = end;
  int pivot  = arr[start]; // 0번쨰 원소를 피봇으로 선택

  while(left < right) {
    while(left < right && arr[right] > pivot) right--;

    if (left != right) {
      arr[left] = arr[right]
    }

    while(left < right && arr[left] < pivot) left++;

    if (left != right) {
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
