//
//  https://www.acmicpc.net/problem/1924
//
//  main.c
//  test
//
//
//  Created by 정호일 on 2015. 12. 9..
//  Copyright © 2015년 정호일. All rights reserved.
//

#include <stdio.h>

int main() {

//입력이 주어진다. 입력은 최대 100줄로 이루어져 있고, 알파벳 소문자, 대문자, 공백, 숫자로만 이루어져 있다. 각 줄은 100글자를 넘지 않으며, 빈 줄은 주어지지 않는다. 또, 각 줄은 공백으로 시작하지 않고, 공백으로 끝나지 않는다.


//    char *s;1, 3, 5, 7, 8, 10, 12월은 31일까지, 4, 6, 9, 11월은 30일까지, 2월은 28

//    while (() < 100){
//    scanf("%[^\n]\n", s);
//    fgets(s, 100, stdin);
//    printf("%s\n",s);
//    }
    // 1,3,5,7,8,10,12를 위한 메서드
    // 2월을 위한 메서드
    // 4월을 위한 메서드


    // 2월 일 때,
    //

    int x,y;
    int sumOfMonth = 0;
    char* day;

    scanf("%d %d", &x, &y);

    for (int i = 1; i<=x; i++)
    {
        if (x >= 2)
        {
            sumOfMonth = sumOfMonth + dateOfMonth(i-1);
//            printf("%d월까지 합계 : %d\n", i-1, sumOfMonth);
        }
    }
    sumOfMonth += y;
//    printf("총 합계 : %d\n", sumOfMonth);

    int result = sumOfMonth % 7;
//    char *day[3];
    if (result == 0)
    {
        day = "SUN";
    }
    else if(result == 1)
    {
        day = "MON";
    }
    else if(result == 2)
    {
        day = "TUE";
    }
    else if (result ==3)
    {
        day = "WED";
    }
    else if(result ==4)
    {
        day = "THU";
    }
    else if (result ==5)
    {
        day = "FRI";
    }
    else if (result ==6)
    {
        day = "SAT";
    }
    printf("%s\n", day);

//    *day = calculate_day(sumOfMonth);

//    printf("%s", day);


    return 0;

}

int dateOfMonth(int mon)
{
//    int sumOfMonth;
    if (mon == 0) return 0;
    // 홀수니? && 8 아니니? && 9,11 아니니?
    else if (mon < 8)
    {
        if (mon==2)
        {
            return 28;
        }
        else if (mon%2==1)
        {
            // 1,3,5,7월 = 31일
            return 31;
        }
        else if (mon%2==0)
        {
            // 4,6월 = 30일
            return 30;
        }
    }
    else
    {
        if(mon%2==0)
        {
            // 8, 10, 12월 = 31일
            return 31;
        }
        else if (mon%2==1)
        {
            // 9, 11월 = 30일
            return 30;
        }
    }
    return 0;
}

// ~x월 까지의 일자 합을 구해야함.
// 인자로 월 값을 받았을 때, 그 일에 대한 30,31,28인지 리턴받아 sum해야함

//
//char calculate_day(int sumOfMon)
//{
//    char** day;
//
//
//    return **day;
//}
