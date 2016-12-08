//
// https://www.acmicpc.net/problem/10824
//
//  main.cpp
//  FOUR_NUMBER_10824
//
//  Created by 정호일 on 2016. 1. 6..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

int main() {

    long long arr_nums[4];

//    int num_1;
//    int num_2;
//    int num_3;
//    int num_4;


    for (int i = 0; i < 4; i++) {
        cin>>arr_nums[i];
    }

//    cin>>num_1;
//    cin>>num_2;
//    cin>>num_3;
//    cin>>num_4;

    long long result = 0;
    // num_1과 num_2를 붙이기
    // num_1을 num_2의 10 자릿수만큼 n제곱하기
    // num_2를 10으로 나눔 until 나머지가 10이하일 때까지

    for (int j = 1; j < 4; j+=2 ) {
        long long share = arr_nums[j];
        int divider = 10;
        int i = 1;

        if (share >= 10)
        {
            do {
                i++;
//                remainder   =   share % divider;
                share       =   share / divider;
            } while (share >= 10);
        }

        arr_nums[j-1] = arr_nums[j-1] * pow(10,i);

        long long attach_twoWords = arr_nums[j-1] + arr_nums[j];
        result += attach_twoWords;
//        cout<<attach_twoWords<<endl;

    }
            cout<<result<<endl;
//    cout<<result<<endl;
//    int share = num_2;
//    int remainder;
//    int divider = 10;
//    int i = 1;
//
//    if (share > 10)
//    {
//        do {
//            i++;
//            remainder   =   share % divider;
//            share       =   share / divider;
//        } while (share >= 10);
//    }
//
//    num_1 = num_1 * pow(10,i);
//
//    int attach_ab = num_1 + num_2;
//
//    cout<<attach_ab<<endl;


    return 0;
}
