//
// https://www.acmicpc.net/problem/11655
//
//
//  main.cpp
//  ROT13_11655
//
//  Created by 정호일 on 2016. 4. 20..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int main(int argc, const char * argv[]) {

    char input_str[100], result_char;
    gets(input_str);

    for(int i = 0; input_str[i]; i++)
    {
        if (input_str[i] >= 'a' && input_str[i] <= 'z') input_str[i] = (input_str[i] - 'a' + 13 ) % 26 + 'a';
        else if (input_str[i] >= 'A' && input_str[i] <= 'Z') input_str[i] = (input_str[i] - 'A' + 13 ) % 26 + 'A';
        printf("%c", input_str[i]);
    }

    printf("\n");



    return 0;
}
//        input_str[i] += 13;
//        if (input_str[i] >= 'A' && input_str[i] <= 'M') input_str[i] += 13;
//        else if (input_str[i] > 'M' && input_str[i] <= 'Z') input_str[i] += 13-26;
//        else if (input_str[i] >= 'a' && input_str[i] <= 'm') input_str[i] += 13;
//        else if (input_str[i] > 'm' && input_str[i] <= 'z') input_str[i] += 13-26;
//
