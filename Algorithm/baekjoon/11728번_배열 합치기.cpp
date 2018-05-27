//
// https://www.acmicpc.net/problem/11728
//
//  main.cpp
//  11752_mergeArray
//
//  Created by 정호일 on 2016. 6. 7..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int firstArr[1000001];
int secondArr[1000001];
int mixedArr[2000003];

void mergeSort(int firstEnd, int secondEnd)
{
    int tempArr[2000003];
    //int mid = (start+end)/2;
    int i = 0, j = 0, tempIndex = 0;

    while( i < firstEnd && j < secondEnd )
    {
        if (firstArr[i] < secondArr[j]) tempArr[tempIndex++] = firstArr[i++];
        else    tempArr[tempIndex++] = secondArr[j++];
    }
    while ( i < firstEnd )   tempArr[tempIndex++] = firstArr[i++];
    while (j < secondEnd) tempArr[tempIndex++] = secondArr[j++];

    for (int i = 0; i<firstEnd+secondEnd; i++)
    {
        printf("%d ", tempArr[i]);
    }
    printf("\n");
}

int main() {

    int firstLen, secondLen, mixLen = 0, mixIndex = 0;
    scanf("%d %d", &firstLen, &secondLen);
    mixLen = firstLen + secondLen;

    for (int i = 0; i< firstLen; i++)   scanf("%d", &firstArr[i]);
    for (int i = 0; i< secondLen; i++)   scanf("%d", &secondArr[i]);

    /*for (; mixIndex < firstLen; mixIndex++)
    {
        mixedArr[mixIndex] = firstArr[mixIndex];
    }
    for (int i = 0; i < secondLen; i++)
    {
        mixedArr[mixIndex++] = secondArr[i];
    }*/

    mergeSort(firstLen, secondLen);

   /* for(int i = 0; i<mixIndex; i++)   printf("%d ", mixedArr[i]);
    printf("\n");*/

    return 0;
}
