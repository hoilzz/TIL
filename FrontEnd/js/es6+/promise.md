# promise

JS는 비동기 처리를 위해 콜백함수를 사용한다. 하지만 최근 복잡해진 FE 환경에서 콜백 패턴의 단점이 드러나고 있다.

```js
step1(function(value1) {
  step2(value1, function(value2) {
    step3(value2, function(value3) {
      ...
    });
  });
});

```

- 콜백헬.
  - 비동기 함수의 처리 결과에 대한 처리는 리턴할 수 없고, 비동기 함수의 콜백 함수 내에서 처리해야 하기 때문.
  - 또한, 비동기 함수 처리 결과를 가지고 다른 비동기 함수를 호출해야 하는 경우, nesting이되어 진정한 콜백헬 완성.
- 가독성이 나쁘다
- 비동기 처리 중 발생한 에러의 예외처리가 곤란하다. (작성하기 까다롭다)
- 여러개의 비동기 처리 로직을 한꺼번에 처리하는 것도 한계가 있다.

### 문제점 1# 콜백헬

```js
// 비동기 함수
function get(url) {
  // XMLHttpRequest 객체 생성
  const xhr = new XMLHttpRequest();

  // 서버 응답 시 호출될 이벤트 핸들러
  xhr.onreadystatechange = function() {
    // 서버 응답 완료가 아니면 무시
    if (xhr.readyState !== XMLHttpRequest.DONE) return;

    if (xhr.status === 200) {
      // 정상 응답
      console.log(xhr.response);
      // 비동기 함수의 결과에 대한 처리는 반환할 수 없다.
      return xhr.response; // ①
    } else {
      // 비정상 응답
      console.log("Error: " + xhr.status);
    }
  };

  // 비동기 방식으로 Request 오픈
  xhr.open("GET", url);
  // Request 전송
  xhr.send();
}

// 비동기 함수 내의 readystatechange 이벤트 핸들러에서 처리 결과를 반환(①)하면 순서가 보장되지 않는다.
const res = get("http://jsonplaceholder.typicode.com/posts/1");
console.log(res); // ② undefined
```

get함수의 반환 값은 없다.

get 함수 내부의 return 문은 readystatechange 핸들러 내부에 있다. 이 이벤트 발생시점은 알 수 없지만 get 함수 종료 후에 발생한다.

get 함수가 종료되면 console.log가 곧바로 호출되어 call stack에 들어간다.

readystatechange 이벤트 핸들러는 바로 실행되지 못하고, 이벤트 발생시 이벤트 큐로 들어가고 호출 스택이 비면 이벤트 루프에 의해 호출 스택으로 들어와 실행된다.

그래서 console.log(res)를 의도한 대로 동작하고 싶으면 비동기 함수 콜백 내에서 처리해야한다. 이 떄, 전달된 데이터를 가지고 또다른 비동기 함수를 호출하면 콜백헬이 시작된다. 이것을 promise로 해결할 수 있다.

Promise는 전통적인 콜백 패턴이 가진 단점을 보완, 비동기 처리 시점을 명확하게 표현한다.

### 문제점 2# 에러 처리의 한계

```js
try {
  setTimeout(() => {
    throw new Error("Error!");
  }, 1000);
} catch (e) {
  console.log("에러를 캐치하지 못한다..");
  console.log(e);
}
```

위 예외는 catch에서 처리되지 못한다. 이벤트 발생 후, 해당 콜백함수가 이벤트 큐로 이동한 후 이벤트 루프는 호출스택이 비워졌을 때, 호출스택에 가져와서 작업을 수행한다.

## Promise

Promise란 말 그대로 약속이다. 지금 없는데 이상 없으면 이따 주고 알려줄꼐 라는 약속이다.

### Promise는

- 비동기 처리가 성공/실패와 같은 상태를 갖는다.
- promise 생성자 함수가 인자로 전달받은 콜백 함수는 내부에서 비동기 처리 작업을 한다.
  - 그래서 아까 결과값을 리턴하지 못해서 콜백 함수 내부에서 결과처리를 했어야 하지만,
  - promise 생성자 함수가 인자로 전달받은 resolve, reject를 통해 결과값을 리턴할 수 있다.

### Promise 후속 처리 메서드

반환된 Promise객체에서 then, catch를 통해 후속처리를 할 수 있다.

catch 메서드는 에러를 처리하는데, then 메서드의 두 번째 콜백 함수도 에러를 처리할 수 있다.
다른 점은, then 메서드의 두 번쨰 콜백 함수는 reject된 함수만 처리한다. 하지만 catch는 비동기 처리에서 발생한 에러 뿐만 아니라 then 메서드 내부에서 발생한 에러도 캐치한다.

---

Promise를 사용하면 비동기 작업을 순차적으로 진행 하거나, 병렬로 진행할 수 있다. 또한 내부적으로 예외처리에 대해 구조가 탄탄해질 수 있다.

promise는 자바스크립트 비동기 처리에 사용되는 객체다. 특정 코드의 실행이 완료될 때까지 기다리지 않고 다음 코드를 먼저 수행하는 비동기를 처리한다.

promise를 사용하지 않고 api 호출시.. 데이터를 받아오기 전에 데이터를 받은 것 마냥 데이터를 표시하게 된다. 이 때, 오류가 발생하거나 빈화면이 노출된다. 이 문제를 promise로 해결할 수 있다.

## promise의 에러 처리는 catch()로 하자

then의 두번쨰 인자(function(err){})로 처리할 수 있지만, catch로 처리하는게 효율적이다.

then 콜백 함수에서 오류 발생시 오류를 제대로 잡지 못한다.

```
Uncaught (in promise) Error:
```

하지만 동일 오류를 catch로 잡으면

```
then error: error..
```
