//
// https://www.acmicpc.net/problem/10845
//
//  main.cpp
//  queue_10845
//
//  Created by 정호일 on 2016. 1. 6..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
using namespace std;

int check_empty(int front_index, int back_index);
void print_size(int front_index, int back_index);

int main() {

    int queue[10000];

    int front_index = 0;
    int back_index = -1;

    int iteration;
    int i = 0;

    cin>>iteration;



    while(i < iteration)
    {
        string input_str;
        cin>>input_str;

        if (input_str.compare("front") == 0)
        {
            if (check_empty(front_index, back_index) == -1)
            {
                cout<<"-1"<<endl;
            }
            else
            {
                cout<<queue[front_index]<<endl;
            }
        }

        else if(input_str.compare("back") == 0)
        {
            if (check_empty(front_index, back_index) == -1)
            {
                cout<<"-1"<<endl;
            }
            else
            {
                cout<<queue[back_index]<<endl;
            }
        }

        else if(input_str.compare("empty") == 0)
        {
            if (check_empty(front_index, back_index) == -1)
            {
                cout<<"1"<<endl;
            }
            else
            {
                cout<<"0"<<endl;
            }
        }

        else if(input_str.compare("size") == 0)
        {
            print_size(front_index, back_index);
        }

        else if(input_str.compare("pop") == 0)
        {
            // 비어있으면
            if (check_empty(front_index, back_index) == -1)
            {
                cout<<"-1"<<endl;
            }

            else
            {
                int temp_value = queue[front_index++];
                cout<<temp_value<<endl;
            }
        }
        else if(input_str.compare("push") == 0)
        {
            int input_num;
            cin>>input_num;
            queue[++back_index] = input_num;
        }
        i++;
    }





    return 0;
}

void print_size(int front_index, int back_index)
{
    if (check_empty(front_index, back_index) == 1)
    {
        cout<<"0"<<endl;
    }
    else
    {
        int result_value = back_index - front_index + 1;
        cout<<result_value<<endl;
    }
}

int check_empty(int front_index, int back_index)
{
    // 비어있으면 1
    if (front_index > back_index)
    {
        return -1;
    }

    // 안비어있으면 0
    else
    {
        return 0;
    }
}
