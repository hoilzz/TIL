# bind
`bind()` 호출시 `this`를 제공된 값으로 설정하고 새로운 함수 호출 시 제공되는 주어진 순서의 선행 인수가 있는 새로운 함수를 생성

## Syntax
> fun.bind(thisArg[, arg1[, arg2[,...]]])
### 매개변수
**thisArg**
: 바인딩된 함수가 호출될 때 target 함수에 this 매개변수로서 전달되는 값. **그 값은 바인딩된 함수가 new 연산자를 사용하여 생성된 경우 무시된다.**

**arg1, arg2, ...**
: 대상 함수를 호출할 때 바인딩된 함수에 제공되는 인수 앞에 붙이는 인수.

### 반환값
지정된 `this`값 및 초기 인수가 있는 주어진 함수의 복제본

```javascript
this.x = 9;
var module = {
  x:81,
  getX: function() { return this.x; }
}

module.getX();

var retrieveX = module.getX;
retrieveX();

var boundGetX = retrieveX.bind(module);
boundGetX();
```

## Summary
- `bind()` 호출시 `this`를 제공된 값으로 설정
- 반환값 : 지정된 `this`값 및 **초기 인수가 있는 주어진 함수의 복제본**
