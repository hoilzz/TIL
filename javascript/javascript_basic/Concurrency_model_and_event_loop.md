# Concurrency model and Event Loop

JS는 `event loop` 기반의 동시성 모델이다.

이 모델은 C와 JAVA와 같은 언어와 매우 다르다.

## Runtime concepts

Modern JS 엔진은 the described semantics를 구현하고 최적화한다.

### visual representation

![js's stack, heap and queue](https://developer.mozilla.org/files/4617/default.svg)

### Stack

함수 호출은 stack frames을 형성한다.

```javascript

function foo(b){
    var a = 10;
    return a + b + 11;
}

function bar(x){
    var y = 3;
    return foo(x*y);
}

console.log(bar(7));

```

`bar`를 호출할 때, first frame은 bar의 arguments와 지역 변수를 포함하여 생성된다.

`bar`가 `foo`를 호출할 때, second frame은 생성되고 foo의 인자와 지역변수를 포함한 stack의 맨 위에 푸쉬된다.

`foo`가 리턴할 때, top frame element는 스택에서 pop된다. (`bar`의 call frame만 놔둔채로)

`bar`가 리턴할 때, stack은 비어있다.


### Heap

Objects는 heap에서 할당된다.

힙은 대부분 구조화되지 않은 메모리 영역을 나타 내기위한 이름입니다.

### Queue

JS runtime은 처리될 메시지의 리스트인 `message queue`를 포함한다.

`함수`는 각 메시지와 연관되어있다.

stack이 충분한 수용력을 가질 때, 메시지는 큐에서 나오고 처리된다.

**`연관된 함수`를 호출하여 처리** 된다. (따라서 초기 stack frame을 생성한다)

stack이 다시 비어있을 때 메시지 처리는 끝난다.

### Run-to-Completion

각 메시지는 다른 메시지가 처리 되기 전에 완전히 처리된다.

이것은 함수가 실행될 때마다 선점 될 수없고 다른 코드가 실행되기 전에 완전히 실행되며 함수가 조작하는 데이터를 수정할 수 있다는 사실을 포함하여 프로그램에 대한 추론을 할 때 좋은 속성을 제공합니다.

이것은 C와는 다르다. 예를 들어, 함수가 쓰레드에서 실행된다면 다른 쓰레드에서 다른 코드를 실행하기 위해 어느 시점에서 멈출 수있다.

이 모델의 단점은 만약 메시지가 완료하기에 너무 오래 걸린다면, 웹 어플리케이션은 click or scroll 같은 user interaction을 처리할 수 없다. 브라우저는 `a script is taking too long to run` 대화상자로 이것을 완화시킨다. 좋은 practice는 처리할 메시지를 짧게 만들고 가능하다면 1개의 메시지를 여러개의 메시지로 줄이는 것이다.


### Adding msgs

웹 브라우저에서 이벤트가 일어나면 메시지는 추가된다.

그리고 그것에 event listener가 부착되어있다.

만약 리스너가 없다면, 이벤트는 사라진다.

그래서 click event handler가 있는 element에 대해 클릭하면 메시지를 추가한다.

`setTimeout`을 호출하면 2번째 인자의 시간이 지나면 큐에 메시지를 추가할 것이다.

만약 큐에 메시지가 없다면, 메시지는 바로 처리된다.

그러나, 만약 메시지가 있다면 `setTimeout` 메시지는 처리될 다른 메시지를 기다려야 한다.

**이러한 이유 때문에, 2번째 인자는 최소 시간을 가리키고 보장된 시간이 아니다.**


### Zero delays

Zero delay는 실제로 0ms 후에 콜백이 시작된다는 의미는 아니다.

0ms 지연으로 `setTimeout`을 호출하면 주어진 시간간격 후에 콜백 함수를 호출하지 않는다.

실행은 큐에 대기 중인 작업 수에 따라 다르다.

아래 예제에서 콜백에서 메시지가 처리되기 전에 `"this is just a message"` 메시지가 콘솔에 출력될 것이다.

왜냐하면 delay는 실행 중에 요청을 처리할 최소 시간이기 때문이다. 하지만 보장된 시간은 아니다.

```javascript
(function() {

  console.log('this is the start');

  setTimeout(function cb() {
    console.log('this is a msg from call back');
  });

  console.log('this is just a message');

  setTimeout(function cb1() {
    console.log('this is a msg from call back1');
  }, 0);

  console.log('this is the end');

})();
```
