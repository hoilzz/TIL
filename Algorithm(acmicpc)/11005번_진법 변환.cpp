//
// https://www.acmicpc.net/problem/11005
//
//
//  main.cpp
//  changeDisposition
//
//  Created by 정호일 on 2016. 6. 8..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remainder[1001];
long long beforeNum;
int disposition;
int rIndex = 0;

void changeDisposition()
{
    long long share = beforeNum;

    while( share >= disposition)
    {
        remainder[rIndex++] = share % disposition;
        share = share / disposition;
    }
    remainder[rIndex] = (int) share;
    for (int i = rIndex; i >= 0; i--)
    {
        if (remainder[i] < 10)        printf("%d", remainder[i]);
        else printf("%c", remainder[i] + 55);
    }


}

int main(int argc, const char * argv[]) {


    scanf("%lld %d", &beforeNum, &disposition);
    changeDisposition();

    printf("\n");


    return 0;
}
