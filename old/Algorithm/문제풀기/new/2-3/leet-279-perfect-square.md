# perfect squares

정수 n이 주어졌을 때, 그 n을 제곱 값의 합으로 나타낼 수 있는 식이 있다고 하자.

12 = 2^2 + 2^2 + 2^2
12 = 3^2 + 1 + 1 + 1

등 이 있다. 첫번째는 3개의 숫자로, 두번째는 4개의 숫자로 식을 나타낼 수 있다.

식을 나타낼 수 있는 최소 숫자의 개수를 구하자.

---

모든 경우의 수를 구해서 최소 값을 구하면 될거 같았다.
바로 떠오른건 DFS로 차례차례 구하는건데 이렇게 될 경우 불필요한 연산이 필요하게 된다.
DFS로 풀게 될 경우 연산을 깊게 실행할 필요 없이 최소 n을 구할 수 있다.


```C
class Solution {
public:
    int numSquares(int n) {
        if(n <= 3) {
            return n;
        }
        queue <pair<int, int>> q;
        q.push(make_pair(n, 0));
        int min = n;

        while(!q.empty()) {
            int nextNum = q.front().first;
            int nextCnt = q.front().second;
            q.pop();
            int i = 1;

            while(nextNum >= i*i) {
                i += 1;
            }
            i -= 1;
            nextCnt += 1;

            for(;i>=1; i--) {
                int temp = nextNum - (i * i);
                if(temp == 0) {
                    if(min > nextCnt) {
                        min = nextCnt;
                    }
                }
                if(nextCnt < min) {
                    q.push(make_pair(temp, nextCnt));
                }
            }

        }
        return min;
    }
};
```