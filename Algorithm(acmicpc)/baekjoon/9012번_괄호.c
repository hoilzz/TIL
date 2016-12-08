//
// https://www.acmicpc.net/problem/9012
//
//  main.cpp
//  VPS_9012
//
//  Created by 정호일 on 2016. 3. 19..
//  Copyright © 2016년 정호일. All rights reserved.
//

#include <stdio.h>

int main() {


    int iteration;
    scanf("%d", &iteration);

    while (1)
    {
//        char inputData[51];
        char *inputData = (char *)malloc(51*sizeof(char));
        int point = 0;

        scanf("%s",inputData);

        for (int i = 0; inputData[i]; i++)
        {
            if (inputData[i] == '(')
            {
                point++;
            }
            else if (inputData[i] == ')')
            {
                point--;
                if (point == -1) break;
            }

        }

        if (point != 0 ) printf("NO\n");
        else if (point == 0) printf("YES\n");

        iteration--;
        if (iteration <= 0) break;
    }

    //   (( )) ( )))
    // ((( ))))

    return 0;
}
