# KMP 알고리즘

기존 문자열 매칭 방식 `오토마타`의 문제점을 극복하기 위해 만들었다.

KMP 알고리즘의 가장 중요한 요소는 `실패 함수` 작성이다.

검색한 문자열에 대한 `실패 함수`를 작성하여

검색 중 불일치가 발견되었을 때, **앞의 일치한 요소들에 대한 재참조를 최대한 줄이는 것**이다.

실패 함수 F는 검색할 문자열 P를 중심으로 작성한다.

`F(i)`는 P(0)~P(i)의 문자열에서 접미사와 일치하는 `최장접두사의 끝 위치`, 단 `최장접두사 != 전체문자열`로 정의된다.

---

실패함수 적용방법을 알아보자.

```
ABCABDABCABC 		// 기존 문자열 (str)
ABCABDABCABE       //  비교할 문자열 (pattern)
```


먼저, 문자열 비교시 앞의 문자열이 일치하다 불일치 하는 곳이 발견됐다.

각 문자열의 마지막 인덱스 `C`와 `E`다.

마지막 인덱스가 다르다는 뜻은 그보다 앞쪽에 있는 문자열은 모두 같다는 의미다.

이 때, 앞부분을 다시 참조하는 것은 시간 낭비다.

예를 들어 다음과 같이 비교하는 것은 낭비다.

```
0 1 2 3 4 5 6 7 8 9 10 11
A B C A B D A B C A B  C 		// 기존 문자열 (str)
  A B C A B D A B C A  B  E       //  비교할 문자열 (pattern)
```

왜냐하면 우리는 10번째 인덱스까지 비교하며, 10번째 인덱스까지는 2개 문자열이 같다는 것을 알고 있다.

즉, 비교할 필요가 없다. str의 11번째 인덱스부터 비교하면된다.

따라서 재참조를 줄이기 위해 다음과 같이 비교해야 한다.

```
0 1 2 3 4 5 6 7 8 9 10 11
A B C A B D A B C A B  C 		// 기존 문자열 (str)
            A B C A B  D A B C A  B  E       //  비교할 문자열 (pattern)
```

C와 D는 다르다.

```
0 1 2 3 4 5 6 7 8 9 10 11
A B C A B D A B C A B  C 		// 기존 문자열 (str)
            		   A B C A B  D A B C A  B  E       //  비교할 문자열 (pattern)
```
결국 처음부터 다시 비교한다.


```C
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

vector <int> getPi(string p){
    int len = p.size();
    int j = 0; vector <int> pi(len, 0);

    for (int i = 1; i<len; i++){
        while(j > 0 && p[i] != p[j]) {
            j = pi[j-1];
        }
        if(p[i] == p[j]){
            pi[i] = ++j;
        }
    }
    return pi;
}

void KMP(string s, string p){
    vector <int> pattern = getPi(p);

    vector <int> ptnIdx; int j = 0;

    for (int i = 0; i<s.size(); i++){
        while(j>0 && s[i] != p[j]){
            j = pattern[j-1];
        }
        if(s[i] == p[j]){
            if(j==p.size()-1) {
                ptnIdx.push_back(i-j+1);
                j = pattern[j];
            }
            else{
                j++;
            }
        }
    }
    int ptnIdxSize = ptnIdx.size();

    printf("%d\n", ptnIdxSize);

    for(int i = 0; i<ptnIdxSize; i++){
        printf("%d\n", ptnIdx[i]);
    }
}

int main(){
    string s,p;
    getline(cin, s);
    getline(cin, p);
    KMP(s,p);
}
```

함수는 2가지가 사용되었다.

패턴을 찾을 문자열에서 P를 구하기 위한 `getPi()`와 `KMP()`이다.


while문에서 `s[i] = 'C'` 와 `p[j] = 'E'`를 비교한다.

while문의 조건을 만족하기 때문에, `j = pi[j-1]` 을 실행한다.

`pi[j-1]`은 마지막 패턴이 매칭된 곳의 다음 index를 가리킨다.

다음 index에서, `s[i] != p[j]` 이다. 다시 반복한다.

이것으로 재참조를 감소시킬 수 있다.


개인적으로,

```C
whlie(j>0 & s[i] != p[j])
j = p[j-1];
```

이 문장을 이해하기 힘들었는데, 아래 참조된 링크를 보면 쉽게 이해할 수 있다.


## summary

텍스트내(본문)에서 특정 문자열, 패턴("테이프")를 찾는 것을 문자열 검색이라고 부릅니다.
이 문자열 검색은 어떤 방식으로 구현되는걸까요?

많은 문자를 가진 본문에서 특정 문자열을 찾는 것을 문자열 검색이라고 한다.

이 검색은 KMP 알고리즘을 이용하면 기존의 `O(M*N)` 방식을 `O(M+N)`으로 개선할 수 있다.


## 참조

[http://bowbowbow.tistory.com/6](http://bowbowbow.tistory.com/6) 설명 넘나 잘하셨다..
