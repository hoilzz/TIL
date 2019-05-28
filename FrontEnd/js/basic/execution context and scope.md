## 4.2 실행 컨텍스트와 스코프

[execution-context](https://github.com/hoilzz/hoilzz.github.io/blob/f966ccf6c7162ca6714f89d581a773d6fc61e47b/_posts/2017-6-12-execution-context.md)

#### **execution context** 는 컨텍스트라고 부르며 중요한 개념이다.

- 변수, 함수의 실행 컨텍스트는 **다른 데이터에 접근할 수 있는지, 어떻게 행동하는지를 규정**한다
- 각 **실행 컨텍스트에는 변수 객체가 연결됨**. **해당 컨텍스트에서 정의된 모든 변수와 함수는 이 객체에 존재**

#### 가장 바깥쪽에 존재하는 실행 컨텍스트는 전역 컨텍스트다.

- 웹 브라우저에서는 이 컨텍스트를 window
  - 전역 변수와 함수는 모두 window 객체의 프로퍼티 및 메서드로 생성

#### **함수를 호출하면 독자적인 실행 컨텍스트 생성**

- **코드 실행이 함수로 들어갈 때마다 함수의 컨텍스트가 컨텍스트 스택에 쌓인다**
- **함수 실행이 끝나면 해당 컨텍스트를 스택에서 꺼내고 컨트롤을 이전 컨텍스트에 반환**

**컨텍스트에서 코드를 실행하면** 변수 객체에 `스코프 체인`이 생성됨

- 스코프 체인의 목적은 실행 컨텍스트가 접근할 수 있는 모든 변수와 함수에 순서를 정의하는 것

#### Summary

- 실행 컨텍스트는 전역 컨텍스트와 함수 컨텍스트 2가지 타입만 있다.
- 스코프 체인은 {} 다
- 지역변수와 전역변수의 개념..

```javascript
var color = 'blue';
function changeColor() {
  if (color === 'blue') {
    color = 'red';
  } else {
    color = 'blue';
  }
}
changeColor(); // color = red
```

#### changeColor()의 스코프 체인에는 2개의 객체가 있다.

1. 함수 자체의 변수 객체 (this ==== function changeColor())
2. 전역 컨텍스트의 변수 객체 (color)
3.

#### 로컬 컨텍스트에서는 지역 변수와 전역 변수 모두 쓸 수 있다.

```javascript
var color = 'blue';

function changeColor() {
  var anotherColor = 'red';
  function swapColor() {
    var tempColor = anotherColor;
    anotherColor = color;
    color = tempColor;
    // color, anothercolor, tempcolor 접근 가능
  }
  // color, anotherColor접근 가능, tempcolor 접근 불가능
}
changeColor();
// color만 접근 가능
```

3개의 실행 컨텍스트가 있다.

1. 전역 컨텍스트
2. changeColor()의 로컬 컨텍스트
3. swapColors()의 로컬 컨텍스트

- 내부 컨텍스트는 스코프 체인을 통해 외부 컨텍스트 전체에 접근 가능
- 외부 컨텍스트는 내부 컨텍스트에 대해 전혀 알 수 없음
- 컨텍스트 사이의 연결은 순서가 중요
  - 각 컨텍스트는 스코프 체인을 따라 상위 컨텍스트 검색 가능
  * but, 스코프 체인 따라 내려가며 검색 불가능
- `swapColors()`의 로컬 컨텍스트 스코프 체인에 3개의 객체가 있다
  1. swapColors() 자신의 변수 객체에서 변수나 함수 이름 검색
  2. changeColor()
  3. 전역 객체

### 식별자 검색

식별자 검색 순서
1 로컬 컨텍스트
2 스코프 체인 따라 검색 계속 (스코프 체인 내부의 객체에 프로토타입 체인이 있으므로 체인 따라 검색할 수도 있다.)
3 전역 컨텍스트 변수 객체에서 찾기
4 없으면 정의 안된걸로 판단

var color = "blue";
function getColor() {
return color;
}
alert(getColor()); //blue

window - color - getColor return color

## 4.4 요약

자바스크립트 변수는 `원시 값`, `참조 값` 2가지 형태로 저장 가능
`원시 값` : 불리언, 숫자, 문자열, undefined, null

- 원시값은 고정된 크기를 가지며 스택 메모리에 저장
- 원시 값을 한 변수에서 다른 변수로 복사하면 값자체가 복사됨
- 참조 값은 객체이며 힙 메모리에 저장
- 변수에 참조 값을 저장하면 참조만 저장할 뿐 객체 자체를 저장하는 것 아님
- 참조 값을 한 변수에서 다른 변수로 복사하면 참조만을 복사하므로 같은 객체를 참조
- typeof 연산자는 원시 타입 판별, instanceof 연산자는 값의 참조 타입 판별

원시 값과 참조 값을 가리지 않고 모든 변수는 스코프라고 부르기도 하는 `execution context`에 존재
실행 컨텍스트는

- **변수가 존재하는 기간을 결정**
- **어느코드가 해당 변수에 접근할 수 있는지도 결정**
- 실행 컨텍스트에는 **전역 컨텍스트와 함수 컨텍스트** 가 있다
- 실행 컨텍스트에 진입할 때마다 스코프 체인 만들어지며, 스코프 체인은 변수와 함수 검색할 때 쓰인다.
- 함수 컨텍스트는 해당 스코프에 있는 변수, 해당 스코프를 포함하는 컨텍스트에 있는 변수, 전역 컨텍스트에 있는 변수에 모두 접근 가능
- 전역 컨텍스트는 전역 컨텍스트에 있는 변수와 함수에만 접근 가능. 로컬 컨텍스트에 있는 데이터에 직접적 접근 불가능
