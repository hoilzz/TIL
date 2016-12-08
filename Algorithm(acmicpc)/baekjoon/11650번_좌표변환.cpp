//
// https://www.acmicpc.net/problem/11650
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x;
    int y;
};

bool cmpPoints(const Point &first, const Point &second)
{
    if (first.x != second.x) return first.x < second.x;
    else return first.y < second.y;
}

int main() {

    int n;
    scanf("%d",&n);
    struct Point arrPoints[100001];
    for (int i = 0; i < n; i++)     scanf("%d %d", &arrPoints[i].x, &arrPoints[i].y);
    sort (arrPoints, arrPoints+n, cmpPoints);
    for (int i = 0; i < n; i++)     printf("%d %d\n", arrPoints[i].x, arrPoints[i].y);

    return 0;
}
