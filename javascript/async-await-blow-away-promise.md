# Aync Await blows promise away

비동기 API 콜에서 promise말구 async await 쓰는 이유가 뭐에요? 라고 했을 때,

- then, catch 체이닝 없이 await로 간단하게 작성가능해요
  - 그리구 모양도 동기 코드랑 비슷하구요.
- 그리고 에러 커버 범위가 catch보다 try catch로 감싼 await가 더 커요(?) 라고 이상하게 말함

이상하게 말한거 정확히 재확인하고 싶어서 쓴글

[참고한 글](https://medium.com/@constell99/%EC%9E%90%EB%B0%94%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8%EC%9D%98-async-await-%EA%B0%80-promises%EB%A5%BC-%EC%82%AC%EB%9D%BC%EC%A7%80%EA%B2%8C-%EB%A7%8C%EB%93%A4-%EC%88%98-%EC%9E%88%EB%8A%94-6%EA%B0%80%EC%A7%80-%EC%9D%B4%EC%9C%A0-c5fe0add656c글

## syntax 비교하기

fetchSomething 함수는 프로미스를 반환한다. 그리고 JSON 오브젝트를 리졸브한다.

```js
var fetchSomethingAPI = new Promise(resolve => {
  setTimeout(() => {
    // JSON 객체라고 생각하자.
    resolve({
      ok: true
    });
  }, 1500);
});

// promise version
var fetchSomething = () => {
  fetchSomethingAPI()
    .then(result => {
      const parsed = JSON.parse(result);
      console.log('result: ', parsed);
      return parsed;
    })
    .catch(e => console.error(e));
};

// async-await verison
var fetchSomething2 = async () => {
  try {
    var result = await fetchSomethingAPI();
    const parsed = JSON.parse(result);
    console.log(parsed);
    return parsed;
  } catch (e) {
    console.error(e);
  }
};

fetchSomething();
fetchSomething2();

// work
fetchSomething.then(result => console.log(result));

// top level is not async fn..
// var result = await fetchSomething;
```

위와 같이 보통 작성한다.
차이점은

- 함수를 async로 정의한다.
  - await는 async 함수 내부에서만 사용 가능하다.
- async 함수는 암묵적으로 promise를 반환한다.

## 그래서 뭐가 더 좋은건데?

문법 차이를 알아봤다.

1. 간결함.

.then, .catch 체이닝 없이 try-catch와 await 문으로 동기 문법처럼 깔끔하게 사용 가능하다.

2. 에러 핸들링

async-await 는 동기와 비동기 에러 모두를 `try/catch`로 처리할 수 있다.
promise는 `try/catch`로 promise 내부에서 발생한 에러(즉, 비동기 코드 내에서)는 잡아내지 못한다.
catch를 호출하여 제어해야한다. (당연하지만 catch는 promise 외부에서 발생한 에러 잡아내지 못한다.)

이렇게 되면 promise는 `try/catch`와 `.catch` 두 곳에서 에러 핸들링을 해야한다.

3. 중간값

promise1 -> promise1값으로 primise2 -> promise1과 promise2로 promise3 이와 같이 호출해야 한다면 then 체이닝의 depth가 깊어진다.

promise.all을 통해 nesting을 피할 수 있지만 then 체이닝은 그대로다.

```js
const makeRequest = () => {
  return promise1().then(value1 => {
    // do something
    return promise2(value1).then(value2 => {
      // do something
      return promise3(value1, value2);
    });
  });
};

// improved version using promise
const makeRequest = () => {
  return promise1()
    .then(value1 => {
      // do something
      return Promise.all([value1, promise2(value1)]);
    })
    .then(([value1, value2]) => {
      // do something
      return promise3(value1, value2);
    });
};
```

async/await를 이용한다면 가독성이 높아진다.

```js
const makeRequest = async () => {
  const value1 = await promise1();
  const value2 = await promise2(value1);
  return promise3(value1, value2);
};
```

4. 디버깅

then에서 return 되는 arrow fn에 breakpoint 잡아내지 못한다.
then으로 step-over 사용 불가. step-over는 동기 코드만 따라간다.

await는 breakpoint 걸 수 있고 step-over로 await문엥서 멈출 수 있다.

## Summary

누가 async await보다 promise를 선호하는 이유를 다시 물어본다면..

1. 가독성, 동기식으로 표현가능하고 then chaining을 보지 않아도 된다.
2. 에러 핸들링

try catch문으로 둘 다 감쌌을 때 promise문의 비동기 에러는 try catch가 잡아내지 못한다. .catch()를 통해 에러 핸들링 해야한다. 즉, try-catch 와 catch문을 통해 두 번 에러 핸들링 해야한다.

async await의 try catch는 try 내부의 promise든 아니든 모두 에러 핸들링 가능하다.

3. breakpoint

then은 step over 불가, then에서 리턴하는 함수에 breakpoint 설정 불가. await문은 전부 가능.
