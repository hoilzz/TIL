# permutation
순열

## next_permutation

```C
template <class BidirectionalIterator> bool next_permutation (BidirectionalIterator first,
	BidirectionalIterator last);
template <class BidirectionalIterator, class Compare> bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp)
```

다음 순열로 변환한다.

범위 내(first, last)의 요소들을 다음순열로 재정렬한다.

순열은 `n!`개의 순열에서 현재의 요소가 취할 수 있는 정렬 중 하나를 리턴한다. 모든 경우에 대해 순열을 탐색할 경우, 미리 오름차순으로 소트해둔다. `next_permutation`의 마지막은 내림차순이다.

`next_permutation`은 다음 순열을 판별할 수 있는데, 재배열하면 true, 마지막 순열인 경우 첫번째 순열로 재정렬 후 false를 리턴. 비교 함수 사용시 다음 상위 순열 판별 가능하면 동일하게 동작한다.


```C
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int myints[] = {1,2,3};
	sort(myints, myints+3);

	do{
		for (int i = 0; i<3; i++){
			cout<<myints[i]<<" ";
		}
		cout<<endl;
	}while(next_permutation(myints, myints+3))
}

cout<<"after loop : "<<myints[0]<<" "<<myints[1]<<" "<<myints[2]<<" "
```

## 관련문제

[10819 차이를 최대로](https://www.acmicpc.net/problem/10819)
