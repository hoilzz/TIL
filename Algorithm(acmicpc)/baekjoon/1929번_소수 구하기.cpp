//
//  https://www.acmicpc.net/problem/1929
//
//  main.cpp
//  find_prime_1929
//
//  Created by 정호일 on 2016. 3. 31..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int main() {
    int minX, maxY, primeArrIndex = -1;
    bool BlistOfNum[1000001];
    int primeArr[1000001];

    scanf("%d %d", &minX, &maxY);

    for (int j = 2; j <= maxY; j++)
    {
        // 왜 i*j<=maxY 냐?
        if (BlistOfNum[j] == false)
        {
            if (j >= minX) primeArr[++primeArrIndex] = j;
            for (int i = j*2; i <= maxY; i+=j)
            {
                // j의 배수를 찾아야함
                BlistOfNum[i] = true;
            }
        }
    }

    for (int i = 0; i<=primeArrIndex; i++)   printf("%d\n", primeArr[i]);

    return 0;
}
