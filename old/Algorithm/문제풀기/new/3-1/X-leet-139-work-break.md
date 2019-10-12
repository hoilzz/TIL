# leet-139-word-break

1. string s : 단어
2. vector<string>& wordDict : 단어 리스트

s가 2번 단어 리스트로 분해될 수 있는지 여부에 대해 리턴.

2번 단어리스트는
- 1번 단어를 분해하기 위해 2번 단어 리스트를 여러번 사용 될 수 있고
- 중복된 단어를 포함할 수 없음

## 남들이 해결한 방법

일단 점화식을 세워보자.

- D[N] : N번째로 끝나는 단어의 분해 여부
- D[N-1] : N-1번째로 끝나는 단어의 분해 여부

- 이 때, D[N]은 (0,N), (1,N-1), (2,N-2), ...(N-1, N) 으로 분해될 수 있다. 그래서 D[N]을 다음과 같이 나타낼 수 있다.

```
D[N] = (D[N-i] && s.substr(i, N)이 wordDict에 있는 단어인지) (0<=i<=N)
```

이 점화식을 바탕으로 코드를 작성해보자.

```C
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.size() == 0) {
            return false;
        }

        vector<bool> endHere(s.size() + 1, false);
        endHere[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (endHere[j]) {
                    string word = s.substr(j, i - j);
                    // find는 wordDict begin~end 사이에 word가 있으면 첫번째 value를, 없으면 end를 리턴.
                    if (find(wordDict.begin(), wordDict.end(), word) != wordDict.end()) {
                        endHere[i] = true;
                        break;
                    }
                }
            }
        }
        return endHere[s.size()];
    }
};
```

### 시간복잡도

`O(n^2)`

### 공간복잡도

O(n)

## Summary

1. 점화식을 잘 세우자... 세워진 점화식에는 여러가지 경우의수가 있을 수 있다. 이 때, 2차원 배열의 매모이즈 공간을 필요로 할 수 있다. 이 문제는 어차피 word break가 가능 여부(true/false)를 구하기 때문에 1차원 배열만을 필요로 했다.

점화식에 대해 여러 경우의수가 있을 수 있음을 고려하자
