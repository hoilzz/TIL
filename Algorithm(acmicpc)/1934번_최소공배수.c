//
// https://www.acmicpc.net/problem/1934
//
//  main.c
//  lcm_1934
//
//  Created by 정호일 on 2016. 3. 20..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <stdio.h>

int gcd(int x, int y)
{
    if (x%y == 0) return y;
    else return gcd(y, x%y);
}

int lcm(int x, int y, int gcdValue)
{
    return gcdValue*(x/gcdValue)*(y/gcdValue);
}

int main() {

    int x,y,gcdValue,iteration;
    scanf("%d", &iteration);
    for (int i = 0; i<iteration; i++)
    {
        scanf("%d %d", &x, &y);

        gcdValue = gcd(x,y);
        printf("%d\n", lcm(x,y,gcdValue));
    }

    return 0;
}
