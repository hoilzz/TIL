//
// https://www.acmicpc.net/problem/11724
//
//  main.cpp
//  ConnectComponent_11742
//
//  Created by 정호일 on 2016. 5. 31..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int nodes[1001][1001] = {0,};
int numOfEdges, numOfNodes, beginNum, checkNum = 0, numOfcc = 0;
bool isComeNode[500001] = {false,};
bool isConnected = false;

void DFS(int beginNode);


int main() {

    scanf("%d %d", &numOfNodes, &numOfEdges);

    for (int i = 0; i < numOfEdges; i++)
    {
        int beginNode, endNode;
        scanf("%d %d", &beginNode, &endNode);
        nodes[beginNode-1][endNode-1] = 1;
        nodes[endNode-1][beginNode-1] =1;
    }

    for (int i = 0; i< 1000; i++)
    {
        DFS(i);
        if (isConnected == true)    {
            numOfcc+=1;
            checkNum+=1;
        }
        isConnected=false;
    }

    // 간선개수가 노드개수보다 더 많아도 연결요소 발생
    //if (numOfNodes >= numOfEdges)
    int temp = numOfNodes -1;
    temp = temp*(temp-1)/2;
    if(checkNum < numOfNodes)
    {
        numOfcc += numOfNodes-(numOfEdges + numOfcc);
    }


    printf("%d\n", numOfcc);
    return 0;
}

void DFS(int beginNode)
{
    //printf("%d ", beginNode+1);
    isComeNode[beginNode] = true;

    for (int i = 0; i < 1000; i++)
    {
        if(nodes[beginNode][i] == 1 && isComeNode[i] == false )
        {
            checkNum++;
            isConnected = true;
            DFS(i);
        }
    }
}

/////////
/*
    노드 1개 짜리 놓침
    return 함수
    그 함수 종료 후 호출한 함수도 종료 그러니까 만약 호출한 함수가 하던일 다 하게 하려면 return사용 ㄴㄴ
*/
