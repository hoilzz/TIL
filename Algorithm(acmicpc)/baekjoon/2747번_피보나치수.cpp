//
//  https://www.acmicpc.net/problem/2747
//
//  main.cpp
//  fibonacci_2747
//
//  Created by 정호일 on 2016. 6. 5..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int memo [45];

int fibonacci(int num)
{
    if (num < 2) return num;
    else
    {
        if (memo[num]) return memo[num];
        memo[num] = fibonacci(num-1) + fibonacci(num-2);

    }
    return memo[num];
}

int main(int argc, const char * argv[]) {

    int num;
    scanf("%d", &num);
    printf("%d\n", fibonacci(num));

    return 0;
}
