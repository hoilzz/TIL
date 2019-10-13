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
    resolve({
      ok: true
    });
  }, 1500);
});

// promise version
var fetchSomething = () => {
  fetchSomethingAPI()
    .then(result => {
      console.log('result: ', result);
      return result;
    })
    .catch(e => console.error(e));
};

// async-await verison
var fetchSomething2 = async () => {
  try {
    var result = await fetchSomethingAPI();
    console.log(result);
    return result;
  } catch (e) {
    console.error(e);
  }
};

fetchSomething();
fetchSomething2();
```

위와 같이 보통 작성한다.
차이점은

- 함수를 async로 정의한다.
- async 함수는 암묵적으로 promise를 반환한다.
  - 그래서 await는 async 함수 내부에서만 사용 가능하다.
