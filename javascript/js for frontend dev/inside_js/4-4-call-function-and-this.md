# 4.4 함수 호출과 this

## 4.4.1 arguments 객체

JS에서는 함수 호출시 인수들과 함께 암묵적으로 arguments 객체가 함수 내부로 전달된다.

arguments 객체는 함수 호출시 넘긴 인자들이 `배열 형태로 저장된 객체`를 의미한다.

주의해야할 점은 실제 배열이 아닌 `유사 배열 객체`다.

[유사배열객체란](https://github.com/seaunseen/TIL/blob/c5ec1282eeee947b3cfd13e86bb86d9340fef149/javascript/js%20for%20frontend%20dev/inside_js/ch3-5-9-array-like-obj.md)

arguments 객체는 다음과 같이 세부분으로 구성되어있다.

    - 함수를 호출할 때 넘겨진 인자 (배열 형태) : 함수 호출시 첫번째 인자는 0번, 두번째는 1번..
    - length : 호출할 때 넘겨진 인자의 개수 의미
    - callee : 현재 실행 중인 함수의 참조값


## 4.4.2 호출 패턴과 this 바인딩

함수 호출시 기존 매개변수로 전달되는 인자값과 `arguments` 객체 및 `this` 인자가 함수 내부로 암묵적으로 전달된다.

this는 이해하기 어렵다.

그 이유는 함수가 `호출되는 방식`에 따라 `this`가 다른 객체를 참조하기 때문이다.

이번 절에서는 함수 호출 패턴과 해당 패턴에 따라 **this가 어떤 객체에 바인딩이 되는지 알아보자**

## 4.4.2.1 객체의 메서드 호출시 this 바인딩

객체의 프로퍼티가 함수일 경우, 이 함수를 메서드라고 부른다.

이러한 메서드를 호출시, **메서드 내부 코드에서 사용된 this는 해당 메서드를 호출한 객체로 바인딩** 된다.

```javascript
var myObject={
    name:'foo',
    sayName:function(){
        console.log(this.name);
    }
}

var otherObject = {
    name:'bar'
}

otherObject.sayName = myObject.sayName;

myObject.sayName();     // foo
otherObject.sayName();  // bar
```


### 4.4.2.2 함수 호출시 this 바인딩

JS에서는 함수 호출시, 해당 함수 내부 코드에서 사용된 **`this`는 전역객체에 바인딩** 된다.

브라우저에서 JS를 실행하는 경우 전역 객체는 `window` 객체다.

```javascript
var foo = "I'm foo";

console.log(foo); // I'm foo
console.log(window.foo); // I'm foo
```

전역 변수는 전역 객체의 프로퍼티로도 접근 가능하다.

이제 함수 호출시 this 바인딩 되는 방법 알아보자.

```javascript
var test = 'This is test';
console.log(window.test);

var sayFoo = function(){
    console.log(this.test); // sayFoo() 함수 호출시 this는 전역객체에 바인딩 된다.
}
sayFoo();
```

- JS에서는 함수 호출시 this는 전역 객체에 바인딩 된다.
- `sayFoo()` 함수가 호출된 시점에서 this는 전역 객체인 `window`에 바인딩 된다.


함수 호출에서의 this 바인딩 특성은 `내부 함수(inner Function)`을 호출했을 경우에도 그대로 적용된다.

```javascript
var value = 100;

var myObj = {
    value:1,
    func1:function(){
        this.value +=1;
        console.log('func1() called. this.value : '+this.value);
        func2=function(){
            this.value +=1;
            console.log('func2() called. this.value : '+this.value);

            func3=function(){
                this.value +=1;
                console.log('func3() called. this.value : '+this.value);
            }

            func3();
        }
        func2();
    }
};

myObj.func1();
```

- func2()는 func1()을 부모함수로 하여, func2() 내부 함수의 this는 당연히 부모 함수의 this와 같은 객체인 myObj를 가리킨다고 생각하는게 자연스럽다.

그래서 예상 결과값은

```
func1() called. this.value : 1
func2() called. this.value : 2
func3() called. this.value : 3
```

하지만,

```
func1() called. this.value : 1
func2() called. this.value : 101
func3() called. this.value : 102
```


실행결과가 예측한 것과 다른 이유는 JS에서는 내부 함수 호출 패턴을 정의해 놓지 않기 때문이다.

내부 함수도 결국 함수이므로 이를 호출할 때 함수 호출로 취급된다.

따라서, 함수 호출 패턴 규칙에 따라 내부 함수의 this는 전역 객체에 바인딩된다.

이것을 극복하려면

부모 함수의 this를 내부 함수가 접근 할 수 있게끔 다른 변수에 저장하는 방법이다.

관례상 this값을 저장하는 변수의 이름을 that이라고 짓는다.

객체 부문만 수정한 다음 코드를 보자

```javascript
var myObj = {
    value:1,
    func1:function(){
        var that = this;
        this.value +=1;
        console.log('func1() called. this.value : '+this.value);
        func2=function(){
            that.value +=1;
            console.log('func2() called. this.value : '+that.value);

            func3=function(){
                that.value +=1;
                console.log('func3() called. this.value : '+tha.value);
            }

            func3();
        }
        func2();
    }
};
```

*apply, bind로 해결하기*

```javascript
var value = 100;

var myObj = {
    value:1,
    func1:function(){
        this.value +=1;
        console.log('func1() called. this.value : '+this.value);
        func2=function(){
            this.value +=1;
            console.log('func2() called. this.value : '+this.value);

            func3=function(){
                this.value +=1;
                console.log('func3() called. this.value : '+this.value);
            }
//             func3();
//             func3.apply(this, arguments);
               func3.bind(this)();
        }
//         func2();
//         func2.apply(this, arguments);
        func2.bind(this)();

    }
};

myObj.func1();
```
