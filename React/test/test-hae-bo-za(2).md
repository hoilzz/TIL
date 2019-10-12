# 테스트해보자(2)

## 리듀서 테스트..

리듀서 테스트는 보통 아래와 같이 했는데.. toEqual에 들어갈 데이터를 매번 작성하기 귀찮았다.

```js
const dispatchedAction = ({
  type..
  payload: mockData..
})

expect(reducer(initialState, dispatchedAction)).toEqual({...})
```

그리고 다른분께 이것에 대해 말한 결과 snapshot을 추천받았고 이 방법이 훨씬 나아서 관련 포스팅을 읽고 요약을 하고자한다.

### 리듀서 테스트의 action은..

리덕스 공홈의 리듀서 테스트는 action 객체를 하드코딩하여 작성하였다.
하지만, 나는 유지보수의 문제를 겪기 싫어서 import 하여 사용하였다.
예를 들어, action 객체의 모양(type 이름, payload 등)이 바뀌면, 리듀서 테스트가 바로 깨질 것을 확인할 수 있다.
하지만, 하드코딩할 경우, action creator의 테스트만 깨질거고, 리듀서의 테스트는 잘 동작할거다.

하지만.. 테스트 초짜라서 이런 고민을 한 사람이 있나 찾아봤더니.. 있다. [고민한 사람](https://stackoverflow.com/questions/38662403/redux-unit-test-reducers-and-action-creators)

답변을 요약하자면.. 트레이드 오프다.

- 만약 action creator를 import하면,
  - 장점 : 유지보수하기 쉽다.
  - 단점 : 다른 개발자가 너 프로젝트 첨 본다면, action creator가 뭘 만들지 일일히 찾아봐야한다.
- action 객체를 하드코딩한다면,
  - 새로온 개발자가 리듀서 테스트 코드만 보고 리듀서 동작을 예측하기 쉽다. 왜냐하면 액션 객체에 모든 정보가 담겨 있기 때문이다.

내가 내린 결론은.. 유지보수가 쉽고 속도를 빠르게 하기 위해 액션 생성자를 사용하기로 결정했다.
그리고 ts를 사용할 경우.. 마우스 갖다대면 actionCreator의 리턴값이 추론되기 때문에, 그리고 더 중요한건
시간이 없기때무니다.

## reselect로 구현된 selector 테스트해보자

주어진 input에서, 셀렉터는 항상 동일한 ouput을 리턴한다. 그래서 unit test 하기 편하다.

셀렉터에 대한 메모이징 함수는 상태 업데이트 함수와 함께 올바르게 동작하는지 확인하는 것이 유용할 수 있다.
각 셀렉터는 재계산된 횟수를 리턴하는 `recomputations` 메서드를 가진다.

추가적으로, 셀렉터는 마지막 결과 함수에 대한 참조값을 유지할 수 있따. (`.resultFunc`).
만약 여러개의 셀렉터로 구성된 셀렉터를 가진다면, 이것은 state의 모양에 대한 커플링 없이 각 셀렉터를 테스트하는데 도움이 될거다.

https://twitter.com/dan_abramov/status/664581975764766721

createSelector(getIds, ids => ids);

얘 테스트 코드에서

```js
state = bannerReducer(initialState, {
  type: FETCH_BANNERS.SUCCESS,
  payload: fetchGeneralBannersSuccess
});
expect(selectBannerIds(state)).toEqual([1815]);
expect(selectBannerIds.recomputations()).toBe(1);

state = bannerReducer(initialState, {
  type: FETCH_BANNERS.SUCCESS,
  payload: fetchGeneralBannersSuccess
});
expect(selectBannerIds(state)).toEqual([1815]);
expect(selectBannerIds.recomputations()).toBe(1);
```

toBe(1)이 fail인데, result는 2다. 내가 잘못알고 있던거가 있는데..

createSelector는 참조값 비교를 한다.

action이 다시 dispatch 되면서 상태는 새로운 참조값을 가리키게 되니까.. 메모이징이 풀리게 된다.. 즉, 메모이징 될 수가 없다.

> defaultMemoize(func, equalityCheck = defaultEqualityCheck)
> defaultMemoize는 함수 파라미터 내부의 함수를 메모이즈한다.
> 이것은 createSelector에 의해 사용되는 함수를 메모이즈 한다.
> defaultMemoize는 1개를 캐싱한다.
> 인자의 값이 변경될 때, 항상 재계산한다는 것을 의미한다.
> defaultMemoize는 equalityCheck 함수를 호출하여 인자 변경 여부를 결정한다.
> defaultMemoize는 immutable data를 위한 설계되었기 때문에, equalityCheck 함수는 참조값을 이용하여 변경 여부 체크한다.

> createSelectorCreator(memoize, ...memoizeOptions)
> createSelector의 커스텀 버전을 만들기 위해 사용된다.
> memoize 인자는 defaultMemoize(걍 참조값 비교하는거)를 대체하기 위한 메모이제이션 함수다.
> ...memoizeOptions은 memoizeFunc에 전달되는 0개 이상의 설정이다.
> 셀렉터 resultFunc는 memoize하기위해 첫번째 인자로 전달되고 memoizeOptions은 2번쨰 인자로 전달된다.
