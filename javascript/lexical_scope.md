# lexical scope
함수 실행시 scope를 `함수 실행` 환경이 아닌 `함수 정의` 환경으로 참조하는 것

#### ex1
```javascript
function f1(){
    var a= 10;
    f2();
}
function f2(){
    return a;
}
f1();

//실행결과
/*
Uncaught Reference Error
: a is not defined
*/
```
ex1에서 f1,f2 모두 `전역에서 생성된 함수여서 서로 참조 가능`하다.
하지만 에러 발생한다.
- **f1안에서 f2를 호출했다고 해서 내부 변수 a를 참조할 수 없다.**
- `lexical scope`특성으로 인해 **함수 f2가 실행될 때가 아닌** **정의 될때의 환경을 참조**


```javascript
function f1(){
    var a= 10;
    f2();
    function f2(){
        return a;
    }
}

f1();
//실행결과
```

#### 혹은
```javascript
var a = 20;

function f1(){
    var a= 10;
    f2();
}
function f2(){
    return a;
}
console.log(f2());
```
- 스코프 체인을 따라 외부 컨텍스트 참조
