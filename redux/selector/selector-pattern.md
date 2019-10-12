# 셀렉터 패턴

[셀렉터 관련 글을 찾게된 계기](https://twitter.com/dan_abramov/status/664581975764766721)
[내가 쓰는 패턴](http://webframeworks.kr/tutorials/weplanet/redux-selectors-structure/)

> Redux tip
> 관련 리듀서에서 selector를 export 하자.
> 이렇게 하면, view와 action creator를 state 모양과 디커플링 할 수 있다.

## 리덕스 셀렉터 구조화 하기

자세히 보려면 [다음 링크를 참조](http://webframeworks.kr/tutorials/weplanet/redux-selectors-structure/)하자.

셀렉터 패턴은 app 상태에 대한 쿼리 로직을 스탠다드하게 하는 추상화다.
app이 접근해야하는 store의 부분에 접근하기 위해, full store가 주어졌을 떄, 원하는 부분을 리턴하는 함수를 정의하는 것이다.

public selector(global selector)와 private selector(local selector) 2가지를 생성한다.

컴포넌트에서 상태를 접근하기 위해서는 public selector를 통해 접근한다.

public selector는

- 이 때, 컴포넌트는 state만 넘겨주면 원하는 상태를 받을 수 있다.
- 1개 이상의 private selector로 구성될 수 있다.
- 거의 바뀌지 않는다.

private selector는

- full store의 특정 부분과 연관되어있다.
- 자주 바뀐다.

이렇게 하면,

- 컴포넌트는 내부 상태 표현과 완전히 분리될 수 있다. 즉, 내부 상태 구조를 몰라도 된다.
  - 또한, 매번 상태를 unpack하지 않고 셀렉터에 state만 넘겨주면된다.
- localSelector를 전체 리듀서 구조가 아닌, 서브 리듀서 구조만으로 테스트할 수 있다.

추가하여..

어떤 셀렉터가 동일한 연산이 자주 일어나는 경우 `reselect` 라이브러리를 이용하여 메모이징 할 수 있다.
