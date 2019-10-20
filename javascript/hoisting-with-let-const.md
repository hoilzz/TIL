# hoisting with let-const

일단 호이스팅 용어를 정확히 하자.

함수 호이스팅과 변수 호이스팅으로 구분해서 이해하자.

#### 함수 호이스팅

함수 선언식은 EC 생성시 함수명을 VO의 프로퍼티로 설정하고, 생성된 함수 객체가 값으로 설정된다.

#### 변수 호이스팅

변수 선언식은 EC 생성시 변수명을 VO의 프로퍼티로 설정하고, undefined가 값으로 설정된다.
값 "할당"은 VO 생성후에 할당문 코드를 실행할 때 이뤄진다.

**그렇다면 함수 표현식은..?**

함수 표현식도 변수선언식이므로 변수 호이스팅에 해당된다.

## 호이스팅

var키워드로 선언된 변숭와 달리 let으로 선언된 변수는 선언문 이전에 참조하면 ReferenceError가 발생한다.
let은 스코프 시작에서 변수 선언까지 TDZ에 빠지기 때문이다.

EC에서 변수가 생성되는 방식은 다음 세가지로 나뉜다.

1. 선언단계 : 변수를 VO의 프로퍼티에 등록. 스코프가 참조하는 대상
2. 초기화 단계 : VO에 등록된 변수를 메모리에 등록. 이 때 JS 엔진이 undefined로 초기화
3. 할당 단계 : undefined로 초기화된 변수에 실제 값을 할당ㅇ.

**var** 는 1,2번이 한번에 이뤄진다. 그래서 변수 선언문 이전에 접근 가능하다. 이것이 변수 호이스팅.

**let** 은 1,2번이 분리되어 진행된다. 즉, 스코프에 변수를 등록(1번 선언단계) 하지만 초기화 단계는 변수 선언문에 도달했을 때 이뤄진다. 그래서 초기화 이전에 접근시 참조에러 발생한다. 이는 변수가 메모리에 등록되지 않았기 때문이다. (메모리에 변수를 할당한 적이 없다. 즉 참조에러)

스코프의 시작지점 ~ 초기화 시작 지점(변수 선언문 도달)까지 TDZ다.

![tdz](https://poiemaweb.com/img/let-lifecycle.png)

```js
let foo = 1; // 전역 변수

{
  console.log(foo);
  let foo = 2; // 지역 변수
}
```

위 그림대로라면 1이 출력되야 한다. 하지만 `ReferenceError: Cannot access 'foo' before initialization` 발생한다. EC의 VO에서 foo에는 접근가능하지만 아직 초기화(initialization)가 되지 않았다. 즉, 메모리에 할당(초기화)되지 않아서 참조에러가 발생한다.

## 클로저에서의 var와 let

```js
var funcs = [];

// 함수의 배열을 생성하는 for 루프의 i는 전역 변수다.
for (var i = 0; i < 3; i++) {
  funcs.push(function() {
    console.log(i);
  });
}

// 배열에서 함수를 꺼내어 호출한다.
for (var j = 0; j < 3; j++) {
  funcs[j]();
}
```

0 1 2 가 아닌 3 3 3 이 출력된다. var i 가 전역변수이기 때문이다.
0 1 2를 출력하려면 클로저를 이용하면 된다.

```js
var funcs = [];

// 함수의 배열을 생성하는 for 루프의 i는 전역 변수다.
for (var i = 0; i < 3; i++) {
  (function(index) {
    // index는 자유변수다.
    funcs.push(function() {
      console.log(index);
    });
  })(i);
}

// 배열에서 함수를 꺼내어 호출한다
for (var j = 0; j < 3; j++) {
  funcs[j]();
}
```

let 키워드를 이용하면 클로저를 이용하지 않아도 된다.

```js
var funcs = [];

// 함수의 배열을 생성하는 for 루프의 i는 for 루프의 코드 블록에서만 유효한 지역 변수이면서 자유 변수이다.
for (let i = 0; i < 3; i++) {
  funcs.push(function() {
    console.log(i);
  });
}

// 배열에서 함수를 꺼내어 호출한다
for (var j = 0; j < 3; j++) {
  console.dir(funcs[j]);
  funcs[j]();
}
```

i가 블록 내에서 유효한 지역 변수이기 때문이다.

![let scope](https://poiemaweb.com/img/for-let.png)

## let과 전역객체

var 키워드를 전역 변수로 사용하면 window의 프로퍼티가 된다.

let을 전역 변수로 사용시 window의 프로퍼티가 아니다.
왜냐하면 let 전역 변수는 보이지 않는 블록 내에 존재하게 된다.

## 참고

[var,let,const](https://poiemaweb.com/es6-block-scope)

## qna

Q. let과 const도 호이스팅이 되는가?
A. ㅇㅇ 된다. 근데 var와 다르게 VO에 프로퍼티만 등록되고 메모리에 할당단계까지 이뤄지지 않는다. 메모리에 할당단계는 VO 생성 후에 선언문 코드에 도달했을 때 메모리에 할당이 된다. 그래서 선언문 전에 접근시 var와 다르게 참조 에러가 발생한다. 내용은 초기화 전에 접근 불가능이다. 즉, VO에 등록은 됐다는 것잉다.

Q. 관련해서 TDZ에 대해 아는가?
A. TDZ는 스코프의 시작지점에서 변수 선언문까지 TDZ라 한다. 이 TDZ동안 변수를 참조할 수 없다.
