//
// https://www.acmicpc.net/problem/10815
//
//
//  main.cpp
//  10815_NumberCard
//
//  Created by 정호일 on 2016. 6. 7..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int answerArr[500001];
int questionArr[500001];
int questionIndex = 0;//, resultIndex = 0;
//int resultNum[101];

bool binarySearch(int len)
{
    int left = 0, right = len-1, tempNum = questionArr[questionIndex], middle;

    while(left <= right)
    {
        middle = (left+right)/2;

        if(answerArr[middle] == tempNum)   return true;//resultNum[resultIndex] = 1;
        else if (answerArr[middle] < tempNum)   left = middle+1;
        else if (answerArr[middle] > tempNum)   right = middle -1;
    }
    return false;

}

int main() {

    int answerLen, questionLen;
    scanf("%d", &answerLen);

    for (int i = 0; i<answerLen; i++)   scanf("%d", &answerArr[i]);

    scanf("%d", &questionLen);
    for (int i = 0; i<questionLen;i++)  scanf("%d", &questionArr[i]);

    sort(answerArr, answerArr+answerLen);

    while(questionIndex < questionLen)
    {
        if ( binarySearch(answerLen) == true) printf("1 ");
        else    printf("0 ");
        questionIndex +=1;
    }
    printf("\n");




    return 0;
}
