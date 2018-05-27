//
// https://www.acmicpc.net/problem/10971
//
//  main.cpp
//  10971
//
//  Created by 정호일 on 2016. 6. 7..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;
int weightOfCity[11][11] = {0,};
int cityArr[11] = {0,};

int valuesOfCourse[4000000];
int courseIndex = 0;

bool nextPermutation(int len)
{
    int beginIndex = -1, endIndex = 0, lastIndex = len -1;
    for (int i = 1; i<len; i++)
    {
        if(cityArr[i-1] < cityArr[i]) beginIndex = i-1;
    }

    if (beginIndex == -1) return false;

    for (int i = beginIndex+1; i < len; i++)
    {
        if (cityArr[beginIndex] < cityArr[i]) endIndex = i;
    }

    swap (cityArr[beginIndex], cityArr[endIndex]);

    while(beginIndex++ < lastIndex)
    {
        swap(cityArr[beginIndex], cityArr[lastIndex--]);
    }

    cityArr[len] = cityArr[0];

    return true;
}
bool calculateCourse(int len)
{
    int temp = 0;
    for (int i = 0; i<len; i++)
    {
        if(weightOfCity[cityArr[i]][cityArr[i+1]] == 0) return false;
        temp += weightOfCity[cityArr[i]][cityArr[i+1]];
    }
    valuesOfCourse[courseIndex] = temp;
    //printf(" : %d \n", valuesOfCourse[courseIndex]);
    courseIndex+=1;
    return true;
}


int main() {

    int numOfCity;
    scanf("%d", &numOfCity);

    for (int i = 0; i < numOfCity; i++)
    {
        for (int j = 0; j < numOfCity; j++)
        {
            scanf("%d", &weightOfCity[i][j]);
        }
    }
    for (int i = 0; i<numOfCity; i++)   cityArr[i] = i;
    cityArr[numOfCity] = cityArr[0];
    calculateCourse(numOfCity);

    while(nextPermutation(numOfCity) == true)
    {
        /*for (int i = 0; i<=numOfCity; i++)
        {
            printf("%d ", cityArr[i]);
        }*/
        calculateCourse(numOfCity);
    }

    int min = valuesOfCourse[0];
    for (int i = 1; i < courseIndex; i++)
    {
        if (min > valuesOfCourse[i])    min  = valuesOfCourse[i];
    }
    //printf("max : %d\n", min);
    printf("%d\n", min);
    return 0;
}
