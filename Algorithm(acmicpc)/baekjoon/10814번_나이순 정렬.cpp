//
// https://www.acmicpc.net/problem/10814
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
struct Entry
{
    int age;
    char name[101];
    int joinIndex;
};

bool cmpEntry(const Entry &first, const Entry &second)
{
    if(first.age != second.age) return first.age < second.age;
    else return first.joinIndex < second.joinIndex;
}


int main() {

    int n;
    scanf("%d", &n);
    struct Entry entryOfSite[100001];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &entryOfSite[i].age);
        gets(entryOfSite[i].name);
        entryOfSite[i].joinIndex = i;
    }

    sort(entryOfSite, entryOfSite+n, cmpEntry);

    for (int i = 0; i < n; i++)
    {
        printf("%d%s\n", entryOfSite[i].age, entryOfSite[i].name);
    }

    return 0;
}
