//
// https://www.acmicpc.net/problem/10828
//
//  stack_10828.cpp
//  stack_10828
//
//  Created by 정호일 on 2016. 1. 1..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
using namespace std;

void push_stack(int* stack, int input_num, int* index);
int pop_stack(int* stack, int* index);
int top_of_stack(int* stack, int* index);
int size(int* index);
int check_empty(int *index);


int main(){

    int *stack = new int[10000];

    int input_num;

    // Last index 값 저장
    int index = -1;
    string input_str;
    int num_of_perform;
    int i = 0;

    cin>>num_of_perform;


    while (i < num_of_perform)
    {
        cin>>input_str;
        if (input_str.compare("push") == 0)
        {
            cin>>input_num;
            push_stack(stack, input_num, &index);
        }
        else if (input_str.compare("pop") == 0)
        {
            cout<<pop_stack(stack, &index)<<endl;
        }
        else if (input_str.compare("top") == 0)
        {
            cout<<top_of_stack(stack, &index)<<endl;
        }

        else if (input_str.compare("empty") == 0)
        {
            cout<<check_empty(&index)<<endl;
        }
        else if (input_str.compare("size") == 0)
        {
            cout<<size(&index)<<endl;
        }
        i++;
    }
    return 0;
}




void push_stack(int* stack, int input_num, int* index)
{
    *index = (*index) + 1;
    stack[*index] = input_num;
}


int pop_stack(int* stack, int* index)
{
    if (check_empty(index) == 1)
    {
        return -1;
    }

    else
    {
        int deleted_num = stack[*index];
        stack[*index] = 0;
        *index = (*index) -1;
        return deleted_num;
    }
}


int top_of_stack(int* stack, int* index)
{
    if (check_empty(index) == 1)
    {
        return -1;
    }
    else return stack[*index];
}


int size(int* index)
{
    return *index + 1;
}


int check_empty(int* index)
{
    if (*index == -1) return 1;
    else             return 0;
}
