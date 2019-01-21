# channel

채널은 외부 이벤트 소스 or 사가 간 통신을 위해 해당 이펙트를 일반화.
또한, 스토어에서 특정 작업을 대기열(queue)에 넣을 때에도 사용.

살펴볼 것
- `yield actionChannel` : 이펙트를 이용해 스토어의 특정 액션을 버퍼링.
- `eventChannel` : 팩토리 함수를 사용하여 take 이펙트를 외부 이벤트 소스에 연결.
- channel 팩토리 함수를 이용하여 채널 만드는 방법, 사가 간 통신을 위해 take/put 이펙트에 이를 사용하는 방법.

## actionChannel 이펙트 사용.

```js
function* watchRequests() {
  while(true) {
    const {payload} = yield take('REQUEST');
    yield fork(handleRequest, payload)
  }
}

function* handleRequest(payload) {...}
```

__전형적인 watch와 fork 패턴__

- watchRequests 사가는
  - block을 피하고
  - 어떤 action도 놓치지 않기 위해 fork를 사용.

- handleRequest 태스크는
  - 각 REQUEST action에서 생성됨.
  - 짧은 시간에 많은 액션이 들어온다면 동시에 많은 handleRequest 태스크가 실행됨.

- 그래서 아직 처리되지 않은 액션을 대기열(queue)에 푸시할거임.
  - 그리고 현재 요청 마치면 대기열에서 다음거 가져올거임.

__`actionChannel`을 통해 위에서 말한거 할 수 있음__
- 위에 코드 바꿔보자.

```js
function* watchRequests() {
  // 1. request action에 대해 channel 생성
  const requestChan = yield actionChannel('REQUEST');

  while(true) {
    // 2. channel에서 가져오기.
    const {payload} = yield take(requestChan);
    // 3. block call 이용한다고 알리기
    yield call(handleRequest, payload)
  }
}
```

actionChannel은 채널 만들기
- take(pattern)과 차이점은, 사가가 아직 처리할 준비가 되지 않았다면 (예를 들어 API 호출에 block됨)
  - actionChannel은 들어오는 __메세지를 버퍼링__ 할 수 있음

## eventChannel 팩토리를 사용해 외부 이벤트 연결하기

actionChannel처럼, eventChannel은 리덕스 스토어가 아닌 외부 이벤트를 위한 채널을 생성.

__일정 간격마다 채널 생성__ 하기 예제

```js
import { eventChannel, END } from 'redux-saga';

function countdown(secs) {
  return eventChannel(emitter => {
    const iv = setInterval(() => {
      secs -= 1;
      if(secs > 0) {
        emitter(secs)
      } else {
        // 채널이 닫히도록 함.
        emitter(END)
      }
    }, 1000);
    // subscriber는 unsubscribe 함수를 리턴해야함.
  })
}
```

eventChannel
- 첫번째 인자는 subscriber 함수
- 구독자의 역할은
  - 외부 이벤트 소스 초기화 (setInterval)
  - 제겅된 emitter를 실행하여 소스에서 채널로 들어오는 모든 이벤트를 라우팅.
  - 매 초마다 emitter를 호출.

- emitter(END) : 채널 소비자에게 채널 폐쇄됨을 알림.

채널 사용 방법 보자

```js

// 초 간격으로 이벤트 채널 생성하기
function countdown(seconds) { ... }

export function* saga() {
  const chan = yield call(countdown, value)
  try {
    while (true) {
      finally block으로 점프하여 sga가 종료하도록 유도
      // take(END) will cause the saga to terminate by jumping to the finally block
      let seconds = yield take(chan)
      console.log(`countdown: ${seconds}`)
    }
  } finally {
    console.log('countdown terminated')
  }
}
```

`take(chan)`을 yield하고 있음.
- 메시지가 채널에 들어가기 전까지 사가는 block됨.
- countdown의 interval 종료시, countdown 함수는 emitter(END)를 호출하여 이벤트 채널 폐쇄
  - 채널 닫으면 take에 block된 모든 사가들을 종료시키는 효과 있음.

## 사가 간 통신체 채널 사용하기

action channel, event channel 외에 어떤 거에도 연결되지 않은 채널 직접 생성 가능.
- 채널에 수동으로 put 가능.
- 사가 간에 통신을 하기 위해 채널 사용.

```js
function* watchRequests() {
  while (true) {
    const {payload} = yield take('REQUEST')
    yield fork(handleRequest, payload)
  }
}

function* handleRequest(payload) { ... }
```


watch와 fork패턴이
동시에 실행되는 태스크의 개수에 제한 없이 동시에 다수 요청 처리 가능.

actionChannel 이펙트를 이용하여 한 번에 하나의 태스크만 실행되도록 제한 가능.

최대 3개의 태스크를 한번에 실행해보자.

3개보다 적은 태스크를 실행하고 있다면, 요청 즉시 실행.
그게 아니라면 3개의 슬롯 중에 1개의 태스크가 끝나기전까지 대기열에 요청 집어넣을거임.

```js
import {channel} from 'redux-saga';

function* watchRequests() {
  // create a channel to queue incoming requests
  const chan = yield call(channel)

  // create 3 worker 'threads'
  for (var i = 0; i < 3; i++) {
    yield fork(handleRequest, chan)
  }

  while (true) {
    const {payload} = yield take('REQUEST')
    yield put(chan, payload)
  }
}

function* handleRequest(chan) {
  while (true) {
    const payload = yield take(chan)
    // process the request
  }
}
```


3개의 워커 saga를 fork.
- 생산된 채널이 fork된 모든 saga에 인수로 들어감.
- watchRequests는 3개의 워커 사가들에게 일을 dispatch하기 위해 채널을 사용.
- 각 request action마다 saga는 채널에 payload를 put할거임.
  - 이는 할 일이 없는 워커 사가에게 전달.
  - 이게 아니라면 워커 사가가 준비 될 때까지 채널 대기열에 들어감.
- while 반복으로 3개의 워커가 req 액션을 가져가거나, 요청으로 만들어진 메시지가 있을 때까지 block됨.
- 이 메커니즘이 3개의 워커 칸 자동 로드밸런싱을 해줌.

## Summary

채널은
- 외부 이벤트 소스
- 사가 간 통신
- 특정 작업을 대기열에 넣을 때에도 사용.

1. actionchannel
2. eventChannel
3. channel 팩토리 함수를 이용하여 채널 만듬. 사가 간 통신을 위해 take/put 사용.

---

1. action channel
- 들어오는 메시지를 큐에 버퍼링할 수 있음.

2. event Channel
- 리덕스 스토어가 아닌 외부 이벤트(emitter를 setInterval에 전달) 를 위한 채널 생성.

3. saga에서 channel 가져와서 call을 통해 직접 생성.
- 보통 한번에 1개의 태스크만 실행되도록 함.
- fork(generator func, channel)하여 여러개의 태스크를 한번에 실행 가능.

사실 1번빼고는 감이 안옴. 예제를 통해 알아보자.
