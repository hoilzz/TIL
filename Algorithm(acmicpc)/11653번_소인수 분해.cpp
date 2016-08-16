//
// https://www.acmicpc.net/problem/11653
//
//  main.cpp
//  integetFactorization_11653
//
//  Created by 정호일 on 2016. 4. 3..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int main() {
    int inputNum;
    scanf("%d", &inputNum);
    for (int i = 2; i*i<=inputNum; i++)
    {
        while (!(inputNum % i))
        {
            printf("%d\n", i);
            inputNum = inputNum / i;
        }
    }
    if (inputNum > 1) printf("%d\n", inputNum);

    return 0;
}
