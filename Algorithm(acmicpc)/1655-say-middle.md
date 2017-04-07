# 1655번 가운데를 말해요

[가운데를 말해요](https://www.acmicpc.net/problem/1655)

N개의 숫자를 입력하면 입력받은 숫자를 기준으로 중간값을 출력한다.

만약, 짝수개 라면 중간에 있는 두 수 중에서 작은 수를 출력한다.

---

## solution

- 최소힙, 최대힙
- Prirority Queue

매 입력시마다 중앙값을 유지해야 한다.

	1. 입력 값이 중앙 값보다 작을 때 최대힙(Left)에
	2. 중앙 값보다 클 때 최소힙(Right)에 추가한다.

추가 후, 중앙값을 최신화해야한다

	- 숫자의 개수가 홀수 개 일 때,
	- Left, Right의 요소 개수가 다르다면
	- 더 많은 요소를 가진 트리의 root값을 중앙값으로 초기화한다.
	- 기존의 중앙값은 더 적은 요소를 가진 트리에 추가된다.









```C
int main() {

    int len, mid, x;
    scanf("%d", &len);

    priority_queue <int, vector<int>, less<int>> maxHeap;
    priority_queue <int, vector<int>, greater<int>> minHeap;

    scanf("%d", &mid);

    for(int i = 1; i<=len;i++){

        if(i==1) printf("%d\n", mid);
        else{
            scanf("%d", &x);
            if(mid<=x) minHeap.push(x);
            else      maxHeap.push(x);

            if(i%2 == 1){
                if(maxHeap.size() < minHeap.size()){
                    int temp = mid;
                    mid = minHeap.top();
                    minHeap.pop();
                    maxHeap.push(temp);
                }
                else if(maxHeap.size() > minHeap.size()){
                    int temp = mid;
                    mid = maxHeap.top();
                    maxHeap.pop();
                    minHeap.push(temp);
                }
                printf("%d\n", mid);
            }else {
                if(maxHeap.size() > minHeap.size()){
                    printf("%d\n", maxHeap.top());
                } else{
                    printf("%d\n", mid);
                }
            }
        }
    }


    return 0;
}
```
