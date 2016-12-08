//
//  https://www.acmicpc.net/problem/1850
//
//  main.cpp
//  GCD_practice2
//
//  Created by 정호일 on 2016. 6. 8..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <cmath>

//long long gcd(long long first, long long second)
int gcd (long long first, long long second)
{
    if (first%second == 0) return second;
    else    return gcd(second, first%second);
}

int main() {

    long long firstNum, secondNum;
    scanf("%lld %lld", &firstNum, &secondNum);

    int temp = gcd(firstNum, secondNum);
    for (int i = 0; i< temp; i++) printf("1");
    printf("\n");
    return 0;
}
