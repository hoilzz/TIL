//
// https://www.acmicpc.net/problem/2751
//
//  main.cpp
//  AlignNumber_2751
//
//  Created by 정호일 on 2016. 4. 21..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

void quickSort(int numbers[], int array_size);
void q_sort(int numbers[], int left, int right);

int main()
{

    int items[1000001], itemSize;

    scanf("%d", &itemSize);

    for (int i = 0; i < itemSize; i++)
    {
        scanf("%d", &items[i]);
    }

    quickSort(items, itemSize);

    for(int i = 0; i < itemSize; i++)
    {
        printf("%d\n", items[i]);
    }
}

void quickSort(int numbers[], int array_size)
{
    q_sort(numbers, 0, array_size -1);
}

void q_sort(int numbers[], int left, int right)
{
    int pivot, l_hold, r_hold;
    l_hold  = left;
    r_hold  = right;
    pivot   = numbers[left];  // 0번째 원소를 피봇으로 선택
    while (left < right)
    {
        // 값이 선택한 피봇과 같거나 크다면, 이동할 필요가 없다
        while ((numbers[right] >= pivot) && (left < right))
            right --;

        // 그렇지 않고 값이 피봇보다 작다면,
        // 피봇의 위치에 현재 값을 넣는다.
        if (left != right)
        {
            numbers[left] = numbers[right];
        }
        // 왼쪽부터 현재 위치까지 값을 읽어들이면서
        // 피봇보다 큰 값이 있다면, 값을 이동한다.
        while ((numbers[left] <= pivot) && (left < right))
            left ++;

        if (left != right)
        {
            numbers[right] = numbers[left];
            right --;
        }
    }

    // 모든 스캔이 끝났다면, 피봇값을 현재 위치에 입력한다.
    // 이제 피봇을 기준으로 왼쪽에는 피봇보다 작거나 같은 값만 남았다.
    numbers[left] = pivot;
    pivot         = left;
    left          = l_hold;
    right         = r_hold;

    // 재귀호출을 수행한다.
    if (left < pivot)
        q_sort(numbers, left, pivot - 1);
    if (right > pivot)
        q_sort(numbers, pivot+1, right);
}
