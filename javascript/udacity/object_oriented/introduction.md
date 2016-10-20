# Scope
- Execution context or in memory scopes differ from lexical Scope
- **실행 context는 코드가 type될 때 가 아닌 코드가 실행될 때 build됨**

## In-memory Data Stores

- 프로그램이 실행될 때, 프로그램은 빌드됨
- 다양한 function object로 이용가능한 모든 변수의 track을 유지하기 위해 내부 데이터가 저장됨
- a new execution context는 너가 함수를 실행할 때마다 생성되야 한다.
  + 각각 new run of a function이 이전의 모든 실행으로부터 완전한 고립상태에서 작동될 것으로 예상되기 때문
- 따라서 각 lexical scope 경우에 실행 중에 생성된 many in-memory scope가 있을 것이다. or 아무것도 없을 것이다.

- 그것은 코드에서 주어진 function을 얼마나 많이 실행했느냐에 달려있다.
- execution context를 조사하기 위해, 우리는 실제로 이 프로그램 실행시켜봐야한다.

### Summary
interpreter가 읽을 때 첫번째 라인 읽은 후,

> memory  |   hero = "Gal"
2번째 라인 읽은 후,

> memory  |   hero = "Gal"
>             newSaga = {f}
newSaga 안의 내용은 무시한다. 이 내용들은 호출될 때만 run된다.

```javascript
var hero = aHero();
var newSaga = function(){
  var foil = aFoil();
  var saga = function() {
    var deed = aDeed();
    log(hero+deed+foil);
  }
  saga();
  saga();
};
newSaga();
newSaga();
```

## In-memory Scopes vs In-memory object

interpreter가 첫번째 newSaga() 읽기 전,
execution context 는 key value pair collection처럼 보인다. (sort of like an object).

## Building Multiple Execution Scopes


## Continuing Output Predictions

2번째 `newSaga()` 실행하면 완전히 새로운 execution context를 생성한다. (첫번째 `newSaga()`에서 생성된 `deed="Eyes"` 대신에)
