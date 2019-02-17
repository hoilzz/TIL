# X-leet-394-decode-string

일단 이 문제는 1시간 반만에 풀었다. 걍 틀렸다고 생각한다

특정 조건에 따라 string을 디코딩 하는 문제다.

```
2[abc]ggg -> abcabcggg
2[a3[bbb]] -> abbbabbbabbb
2[a]3[b] -> aabbb
```

위와 같이 숫자[X] 와 같이 구성된 문자열은 숫자만큼 X문자열을 반복하는 거다. 숫자는 정수다.

```C
int recursive(string s, int printIdx, string& result) {
    int lastIdx = 0;
    int k = printIdx;
    int t = printIdx;
    string temp = "";
    int iterSize;
//
//    while (s[i] >= ' 0 ' && s[i] <= ' 9 ' ) {
//        Cnt = cnt * 10 + s[i++] - ' 0 ' ;
//    }

    // iteration 숫자 찾기
    // 숫자가 아니면 스트링 끝까지 || 숫자를 만나거나 ||
    if(s[printIdx] < '0' || s[printIdx] > '9') {
        int idx = printIdx;
        while(true) {
            if(idx >= s.length() || s[idx] > '9' || s[idx] < '0') {
                return idx;
            }
            result += s[idx];
        }
    }
    // 숫자면 ]일 때까지 찾고
    while(true) {
        if(s[t] == '[') {
            break;
        }
        temp += s[t];
        t += 1;
    }
    cout<<"temp"<<temp<<endl;
    iterSize = stoi(temp);

    for(int i = 0; i< iterSize; i++) {
        k = printIdx + t - 1;
        while(true) {
            if(s[k] >= '0' && s[k] <= '9') {

            } else if(s[k] == '[') {
                lastIdx = recursive(s, k + 1, result);
                k = lastIdx;
            } else if(s[k] == ']' || k>= s.length()) {

                break;
            } else {
                result += s[k];
//                cout<<s[k];
            }
            k += 1;
        }
    }

    if(k < lastIdx) {
        return lastIdx;
    }
    return k;
}
```

이거 하다가 점점 코드가 산으로 가는거 같아서.. 포기하고 답을 봤다.

일단 재귀에 넘기려고 한 정보는 
1. string s : 전체 스트링
2. int printIdx : 출력이 시작되는 index
3. string result: 결과 string

재귀함수의 task는 result에 string 계속 누적시키기.
반환값은 마지막으로 가리킨 index를 반환.

---

_2번째 시도_

```C
string decodeString(string s) {
    int index = 0;
    string result = "";
//    return decode(s, index);
    decode(index, )
    return result;
}

void decode(int &index, int iterSize, string s, string result) {
    for(int k = 0; k<iterSize; k+=1) {
        int i = index;
        
        while(index<s.size() || s[i] != ']') {
            // 문자면
            if (s[i] < '0' || s[i] > '9') {
                result += s[i];
            } else {
                int nextIter = 0;
                while(s[i] >= '0' && s[i] <= '9') {
                    nextIter = nextIter * 10 + s[i] - '0';
                }
                i++;
                decode(i, nextIter, s, result);
            }
        }
        
    }
}
```

- iterSize를 전달해주려다보니..
  - string의 첫번째값이 숫자라는 보장 없음
  - 숫자여도 정수이기 때문에 2자리 수 이상일 수 있음
  - 로직을 두번 반복해야됨.
- 결국엔 iterSize를 재귀함수에서 호출하지 않는 편이 나았다.
  - 재귀함수의 단위가 스트링만 result에 저장.
  - 재귀를 몇번 호출할지에 대해서는 인자로 받지 않고 재귀함수 내에서 처리.

_2번째 시도_수정_

```C
void decode(int &index, string s, string& result) {
    
    int i = index;
    
    // or가 아닌 and인 이유는 종료 조건이 두가지 조건을 모두 충족해야함. ]는 스트링을 모두 탐색하기 전에 만날 수 있기 때문.
    while(index<s.size() && s[i] != ']') {
        // 문자면
        if (s[i] < '0' || s[i] > '9') {
            result += s[i];
        } else {
            int nextIter = 0;
            while(s[i] >= '0' && s[i] <= '9') {
                nextIter = nextIter * 10 + s[i] - '0';
                i+=1;
            }
            i++;
            for(int j = 0; j<nextIter; j++) {
                decode(i, s, result);
            }
            
        }
        i+=1;
    }
}
```

- decode 재귀함수 호출시, index값을 초기화 해줘야함
- decode 순환함수에서 동일한 작업을 nextIter만큼함.
- 걍 string을 리턴받아서 result에 반복문돌려서 붙여주는게 효율적이고 로직(index 초기화) 추가안해도됨.

_3번째 시도_수정__

```C
string decode(int &i, string s) {
    string result = "";
//    int i = index;
    
    // or가 아닌 and인 이유는 종료 조건이 두가지 조건을 모두 충족해야함. ]는 스트링을 모두 탐색하기 전에 만날 수 있기 때문.
    int n = (int) s.length();
    while(i < n && s[i] != ']') {
        cout<<n<<endl;
        // 문자면
        if (s[i] < '0' || s[i] > '9') {
            result += s[i];
            i+=1;
        } else {
            int nextIter = 0;
            while(s[i] >= '0' && s[i] <= '9') {
                nextIter = nextIter * 10 + s[i] - '0';
                i+=1;
            }
            i++;
            string temp = decode(i, s);
            i+=1;
            for(int j = 0; j<nextIter; j++) {
                result += temp;
            }
            
        }
    }
    return result;
}


string decodeString(string s) {
    int index = 0;
    return decode(index, s);
}
```

---

찾은 정답
```C
string decodeString(string s) {
    int index = 0;
    return decode(s, index);
}

string decode(string s, int index) {
    string result  "";
    int i = index;
    while(i < result.size() && s[i] != ']') {
        if (s[i] < '0' || s[i] > '9') {
            result += s[i++];
        } else {
            int cnt = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                cnt = cnt * 10 + s[i++] - '0';
            }
            i++;
            string temp = decode(s, i);
            i++;
            while (cnt-- > 0) {
                result += temp;
            }
        }
    }
    return result;

}
```

정답을 수도코드로 작성해보면

재귀함수는 
- string s : 입력받은 스트링
- int index : 시작 index
- return result: 출력되야할 스트링.

- task : s[i]가 ]거나 i가 입력받은 문자열 길이보다 커지면
  - 숫자가 아니면 result에 문자 추가
  - 숫자면
    - [ 만날 때까지 숫자 모아서 완성
    - 숫자 완성되면 
      - 문자열만 반환받아서
      - 반환받은 문자열을 숫자만큼 반복문 돌려서 result에 추가

## summary

- 재귀함수 호출 횟수를 재귀함수의 인자로 넣어줬는데(재귀함수의 task는 출력만해라 라고 정해서),
    - 이렇게 하게 될 경우 재귀 함수 첫 호출 때, 몇번 호출해야하는지 정해줘야한다.(재귀 호출 전, 재귀 함수 내부 이렇게 두곳에서 코드가 중복된다.)
- "100" 을 100으로 표현하기 위해 아래와 같은 코드를 순간적으로 생각했는데
    - stoi쓰자 걍

```C
while(s[i] >= '0' && s[i] <= '9') {
    nextIter = nextIter * 10 + s[i] - '0';
    i+=1;
}
```