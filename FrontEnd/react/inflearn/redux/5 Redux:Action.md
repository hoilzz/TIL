# Redux : Action

## 기능
1. 값을 증가
2. 값을 감소
3. 새로운 색상 설정

### 이름 만들자
이름은 `_`와 `대문자`로
1. INCREMENT
2. DECREMENT
3. SET_COLOR

### actions/ActionTypes.js
이 파일에 action 이름들을 상수 형태로 만들고 다른 파일에서 불러와 사용할 수 있도록 내보내자.

action 개체가 어떻게 생겼는지 한 번 보자.
```javascript
// type은 항상 필수. type 종류에 따라 리듀서가 할일을 한다.
{ type : "INCREMENT"}
{ type : "DECREMENT"}
// 위 두가지는 액션에 따로 정보가 필요없다. 이 파일 말고는 액션에 추가적인 정보가 없다.
{
  // set color는 위와 다르게 추가 정보 필요
  // 색상을 새로운 값으로 설정해야하는데 어떤 값으로 설정할지 알려줘야 하는데 color가 그 역할을 한다.
  // 아래는 배열 값인 RGB를 전달
  // 추가 정보가 필요할 때는 color처럼 field 추가하면 됨
  // 액션은 그때그때 만들기 귀찮다.
  // 그래서 만든게 액션 생성자 함수
  type : "SET_COLOR",
  color: [200,200,200]
}
```

- 액션은 객체다
- 액션 객체가 필수로 가져야하는 것은 type이다.
  - 해당 타입의 종류에 따라 `Reducer`가 할 일을 한다.
- 액션에 새로운 정보가 필요할 때 field 추가하면 됨
- action을 그 때 그 때 객체 만들기 귀찮음
  - 그래서 action 생성자가 있다.

<br>

액션의 이름들을 ActionsTypes안에 만들어서 내보낸다.
actions/ActionsTypes.js
```javascript
export const INCREMENT = "INCREMENT";
export const DECREMENT = "DECREMENT";
export const SET_COLOR = "SET_COLOR";
```

### actions/index.js
```javascript

```
- 파일 이름이 index인 이유
  - 나중에 액션 디렉토리만 불러왔을 때 자동으로 index.js만 로드 되게끔 하기 위해
- `actionsTypes.js` 에서 export default가 아니기 때문에 `import`를 따로 해야한다
  - *을 쓰면 편함
  - 위와 같이 선언하면 `types.action이름`으로 사용하면됨,
- 액션 생성자는 camelCase,
- 액션 생성자는 다른 곳에서 불러올 수 있도록 `export`
  - 리턴하는 건 객체
  - increment는 type만 반환
