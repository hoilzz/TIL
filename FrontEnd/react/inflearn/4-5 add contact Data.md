# 4-5 Contact 데이터 추가 기능 구현

## ContactCreate 클래스 추가
- input 2개
    - state 사용
- button 1개 추가
    - create 버튼 누르면 handleCreate(in Contact class) 메서드 실행

### constructor
- state 초기화
```javascript
this.state = {
  name: '',
  phone: ''
};
```

- input value 속성의 값은 state로
```javascript
<input
      type = "text"
      name="name"
      placeholder="name"
      value={this.state.name}
      onChange={this.handleChange}
/>
<input
      type = "text"
      name="phone"
      placeholder="phone"
      value={this.state.phone}
      onChange={this.handleChange}
/>
```

## 추가하기
- 수정할 땐 change 메서드를 만들어 담당하게 했는데, 수정할 state가 하나라 다음과 같이 한다.
```javascript
handleChange(e) {
  this.setState({
    keyword: e.target.value
  });
}
```
#### 근데 2개일 때는..?
- 비어있는 객체를 만든다.
    - 이렇게 되면 여러개 객체를 만들 수 있다.
- `e.target.name` 은 `<input name="...">`이다.

```javascript
handleChange(e) {
  let nextState = {};
  nextState[e.target.name] = e.target.value;
  // phone 수정시
  // 이러한 객체 생성 {phone : "3903903"}
  this.setState(nextState);
}
```

- `nextState[e.target.name]`이 수정되면 `{phone:'asdf'}`와 같은 객체가 생성됨


## click 했을 때 이벤트 설정
handleClick 이라는 메서드 만들자.
```javascript
handleClick() {
  const contact = {
    name: this.state.name,
    phone: this.state.phone
  };
  this.props.onCreate(contact);
  this.setState({
    name: ' ',
    phone:' '
  });
}
```
- 먼저 contact에서 oncreate라는 props를 받아올꺼다.
    - onCreate props는
    ```javascript
    handleClick(key) {
      this.setState({
        selectedKey: key
      });
      console.log(key, 'is selected');
    }
    ```

## props 설정
- proptype 와 defaultprops 설정해주자. 안해도 되지만 습관들이면 좋다.
