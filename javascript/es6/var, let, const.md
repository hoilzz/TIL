# var, let 그리고 const

## 같은 이름의 변수 선언
var는 너그럽다

```javascript
var foo = 'bar1';
var foo = 'bar2';
```

let과 const는 엄격하다

```javascript
let foo = 'bar1';
let foo = 'bar2';
// ERR : Uncaught SyntaxErr : Identifier 'foo has already been declared'
```
규모가 큰 코드에서 버그 방지할 수 있는 특징

## 호이스팅

```javascript
console.log(foo); // undefiend

var foo;
```
`호이스팅`
    - 변수의 정의가 그 범위에 따라 선언과 할당으로 분리되는 것을 의미
    - 변수가 함수내에서 정의되었을 경우 선언이 함수의 최상위로
    - 함수 바깥에서 정의되었을 경우 전역 컨텍스트의 최상위로 변경
    - 변수의 선언이 초기화나 할당시에 발생하는 것이 아닌, 최상위로 호이스트 된다!
    ```javascript
    function showName() {
      console.log("First Name : " + name);
      var name = "Ford";
      console.log("Last Name : " + name);
    }
    showName();
    // First Name : undefiend // 지역변수 name이 호이스팅됨.
    // Last Name : Ford
    ```
let 과 const
```javascript
console.log(foo);
// Err foo is not undefined
let foo;
```

## 블록
변수의 유효범위. var의 경우 function-scope라고 한다. 유효 범위가 함수 단위라는 말

```javascript
var foo = 'bar1';
cosole.log(foo); // bar1
if (true) {
  var foo = 'bar2';
  console.log(foo); // bar2
}
console.log(foo); // bar2
```

let과 const는 block-scope. 유효범위가 블록 즉 {}로 감싸지는 범위
```javascript
let foo = 'bar1';
console.log(foo); // bar1

if (true) {
  let foo = 'bar2';
  console.log(foo) // bar2
}

console.log(foo); // bar1
```

## let과 const는 적절한 관계

#### const
- 원시형(primitive : string, number, boolean, null, undefined)에서 const는 상수로 동작
- 재할당할 경우 에러 발생

#### let
- 값의 변경이 있는 경우

**참조형(array, object, function)의 경우 const로 선언하는 것이 바람직**.
- 참조형은 const 선언하더라도 멤버 값 조작 가능
```javascript
const foo = [0,1];
const bar = foo;
foo.push(2);
bar[0] = 10;

console.log(foo, bar);
// [10,1,2], [10,1,2]
```

위의 결과를 보다시피 `const bar = foo`의 선언으로 `bar는 foo를 참조`한다. 참조가 아니라 값을 복사하는 경우에는 array는 `...` 연산자를 사용, object는 `assign()`을 사용

## summary
- ES6 에서는 var를 지양하고 let과 const사용하자
- 원시형애서 변수는 let, 상수는 const
- 참조형은 const로 선언
