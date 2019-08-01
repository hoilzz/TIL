# const는 상수인데, 왜 값이 바뀔 수 있을까?

```js
const user = {
  age: 15
};

user.age = 16;
```

[const에 관한 mdn](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Statements/const) 문서를 보자.

> const 선언은 블록 범위의 상수를 선언한다.
> 상수의 값은 **재할당** 할 수 없고 다시 선언 불가하다.

말 그대로 재할당이 불가하다. 예를 들어 객체를 살펴보자.

위 user 변수는 Object의 참조값을 갖는다. 그래서 재할당하지 않는 한, object 내부의 값을 변경하는 것은 가능하다.
