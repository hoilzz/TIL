# 가장 긴 증가하는 수열 (틀림)
[가장 긴 증가하는 수열](https://www.acmicpc.net/problem/11053)

주어진 수열에서 가장 긴 증가하는 수열의 길이를 찾는 문제다.

이 문제는 **가장 긴 증가하는 수열을 개념으로 정의하는 것** 이 중요하다.

## 가장 긴 증가하는 수열
- `D[i] = A[1]...A[i]`의 수열
- **가장 긴 부분 수열** `A[?]...A[j], A[i]` 일 때 **겹치는 부분 문제는?**
  - `A[?]...A[j]`는 `D[j]`로 나타낼 수 있다.
- `A[j]`와 `A[i]`의 관계
  - `A[j] < A[i]` : 증가하는 부분 수열이기 때문에

```C
void getLongestIncreasingSequence()
{
    for (int i = 0; i < size; i+=1)
    {
        memo[i] = 1;

        for (int j = 0; j< i; j+=1)
        {
            if (nums[j] < nums[i] && memo[i] < memo[j]+1) {
                memo[i] = memo[j] + 1;
            }

        }
    }
    for (int i = 0; i < size; i+=1) {
        if (max < memo[i]) {
            max = memo[i];
        }
    }
    printf("%d\n", max);
}
```
