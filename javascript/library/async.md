# async

```javascript
waterfall(tasks, callback)
```

함수 배열의 `tasks`를 실행한다. 배열 내에서 다음 함수에 결과를 통과시킨다.
그러나 만약 `tasks`가 에러를 가진다면, 다음 함수는 실행하지 않는다. 메인 콜백은 즉시 에러와 함께 호출된다.

그러나 만약 tasks가 콜백에서 에러 통과시키면 다음 함수는 시랳ㅇ 안된다
그리고 메인 콜백은 즉시 에러를 호출한다.

## Parameters

 - `tasks`는 `async fucntions`의 배열이다
	- 각 함수는 `result` 값과 함꼐 완료해야한다.
	- `result`값은 다음 task에 인자로 전달된다.

> AsyncFunction()
`function (arg1, arg2, ..., callback){})`
많은 파라미터(마지막 파라미터는 콜백함수다)를 가진 비동기함수다

마지막 콜백은 callback(err, results...)다.이 콜백은 함수가 완료되면 무조건 호출되어야 한다. 콜백은 첫번째 인자의 에러와 함꼐 호출되어야 한다.
만약 에러가 없다면 첫번째 인자에 null이 들어간채로 호출된다
그리고 result argument가 successful completion 신호로 들어갈 것이다
콜백은 정확히 한번 실행된다 이상적으로 on a later tick of JS event loop


```javascript
async.waterfall([
    function(callback) {
        callback(null, 'one', 'two');
    },
    function(arg1, arg2, callback) {
        // arg1 now equals 'one' and arg2 now equals 'two'
        callback(null, 'three');
    },
    function(arg1, callback) {
        // arg1 now equals 'three'
        callback(null, 'done');
    }
], function (err, result) {
    // result now equals 'done'
});

// Or, with named functions:
async.waterfall([
    myFirstFunction,
    mySecondFunction,
    myLastFunction,
], function (err, result) {
    // result now equals 'done'
});
function myFirstFunction(callback) {
    callback(null, 'one', 'two');
}
function mySecondFunction(arg1, arg2, callback) {
    // arg1 now equals 'one' and arg2 now equals 'two'
    callback(null, 'three');
}
function myLastFunction(arg1, callback) {
    // arg1 now equals 'three'
    callback(null, 'done');
}
```

## how to use

```javascript
async.waterfall([
    func1,
    func2,
    func3
])

function funcExample()
```
