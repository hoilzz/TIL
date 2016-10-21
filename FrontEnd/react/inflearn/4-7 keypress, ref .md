# keypress, ref 를 이용한 extra 기능 구현

## 엔터를 이용하여 input 추가하기
```javascript
handleKeyPress(e){
  if (e.charCode == 13) {
    this.handleClick();
  }
}
<input
  onKeyPress={this.handleKeyPress}
```

## focus 컨트롤하기
create 버튼 누르면 input에 focus하기

```javascript
document.getElementById(id).focus();
```
보통의 경우 위와 같이 한다. 근데 이렇게 하면 안된다. 컴포넌트 여러개 로딩하는 경우 id가 중첩될거다..

### 해결책 ref
react js에서 id와 비슷하다.

ref 사용 방법
**use callback fun**

```javascript
class hello{
  render(){
    return(
      <div>
        <input ref={(ref) => {this.input = ref}}/>
      </div>
    )
  }
  // react's lifecycle api
  componentDidMount() {
    this.input.value = "I used ref to do this";
  }
}
```

- arrow 함수를 사용하여 this의 input을 ref 값으로
- componentDidMount()에서 접근

```javascript
<input ...
      ref = {(ref)=>{this.nameInput = ref}} />
```

추가를 한 다음 focus를 주고 싶다면
```javascript
handleClick()
{
  ...
  this.nameInput.focus();
}
```
- ref는 DOM외에도 컴포넌트에도 설정 가능
    - 만약 Contact에서 Component ref를 정했다.
    - 그럼 나중에 ref에 접근해서 그 컴포넌트의 내부 메서드도 직접 실행 할 수 있다.
    - 주의 할점 : 지금 해야할 작업이 ref를 사용하지 않고 다른 방법으로 구현할 수 있는지 하기
    - 예를 들어, focus는 ref 사용하지 않고 할 수 있는 방법 없다.
    - rendering, constructor 내부는 ref에 접근 불가능..









































ㅍ
