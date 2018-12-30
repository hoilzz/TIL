# async-await

```javascript
function resolveAfter2Seconds() {
  return new Promise(resolve => {
    setTimeout(() => {
      resolve('resolved');
    }, 2000);
  });
}

resolveAfter2Seconds()
.then(
    resolved => {
        console.log(resolved);
        return 'done';
    }
);

async function asyncCall() {
  console.log(await resolveAfter2Seconds(););
  return 'done'
}

asyncCall();
// .then() 사용가능. async 함수의 반환값은 promise기 때문이다.
```

async 함수에는 `await`가 포함될 수 있다. await는 `async` 함수 실행을 일시 중지한다. 그리고 전달된 `Promise`의 resolve를 기다린다. 그리고 `async` 함수의 실행을 다시 시작한다.

asyncCall()에서 `await resolveAfter2Seconds()`는 console.log의 호출이 resolveAfter2Seconds promise가 resolve될 때까지 기다린다. resolve 된 후에 그 값을 출력한다.

## 왜 async/await가 더 나을까?

1. 간결함

- .then 코드 불필요
- response를 해결하기 위한 비동기 함수 불필요
- data란 이름의 변수를 선언 및 사용할 필요 없음
- 코드 nesting 줄어든다.

2. 에러 핸들링

- 동기와 비동기 에러 모두 try.catch로 해결 가능.
    - promise는 동기, 비동기 에러를 커버하기 위해 try/catch와 promise의 .catch를 사용해야하는 복잡함

*promise*
```javascript
const makeReq = () => {
    try {
        getJSON()
            .then(res => {
                const data = JSON.parse(res);
                console.log(data)
            })
            // async error를 핸들링 하기 위한 catch문
            .catch(err => {
                console.log(err);
            })
    // then 내부(async error)의 에러를 캐치하지 못함.            
    } catch (err) {
        console.log(err);
    }
}
```

1개의 catch문으로 모든 영역 커버

*async-await*
```javascript
const makeReq = async () => {
    try {
        const res = await getJSON();
        const data = JSON.parse(res);
        console.log(data);
    } catch (err) {
        console.log(err);
    }
}
```


3. 분기

```javascript
const makeRequest = () => {
  return getJSON()
    .then(data => {
      if (data.needsAnotherRequest) {
        return makeAnotherRequest(data)
          .then(moreData => {
            console.log(moreData)
            return moreData
          })
      } else {
        console.log(data)
        return data
      }
    })
}
```

코드가 너무나 불편해보인다. async-await로 nesting을 줄여보자.

```javascript
const makeReq = async () => {
    const data = await getJSON();
    if (data.needsAnotherReq) {
        const moreData = await makeAnotherReq(data);
        console.log(moreData);
        return moreData;
    } else {
        console.log(data);
        return data;
    }
}
```

4. 중간값

promise1 호출 후 여기서 return 값을 활용하여 promise2를 호출하고, promise3을 호출하기 위해 promise1과 promise2의 결과값을 사용한다. 그렇기 하기 위해 다음과 같은 코드를 작성한다.

```javascript
const makeReq = () => {
    return promise1()
        .then(res1 => {
            return promise2(res1)
                .then(res2 => {
                    return promise3(res1, res2)
                })
        })
}
```

이걸 좀 줄이기 위해 promise.all을 사용해보자.

```javascript
const makeReq = () => {
    return promise1()
        .then(res1 => {
            return Promise.all([res1, promise2(res1)])
        })
        .then(([res1, res2]) => {
            return promise3(res1, res2);
        })
}
```

promise nesting을 피하기 위해 res1과 res2가 배열로 묶은건데 코드 가독성을 떨어뜨린다. 걍 async-await를 쓰면 굉장히 단순해진다.

```javascript
const makeReq = async () => {
    const res1 = await promise1();
    const res2 = await promise2(res1);
    return promise3(res1, res2);
}
```

## 참고

[async-await가 promise를 사라지게할 수 있는 이유](https://medium.com/@constell99/%EC%9E%90%EB%B0%94%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8%EC%9D%98-async-await-%EA%B0%80-promises%EB%A5%BC-%EC%82%AC%EB%9D%BC%EC%A7%80%EA%B2%8C-%EB%A7%8C%EB%93%A4-%EC%88%98-%EC%9E%88%EB%8A%94-6%EA%B0%80%EC%A7%80-%EC%9D%B4%EC%9C%A0-c5fe0add656c)
 걍 거의 베낌


