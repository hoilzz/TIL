# Hot Module Replacement

- 현상태 : 서버 가동중에 코드 변경되면 모든페이지가 새로고침됨
- 원하는거 : HotModuleReplacementPlugin의 기능은 수정된 파일만 리로딩
- 왜 gap발생?
  + webpack이 어떤 파일을 어떠한 상황에 갈아끼울 수 있는지 몰라서
  + 그래서 설정해주면 해결됨

```javascript
if(module.hot) {
  module.hot.accept();
}
```

## 문제점
- 프로젝트가 리로딩 될 때 local `state` 유지가 안된다.

### state 만들어보자
```javascript
constructor(props) {
  super(props);
  this.state = {
    name: ''
  };
}
```
- 여튼 이상황에서 리로딩되면 local state 없어짐..

## 해결책
- react-hot-loader 적용하자
