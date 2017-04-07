# event loop

Node.js는 Event를 사용한다.

서버 가동시, 변수들을 initialize하고, 함수를 선언하고 이벤트 발생할 때까지 기다린다.

Event-Driven 어플리케이션은, 이벤트를 대기하는 메인 루프가 있다.

그리고 이벤트 감지시 Callback 함수를 호출한다.

**이벤트가 콜백과 비슷해 보일 수 있다.**

차이점은
- `콜백함수`는 비동기식 함수에서 결과를 반환할 때 호출된다.
- 하지만, `이벤트 핸들링`은 옵저버 패턴에 의해 작동된다.

## how to work

EventListener 함수들이 옵저버 역할을 한다. 옵저버들이 이벤트를 기다리다가, 이벤트가 실행되면 이벤트를 처리하는 함수가 실행된다.

Node.js에는 `events` 모듈과 `EventEmitter` 클래스가 내장되어있다. 이를 사용하여 이벤트와 이벤트 핸들러를 연동(bind) 시킬 수 있다.

```javascript
// event 모듈 사용
var events = require('events');

// EventEmitter 객체 생성
var eventEmitter = new events.EventEmitter();
```

이벤트 핸들러와 이벤트를 연동(bind)시키는건 다음과 같다.

```javascript
// event와 EventHandler를 연동(bind)
// eventName은 임의로 설정 가능
eventEmitter.on('eventName', eventHandler);
```

프로그램 안에서 이벤트 발생하는 방법은 다음과 같다.

```javascript
eventEmitter.emit('eventName');
```

### 이벤트 핸들링 예제

main.js

```javascript
var events = require('events');

var eventEmitter = new events.EventEmitter();

var connectHandler = function connected(){
  console.log("Connection Successful");

  // data_received 이벤트를 발생시키기
  eventEmitter.emit("data_received");
}

eventEmitter.on('connection', connectHandler);

eventEmitter.on('data_received', function(){
  console.log("Data Received");
})

eventEmitter.emit('connection');

console.log('Program has ended');
```
