모든 리액트 컴포넌트는  render method가 있다.
이 메서드는

# JSX의 특징
모든 리액트 컴포넌트는 `render` 메서드가 있다
이 메서드는 컴포넌트가 어떻게 생길지 정의를 해준다
여기서 특별한점은 `JSX`다.

js에서 html형식을 그대로 작성할 수 있다.
```javascript
  var a = (
    <div>
    Welcome to <b>React Codelab</b>
    </div>
  ); // 가독성을 위해 괄호 사용하자
```

jsx는 어떻게 작동할까?
- babel이 해준다
- 그렇다고 jsx는 es6문법은 아니다
- babel에서 jsx 로더를 사용하여 jsx 코드 형태 코드를 변환해주는 것

다시 코드펜으로 오자

```javascript
class Codelab extends React.Component {
  render() {
    return (
        <div>Codelab</div>
    )
  }
}

// 코드랩 컴포넌트를 보여주게 해보자
class App extends React.Component {
  render() {
    return (
      <Codelab/>
    );
  }
}

// ReactDOM은 페이지에 JSX 코드를 렌더링할 때 사용
// 첫번째 인수는 렌더링할 JSX 형태의 코드
//
ReactDOM.render(<App/>, document.getElementById('root'));
```

## JSX의 특징
### 1 Nested Element

모든 JSX의 코드는 `container element`안에 포함시켜야함

```javascript
  // 에러 발생 코드
  render() {
    return(
      <h1>Hi</h1>
      <h2>I am Error</h2>
    )
  }

  // 컴포넌트에서 여러 Element를 렌더링할 때
  // container element안에 포함시키기

  render() {
    return (
      <div>
        <h1>Hi</h1>
        <h2>Yay! Error is gone!</h2>
      </div>
    )
  }
```
### 2 JavaScript Expression
JSX안에서 javascript 표현하려면 그냥 `{}`로 wrapping

```javascript
render() {
  let text = "Hello React";
  return (
    <div>{text}</div>
  );
}
```

if else 문은 JSX에 사용불가
대안은 tenary Expression
condition ? true : false

```javascript
render() {
  return (
    <p> { 1==1 ? 'True' : 'false'}</p>
  )
}
```

> *let*
- es6의 새로운 문법
- var와 비슷함
- 다른점은 var는 함수단위
- let은 block 범위
- 1번 선언되면 다시한번 선언 안된다
- es6에서 평상시 변수 선언시 let을 사용 (컨벤션)

### 3 Inline style
JSX에서 style 설정시 string 형식이 아닌
key가 camelCase인 객체가 사용됨

```javascript
render() {
  let style = {
    color: 'aqua',
    backgroundColor:'black'
  };

  return (
    <div style={style}>React Codelab </div>
  )
}
```

JSX안에서 class 설정시 class가 아닌 className을 사용

```javascript
  render() {
    return (
      <div className="box">React CodeLab</div>
    );
  }
```

### 4. Comments
JSX안에서 주석 작성시 `{/* ... */}`
container Element안에 주석이 작성되어야 한다
(아래 예시에서 div 아래 혹은 위에 주석이 올 시 에러 발생)

```javascript
render() {
  return (
    <div>
      {/*...*/}
    </div>
    )
}
```

## Summary

- JSX 안에서 javascript 표현시 `{}`로 래핑

```javascript
render(){
  let text="Hello React";
  return(
    <div>{text}</div>
  );
}
```

- JSX에서 if-else 사용 불가 -> 3항 연산자로 대체
- `let` 은 block 단위, `var`는 함수 단위다.

즉, var의 유효범위는 전체 외부 함수까지(for문에서 선언한 var를 생각해보자.), let은 변수를 선언한 블록과 그 내부블록까지 유효하다.

JSX에서, css의 property를 inline으로 표현할 때 `camelCase`를 사용하고
class도 `className`으로 표현한다.
