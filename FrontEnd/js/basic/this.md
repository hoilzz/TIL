# this

[zerocho님의 this](https://www.zerocho.com/category/JavaScript/post/5b0645cc7e3e36001bf676eb)

```js
this; // window

var obj = {
  a: function() {
    console.log(this);
  }
};
obj.a(); // obj

var a2 = obj.a;
a2(); // window
```

호출할 때, 호출하는 함수가 객체의 메서드인지 그냥 함수인지가 중요합니다. a2는 obj.a를 꺼내온 것이기 때문에 더 이상 obj의 메서드가 아닙니다.

```js
var obj2 = { c: "d" };
function b() {
  console.log(this);
}
b(); // Window
b.bind(obj2).call(); // obj2
b.call(obj2); // obj2
b.apply(obj2); // obj2
```

명시적으로 this를 바꾸는 함수 메서드 삼총사 bind, call, apply를 사용하면 this가 객체를 가리킵니다.

## 화살표 함수

일반 함수는 함수를 선언할 때 this에 바인딩할 객체가 정적으로 결정되는 것이 아니고, 함수를 호출할 때 함수가 어떻게 호출되었는지에 따라 this에 바인딩할 객체가 동적으로 결정된다고 하였다.

**화살표 함수는 함수를 선언할 때 this에 바인딩할 객체가 정적으로 결정** 된다. (선언할때!!) 동적으로 결정되는 일반 함수와는 달리 화살표 함수의 this 언제나 상위 스코프의 this를 가리킨다. 이를 Lexical this라 한다. 화살표 함수는 앞서 살펴본 Solution 3의 Syntactic sugar이다.
