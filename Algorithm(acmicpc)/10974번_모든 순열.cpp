//
// https://www.acmicpc.net/problem/10974
//
//
//  main.cpp
//  AllPermutation_10974
//
//  Created by 정호일 on 2016. 6. 6..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;

int arrNum[9];

bool nextPermutation(int len)
{
    int changedBegin = -1, changedEnd = 0;
    for (int i = 1; i<len;i++)
    {
        if (arrNum[i-1] < arrNum[i]) changedBegin = i-1;
    }
    if (changedBegin == -1) return false;

    for (int i = changedBegin+1; i<len;i++)
    {
        if(arrNum[changedBegin] < arrNum[i]) changedEnd = i;
    }
    swap(arrNum[changedBegin], arrNum[changedEnd]);
    int lastIndex = len-1;
    while(changedBegin++ < lastIndex )
    {
        swap(arrNum[changedBegin], arrNum[lastIndex--]);
    }

    return true;
}

int main() {

    int arrLen;

    scanf("%d", &arrLen);

    for (int i = 0; i< arrLen; i++) arrNum[i] = i+1;
    for (int i = 0; i< arrLen; i++) printf("%d ", arrNum[i]);
    printf("\n");
    while(nextPermutation(arrLen) == true)
    {
        for (int i = 0; i< arrLen; i++) printf("%d ", arrNum[i]);
        printf("\n");
    }








    return 0;
}
