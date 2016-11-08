## apply() in frontend javascript book

apply 메서드는 소유자인 함수를 호출하면서 this를 넘기는데, 결과적으로는 함수 내부에서 this 객체의 값을 바꾸는 것이나 마찬가지
- 매개변수로 소유자 함수에 넘길 this와 매개변수 배열을 받는다.
- 2번째 매개변수는 Array의 인스턴스 or arguments 객체

```
  function sum(num1, num2){
    return num1 + num2;
  }

  function callSum1(num1, num2){
    return sum.apply(this, arguments);
  }
  function callSum2(num1, num2){
    return sum.apply(this, [num1, num2]);
  }

  console.log(callSum1(10,10)); // 20
  console.log(callSum2(10,10));
```
- callSum1은 자신의 this와 arguments 객체를 매개변수로 넘김
- callSum2는 arguments 객체가 아닌 매개변수 배열을 넘김

## apply() in opentutorial.org

`함수.apply()`

Ex
  function sum (arg1, arg2) {
    return arg1+arg2;
  }

  sum.apply // function apply() { [native code]}
            // apply는 내장 함수라 노출 안됨

  아래 2줄은 결과가 같다.

  sum.apply(null, [1,2])
  sum(1,2)

왜 사용하는지 알기 위해 null에 다른걸 넣어보자

## WHY?


#### Ex

  o1 = {val1:1, val2:2, val3:3}
  o2 = {v1:10, v2:50, v3:100, v4:25}
  function sum(){
    var _ sum = 0;
    for (name in this) {
      _ sum += this[name];
    }
    return _ sum;
  }
  alert(sum.apply(o1));
  alert(sum.apply(o2));

sum은 for in 문을 이용하여 객체 자신(this)의 값을 열거한 후에 각 속성의 값을 지역변수 _ sum에 저장 후 리턴하고 있다.

객체 function의 메소드 apply의 첫번째 인자는 함수가 실행될 맥락이다. sum.apply(o1)은 함수 sum을 객체 o1의 메소드로 만들고 sum을 호출한 후 sum을 삭제한다. 아래와 비슷하다

  o1 = {val1:1, val2:2, val3:3, sum:sum}
  o1 = {val1:10, val2:50, val3:100, v4:25 sum:sum}

  alert(o1.sum());
  alert(o2.sum());

  // 근데 코드가 그대로 출력된다. 왜냐면 o1의 마지막 속성이 for in 문에 들어간다. this[name]의 typeof 가 function이면 썸에 안더하면 된다.


## Summary
- 함수 sum에서 this의 값이 전역객체가 아니라 o1이 된다는 의미
- 일반적인 객체지향 언어에서 하나의 **객체에 소속된 함수는 그 객체의 소유물** 이 됨
- 하지만 **JS 에서는 함수는 독립적인 객체** 로 존재, apply 메서드를 통해 다른 객체의 소유물인 것처러 ㅁ실행 가능
- apply의 첫째 인자로 null 전달시 apply가 실행된 함수 인스턴스는 전역객체(브라
  우저에서는 window)를 맥락으로 실행
