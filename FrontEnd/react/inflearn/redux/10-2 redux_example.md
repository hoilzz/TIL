# redux example

## connect API
```javascript
connect([mapStateToProps], [mapDispatchToProps], [mergeProps], [options])
```

`connect`는 react-redux의 내장 API입니다.
- `React Component`를 `Redux Store`에 연결 해준다
- 이 함수의 리턴값은 특정 `컴포넌트 클래스의 props`를  `store의 데이터`에 연결시켜주는 또 다른 함수 리턴
- 리턴된 함수에 컴포넌트를 인수로 넣어 실행하면
  - 기존 컴포넌트를 수정하는게 아닌 `새로운 컴포넌트 return`

`mapStateToProps(state, [ownProps])` : (Function) store의 state를 컴포넌트의 props에 매핑 시켜준다. ownProps 인수가 명시될 경우, 이를 통해 함수 내부에서 컴포넌트의 props 값에 접근 가능.

`mapDispatchToProps(dispatch, [ownProps])` : (Function or Object) 컴포넌트의 특정 함수형 props를 실행 했을 때, 개발자가 지정한 action을 dispatch 하도록 설정한다. ownProps의 용도는 위 인수와 동일하다.

[connect APi] (https://github.com/reactjs/react-redux/blob/master/docs/api.md#connectmapstatetoprops-mapdispatchtoprops-mergeprops-options)
