//
// https://www.acmicpc.net/problem/1676
//
#include <iostream>
#include <stdio.h>

int main() {

    int inputNum, numberOfFive = 0, j=1, temp;
    for (scanf("%d", &inputNum); 5*j<= inputNum; j++)
    {
        temp = 5*j;
        while(((temp)%5) == 0)
        {
            temp = temp/5;
            numberOfFive++;
        }
    }
    printf("%d\n",numberOfFive);
    return 0;
}
