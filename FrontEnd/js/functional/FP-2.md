# 일급함수, add_maker, 함수로 함수 실행하기

FP를 구글에 검색시 가장 많이 활용되는 `add_maker()` 예제다.

```javascript
function func1(func) {
    return func();
}

f3( function() { return 'hoil'; })
f3( function() { return 'test'; })

/* add_maker */
function add_maker(a) {
    return function(b) {
        return a + b;
    }
}

var add10 = add_maker(10);

console.log(add10(20));

var add5 = add_maker(5);
var add15 = add_maker(15);

console.log(add5(10));
console.log(add10(20));
```

`add_maker()`는 클로저와 일급함수 개념을 사용하였다. 또한, `add_maker()` 내부의 리턴문의 함수가 순수 함수다. a라는 값은 변수이지만 참조만 할 뿐 변경하지 않는다. 그래서 내부 함수는 항상 동일한 값을 가리키고 있는 a라는 값에 b를 더하는 값을 리턴하는 순수함수다. `add_maker()`를 만들고 나면 어느 시점에 호출을 하든 동일 결과값을 만든다. 

```javascript
function f4(f1, f2, f3) {
    return f3(f1() + f2());
}

f4 (
    function() {return 2},
    function() {return 1},
    function(a) {return a * a});
```

f4는 실무에서 쓸 형태는 아니다. 걍 함수형 프밍 이해를 돕기 위한 함수로만 보자.

---

## 번외

함수형 프로그래밍은 애플리케이션, 함수의 구성요소, 언어 자체를 함수처럼 여기도록 만들고, 이러한 함수 개념을 가장 우선순위에 놓는다.

함수형 사고방식은 문제의 해결 방법을 동사(함수)들로 구성(조합)하는 것이다. 그렇다면 함수를 가장 우선순위로 놓는 프로그래밍이란?

```javascript
duck.moveLeft();
duck.moveRight();
dog.moveLeft();
dog.moveRight();

moveLeft(dog);
moveRight(duck);
moveLeft({ x: 5, y: 2})
```

단순하게 객체가 먼저 나오느냐 함수가 먼저 나오느냐 차이로 볼 수 있다. 객체지향에서는 데이터를 먼저 디자인하고 데이터에 맞는 함수를 만든다. 함수를 먼저 만들고 그 함수에 맞게 데이터 세트를 구성하는 식으로 프밍하게 된다. 예를 들어 moveLeft를 모든 동물이 사용할 수 있게 animal 클래스를 만든다.