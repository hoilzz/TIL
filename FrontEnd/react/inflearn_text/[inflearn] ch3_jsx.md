# JSX
JSX 문법을 사용하여 UI를 템플릿화
- JSX는 컴파일링 되면서 최적화되므로 빠름
- Type-safe (어떠한 연산도 정의되지 않은 결과를 내놓지 않는 것, 즉 예측 불가능한 결과를 나타내지 않는 것) 하며 **컴파일링 과정에서 에러를 감지**
- HTML에 익숙하다면, JSX를 사용하여 더 쉽고 빠르게 템플릿 작성 가능


## 1 JSX 사용하기
```javascript
import React from 'react';

class App extends React.Component {
    render(){

        return (
                <h1>Hello Velopert</h1>
        );
    }
}

export default App;
```

- class 개념 도입, ES5에서는 `React.createClass()` 메서드 사용. 또한 ES5에서 클래스 만들 때, 메소드를 nest할 수 없고 prototype 사용했어야함

- render()
  - 메서드에서는 컴포넌트에 렌더링 될 데이터 정의
- return ()
  - js에서 html 반환. 따옴표같은건 없다.
  - React JSX는 XML-like Syntax를 native JS로 변환해준다.
  - 따라서 " "로 감싸지 않는다.
  - () 도 필요없지만 가독성을 위해 써주자

## 2 Nested Element
컴포넌트에서 여러 엘리먼트 렌더링시, 그 엘리먼트들을 필수적으로 container element 안에 포함시켜줘야 합니다.
: 걍 div와 같은 container element를 wrapper로 사용해라.

## 3 Javascript Expression
JSX 안에서, js 표현 사용하는 방법은 **그냥 {}로 wrapping하기**
```javascript
render() {
  let text = "Dev-Server"
  return (
    <div>
      <h1> Hello velopert </h1>
      <h2> welcome to {text} </h2>
    </div>
  );
}
```

- `let`
  - es6에 도입된 let은 var와 비슷하지만
    - var의 scope는 함수 단위
    - let은 블럭 범위 내에서 변수 선언
  - 따라서 js scope관련 문제 해결 가능
- `{text}`
  - text javascript 변수를 렌더링

### 임의 method 생성 및 사용하기
React에서 method 생성하고 사용하는 방법에 대해 알아보자.
```javascript
sayHey(){
  alert("hey");
}

render() {
  let text = "Dev-Server"
  return (
    <div>
      <h1> Hello Velopert </h1>
      <h2> Welcome to {text} </h2>
      <button onClick={this.sayHey}>Click me </button>
    </div>
  )
}
```
- `{this.sayHey}`
  - ()가 뒤에 안붙음, 만약 붙으면 페이지 로드시에도 실행됨

### If-Else 문 사용불가
JSX안의 js에서 사용불가. 대안은 `condition ? T : F`

## 4 inline style
React의 inline style에서는 string 형식 아닌 `camelCase`인 object가 사용

```javascript
render(){
        let text = "Dev-Server";

        let pStyle = {
            color: 'aqua',
            backgroundColor: 'black'
        };

        return  (
            <div>
                <h1> Hello Velopert </h1>
                <h2> Welcome to {text}</h2>
                <button onClick= {this.sayHey}>Click Me</button>
                <p style = {pStyle}>{1 == 1 ? 'True' : 'False'}</p>
            </div>
        );
    }
```

## 5 주석
`{/* comments */}` container element 안에 작성되어야 한다

## 6 Naming Convention
- React Component는 첫문자가 대문자인 CamelCase로 작성


## Summary
1. JSX 사용하기
  - class 개념 도입 `class App extends ..{}`
  - render(){return(...)} :  컴포넌트에 렌더링 될 데이터 정의
  - return() : 따옴표 없이 html 반환. () 필요없는데 가독성 위해 써주자
2. Nested Element
  - 컴포넌트에서 여러 엘리먼트 렌더링시, container element를 wrapper로 사용
3. javascript Expression
  - JSX 안에서, js 표현 방법은 그냥 {}로 wrapping 하기
  - `let` : 블럭 범위내 변수 선언
  - `{text}` : text js 변수를 렌더링
  - `onClick={this.sayHey}`: () 붙이면 컴포넌트 생성시에도 메서드 호출됨
  - if-else 문 사용불가
4. inline style
  - inline style에서 `camelCase`인 object 사용
5. Naming convention
  - React Component는 첫문자가 대문자인 camelCase로 작성
