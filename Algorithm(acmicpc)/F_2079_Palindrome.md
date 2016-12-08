# Palindrome

```C
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

string buf;

int isPal(int start, int end) {
    if (start >= end) return true;
    else if(buf[start] == buf[end]) {
        return isPal(start+1, end-1);
    }
    else return false;
}

int main() {

    int numOfPalindrome = 0;

    cin>>buf;

    int len = buf.length();

    for (int i = 0 ; i < len; i++) {
        for (int j = len-1; j >= i; j--) {
            if(buf[i] == buf[j]) {
                if (isPal(i+1, j-1)) {
                    i = j;
                    numOfPalindrome += 1;
                    break;
                }
            }
        }
    }

    printf("%d\n", numOfPalindrome);



    return 0;
}
```
