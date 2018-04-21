# promise

Promise는 비동기 동작의 최종완료 및 실패를 나타내는 **객체**다.

기존 방식의 콜백함수를 넘기는 대신, 콜백함수를 붙인 콜백에서 반환된 객체다.

```javascript
function successCallback(result){...}
function failCallback(err){}

doSomething(successCallback, failCallback);


const promise = doSomething();
Promise.then(successCallback, failCallback);
```

Promise의 기본적인 동작을 보자.

```javascript
var _promise = function (txt) {
    return new Promise(function(resolve, reject){
        setTimeout(function(){
            if (txt) {
                // 성공
                resolve(txt);
            } else {
                // 실패
                reject(Error('거절: 파라미터 없음'));
            }
        }, 1000)
    }) 
}

_promise('success')
.then(
    (resolveParam) => { console.log(resolveParam); },
    (err) => {console.error(err)}
)

_promise()
.then(
    (resolveParam) => { console.log(resolveParam); },
    (err) => {console.error(err)}
)
```

Promise는 다음 상태값을 가진다.

- pending : resolve나 reject가 실행되기 전 초기 상태(대기중)
- fulfilled : resolve 실행 (수행 완료)
- rejected : reject 실행 (실패)

1. _promise 함수 호출 후 resolve 및 reject를 만나기 전까지 pending 상태다. 조건에 따라 resolve 및 reject 함수 호출한다. 
    - resolve, reject 함수는 Promise 객체를 반환한다. 그래서 .then() 함수 호출가능하다.
1. `then()`을 통해 처리 결과 값(resolve 인자 or reject 인자)을 받는다.
    - then의 첫번째 인자는 succeeCallback(onFulfilled)을, 두번째는 failureCallback(onRejected)을 선언하면 Promise 상태에 따라 수행하게 된다.

## then

죄금 더 응용 해서 then 체이닝을 걸어보자.

```javascript
new Promise(function(resolve, reject){
    setTimeout(function() {
        resolve(1)
    }, 1000)
})
.then(function(result) {
    console.log(result); // 1
    return result + 1; 
})
.then(function(result) {
    console.log(result); // 2
    return result + 1;
})
.then(function(result) {
    console.log(result); // 3
    return result + 1;
})
```

Promise가 1초간 pending 상태 후, resolve 호출부를 만나고 프로미스 상태가 fulfilled로 변경된다. 첫번째 then에서는 resolve가 넘겨준 1을 받는다. 그 값에 1을 더해서 다음 then으로 넘겨준다.

> then 메서드는 `Promise`를 리턴한다. 그래서 이어지는 then 호출들을 chaining할 수 있다. **onFulfilled or onRejected 콜백함수가 리턴하는 값은 자동으로 resolved promise로 wrpaping되기 때문에 다음에 오는 then or catch 메서드로 전달된다.**


### 에러처리

1. then의 두번째 인자(onRejected) 함수에서 처리하기

```javascript
    new Promise(function(resolve, reject){})
    .then(onFulfilled, onRejected)
```

2. catch문 이용하기
```javascript
    new Promise(function(resolve, reject){})
    .then(onFulfilled)
    .catch(function (err){
        console.error(err);
    })
```

가급적 에러 처리는 catch()로 하는게 좋다.

onRejected에서 에러 핸들링시 onFullfiled에서 에러가 발생한 경우 오류를 제대로 잡지 못한다. onFulfilled 함수의 에러까지 커버 가능한 catch문에서 에러를 핸들링하자.


## 참고

[https://joshua1988.github.io/web-development/javascript/promise-for-beginners/](https://joshua1988.github.io/web-development/javascript/promise-for-beginners/)
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/Using_promises](https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/Using_promises)