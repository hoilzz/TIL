//  https://www.acmicpc.net/problem/1260
//
//
//
//  main.cpp
//  Adjacency_Matrix
//
//  Created by 정호일 on 2016. 5. 20..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <iostream>
#include <stdio.h>

// 정점
int adjMatrix[1001][1001] = {0,};
// 간선
int vertexArr[10001] = {0,};

// 탐색 여부
bool isTrueDFS[1001];
bool isTrueBFS[1001] = {false,};

int BFSIndex = 0;
int BFSFirst = 0;

int numOfVertex, numOfEdge, startVertex;

void DFS(int firstNode);
void BFS(int firstNode);
int main() {

    // 정점 개수, 간선 개수, 시작할 정점 번호
    // 연결될 두 정점의 번호가 주어짐.

    int tempStart, tempEnd;
    scanf("%d %d %d", &numOfVertex, &numOfEdge, &startVertex);

    for (int i = 0; i<numOfEdge; i++)
    {
        scanf("%d %d", &tempStart, &tempEnd);

        adjMatrix[tempStart-1][tempEnd-1] = 1;
        adjMatrix[tempEnd-1][tempStart-1] = 1;
    }

    DFS(startVertex-1);
    printf("\n");
    BFS(startVertex-1);
    printf("\n");
    return 0;
}

void DFS(int firstNode)
{
    isTrueDFS[firstNode] = true;
    printf("%d ", firstNode+1);
    //for (int i=0; i<numOfVertex; i++)
    for (int i=0; i<1000; i++)
    {
        // 방문한적이 없고, Matrix 값이 1일 때, 임시 배열에 쌓아놓음
        if (isTrueDFS[i] == false && adjMatrix[firstNode][i] != 0)         DFS(i);
    }
    // tempArr중 가장 작은 값을 검색 후, DFS
}

void BFS(int firstNode)
{
    // 지금 위치에서 갈 수 있는 것 큐에 넣기
    // 지금 위치에서 갈 수 있는 것 : adjMatrix[i][j] != 0,
    isTrueBFS[firstNode] = true;
    printf("%d ", firstNode+1);

    for(int i = 0; i<1000; i++)
    {
        // 큐에 쌓기
        if (isTrueBFS[i] == false && adjMatrix[firstNode][i] != 0)
        {
            vertexArr[BFSIndex++] = i+1;
            isTrueBFS[i] = true;
            /*for (int j = 0; j <= i; j++)
            {
                    printf("index[%d] : %d\n", j, vertexArr[j]);
            }*/
        }
    }
    if (vertexArr[BFSFirst]) BFS(vertexArr[BFSFirst++]-1);
}
