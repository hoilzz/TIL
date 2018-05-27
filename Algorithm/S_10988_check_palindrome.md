# check palindrome
`이효리`는 거꾸로 해도 `이효리` 인것처럼 거꾸로 해도 같은 문자열인지 판별하는 것

## 개념

`char *str = "xxyxx"`가 있다.
- 팰린드롬이 되려면 양 끝 값(`[0]`, `[strlen(str)] - 1`)이 같아야한다.
- 양 끝값의 인덱스는 각각 1씩 증가, 감소하며, 하나라도 다를시 팰린드롬이 아니다.

## how to work
1. 문자열 길이를 구한다.
2. 반복문을 `문자열 길이 * 1/2` 만큼 수행
  - `start = 0`, `end = strlen(str) - 1`
  - `str[start] != str[end]`일 경우 수행 멈춤
  - `start ++, end--`
3. 2번 과정을 반복하며 수행 멈출시 팰린드롬 ㄴㄴ해

check_palindrome.cpp
```C
#include <iostream>
#include <stdio.h>
#include <string.h>

int main() {

    char buf[101];
    int len, result = 1;

    scanf("%s", buf);

    len = strlen(buf);

    for (int i = 0; i < len/2; i+=1) {
        if(buf[i] != buf[len - (i + 1)]) {
            result = 0;
            break;
        }
    }
    printf("%d\n", result);

    return 0;

}
```



## debug
- `strlen(char * str)`은 `<string.h>`에 구현되어있다.
