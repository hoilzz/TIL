# n개의 숫자에서 r개 고르기

각 조각에서 하나의 원소를 고른다. **원소 고른 뒤, 남은 원소들을 고르는 작업을 자기 자신을 호출해 떠넘기는 재귀 함수를 작성한다.** 이 떄 남은 원소들을 고르는 작업을 다음과 같은 입력들의 집합으로 정의할 수 있다. 

- 원소들의 총 개수
- 더 골라야 할 원소들의 개수
- 지금까지 고른 원소들의 번호

```C
/**
  - n : 전체 원소의 수
  - picked: 지금까지 고른 원소들의 번호
  - toPick : 더 고를 원소의 수
  일 때, toPick개의 원소를 고르는 모든 방법 출력
**/
void pick(int n, vector<int>& picked, int toPick){
  // 기저 사례: 더 고를 원소 없을 때 고른 원소들을 출력
  if(toPick == 0) {printPicked(picked); return;}
  // 고를 수 있는 가장 작은 번호 계산
  int smallest = picked.empty() ? 0 : picked.back() + 1;

  for(int next = smallest; next < n; ++next){
    picked.push_back(next);
    pick(n, picked, toPick - 1);
    picked.pop_back();
  }
}
```

위 코드는 텅 빈 답에서 시작해서 매 단계마다 하나의 원소를 추가하는 일은 반복한다. 그러다가 하나의 답을 만든 뒤 **이전으로 돌아가** 다른 원소를 추가하는 식으로 모든 답을 생성한다.

## 오답노트

문제 : 원소 선택하기
기저 사례 : 원소를 r개 모두 선택한 경우