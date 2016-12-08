//
// https://www.acmicpc.net/problem/1978
//
//  main.cpp
//  searchPrimeNumber_1978
//
//  Created by 정호일 on 2016. 3. 30..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int main() {

    int inputNum, inputArr[101], numberOfPrime = 0;
    scanf("%d", &inputNum);
    numberOfPrime = inputNum;
    for (int i=0;i<inputNum;i++)        scanf("%d", &inputArr[i]);

    while (--inputNum>=0)
    {
        if (inputArr[inputNum] == 1) numberOfPrime--;
        for (int i = 2; i*i<=inputArr[inputNum]; i++)
        {
            if ( inputArr[inputNum] % i  == 0)
            {
                numberOfPrime--;
                break;
            }
        }
    }
    printf("%d\n", numberOfPrime);


    return 0;
}
