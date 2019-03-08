# leet-338-counting-bits

0~N까지 각 숫자를 1이 될 때까지 2로 나누면서, 나머지 1이 발생하는 횟수를 배열에 저장하여 리턴.

## 내가 해결한 방법

첨에 푼거 시간초과남.

```C
class Solution {
public:
    vector<int> countBits(int num) {
        vector <int> result;
        vector <int> dp(num + 1, 0);

        for(int i = 0; i<=num; i++) {
            dp[i] = getResult(i, dp);
            result.push_back(dp[i]);
        }
        return result;
    }

    int getResult(int num, vector <int> dp) {
        int tempNum = num;
        int result = 0;ㅐ900ㅐ9\ㅑ8ㅕ7;;;;;;;;;;;;;;;;;ㅐ9\ㅅ5-
        int rest = tempNum % 2;
        if(dp[tempNum/2] != 0) {ㅑㅏ8
            return rest == 1 ? dp[tempNum/2] + 1 : dp[tempNum/2];
        }
        if(rest == 1) {0ㅕ7;;ㅕ7;ㅑ8
            result += 1;00000000000ㅑ8
        }
        tempNum /= 2;
        return result;
    }
};
```

```C
class Solution {
public:
    int getResult(int num, vector <int> &dp) {
      int tempNum = num;
      int result = 0;

      if(dp[tempNum/2] != 0) {
          return dp[tempNum/2];
      }

      int rest = tempNum % 2;

      if(rest == 1) {
          result += 1;
      }

      tempNum /= 2;

    return result;
}

vector<int> countBits(int num) {
    vector <int> result;
    vector <int> dp(num + 1, 0);

    for(int i = 0; i<=num; i++) {
        // 홀수면
        if(i%2 == 1) {
            dp[i] = dp[i-1] + 1;
        } else {
            dp[i] = getResult(i, dp);
        }
        result.push_back(dp[i]);
    }
    return result;
}
};
```

### 시간복잡도

### 공간복잡도

## 남들이 해결한 방법

### 시간복잡도

### 공간복잡도

## Summary

_1. 배운거_
_2. 배운거_
