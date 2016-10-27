# 1912번 연속합
[연속 합](https://www.acmicpc.net/problem/1912)

## 내가 생각한 것
- 기준 값 : 배열 끝(size)의 값부터 인덱스를 -1씩 감소시키며 기준 값 설정
- 기준 값부터 배열 끝(size) 까지 비교

틀린것.c
```C
for(int i = size-2; i >= 0; i-=1)
{
    if (nums[i] > max) {
        max = nums[i];
    }

    sums[i] = nums[i] + max;

    if(sums[i] > max)
    {
        if (sums[i+1] + nums[i] > max ) max = nums[i] + sums[i+1];

    }
    sums[i] = sums[i+1] + nums[i];
    for(int j = i+1; j < size; j+=1)
    {
        sums[j] = nums[j];
        sums[j] += sums[j-1];
        if(sums[j] > max)
        {
            max = sums[j];
        }
    }
}
```

### 문제점
- `n^2`의 시간 소요
- 또한 DP의 중요한 겹치는 부분문제를 n번만큼 실행
- 연속합의 개념 분류화 하는 것을 못함
- 연속이라는 개념에 대해 깊게 생각하지 못함
- **`D[i]`(`A[i]`)**
- 1개 인덱스를 지나갈 때마다 최대 연속합 판단할 수 있을거라 생각
  - 즉, 검사된 인덱스는 더이상 조사 안해도 된다고 착각..

### 해결책
- 개념화 하는 것이 어렵다면 **결과값들을 분류화하는 것도 고려**
- 연속은 끊기거나 이어지거나..
<hr>

## 개념
- `D[i] = i번째 수로 끝나는 가장 큰 연속합`
  + i번째 수에게 가능한 경우
  1. i번째 수의 연속합에 포함되는 경우 : i-1번째 수의 연속합에 포함되는 경우
  2. 새로운 연속합을 시작하는 경우 : 새로운 연속합을 시작하는 경우
- **`D[i]`** 를 완성 후 다시 비교하여 최대값 구함
두 값 중 어떤 값이 `D[i]`에 들어갈까?
```C
D[i] = max(D[i-1] + num[i], num[i])
```

정답.c
```C
int main() {
    int size, nums[100001], sums[100001], max = 0;

    scanf("%d", &size);

    for (int i = 0; i < size; i+=1)
    {
        scanf("%d", &nums[i]);
    }

    sums[0] = nums[0];

    for (int i = 1; i< size; i+=1)
    {
        if(nums[i] + sums[i-1] > nums[i])
        {
            sums[i] = nums[i] + sums[i-1];
        }
        else
        {
            sums[i] = nums[i];
        }
    }
}
```
