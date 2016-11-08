# connect
```javascript
connect([mapStateToProps], [mapDispatchToProps], [mergeProps], [options])
```
`React component`와 `Redux store`를 연결
- 이것은 인자로 전달된 컴포넌트 클래스를 수정하지 않는다.
- 대신에 *new* , connected component class를 리턴한다.

### Arguments
- `[mapStateToProps(state, [ownProps])]` (Function) : 만약 명시되어있다면, **컴포넌트는 Redux store update를 subscribe 할 것**이다.
  - **이것이 업데이트될 때마다, `mapStateToProps`는 호출될 것이다**.
  - Its result는 plain object여야 한다
  - **그리고 component's props로 머지될 것**이다.
  - 만약 그것을 생략했다면 컴포넌트는 Redux store를 구독하지 않는다.
  - 만약 `ownProps`가 2번째 인자로 명시되어있다면, 그것의 값은 component로 전달된 props일 것이다.
  - **그리고 component가 `new props`를 받을 때마다 `mapStateToProps`는 재호출**된다.
    - (e.g 만약 parent component로 받은 props가 약간 바뀐다면, ownProps argument를 사용한다, `mapStateToProps`는 re-evaluated된다.)
    > Note : `mapStateToProps()` 또한 function을 리턴한다. 이 경우에 그 func는 특정 component instance를 위한 `mapStateToProps()`로 사용될 것이다. 이것은 너가 instance마다 memoization을 하도록 한다. 3

- `[mapDispatchToProps(dispatch, [ownProps]): dispatchProps]`(Object or Function) : **만약 object가 인자로 전달되면, 그것의 내부에 있는 각 function은 Redux action creator로 추정**된다.
  - 동일한 함수 이름을 가진 object, 하지만 every action creator 는 `dispatch`로 wrapped 되어서 그것들은 직접 호출된다. **action creator를 바인딩 하기위해 `dispatch`를 사용하는 object를 리턴하는 것**은 너한테 달려있다.
    - Tip : `bindActionCreators()` helper를 사용해도 된다.
  - 만약 이것을 생략하면, default 구현은 `dispatch`를 단순히 component's props에 주입한다. 만약 `ownProps`가 2번째 인자로 명시되어있다면, 그것의 값은 컴포넌트에 전달된 props가 될 것이다.
  - `mapDispatchToProps`는 컴포넌트가 new props를 받을 때마다 재호출 될 것이다.
  > `mapDispatchToProps()` 또한 function 리턴. 이 경우에 function은 특정 컴포넌트 인스턴스를 위해 `mapDispatchToProps()`.
  > 이것은 instance마다 memoization을 허용한다.

### Returns
state를 inject하고 action creators를 컴포넌트에 넣은 A React Component class

### Remarks
- 2번 호출될 필요가 있다.
  - 첫번째는 argument가 위와같이 설명된 것.
  - 두번째는 component로 : `connect(mapStateToProps, mapDispatchToProps, mergeProps)(MyComponent)`
- 전달된 React Component를 수정하지 못한다. 그것은 너가 대신 사용해야 하는 new, connected component를 리턴한다.
- `mapStateToProps` func는 전체 Redux store's state의 single argument만 가진다
- 그리고 props로 전달된 object를 리턴한다.

## Summary
`[mapStateToProps(state, [ownProps])]`(Function)






















































ㅍ
