# window.history

DOM window 객체는 브라우저의 세션 history의 접근자를 제공한다.

- history stack의 컨텐츠 제어하기
- history forth and back

## 브라우저 히스토리 다루기

```js
// history 앞 뒤로 움직이기
window.history.back();
window.history.forward();

// history의 특정 지점으로 가기
window.history.go(-1);
window.history.go(1);

let numberOfEntries = window.history.length;
```

## history entries를 추가하고 수정하기

HTML5는 다음 메서드를 도입했다.

- history.pushState
- history.replaceState

위 메서드는 `onpopstate` event와 함께 동작한다.

### pushState 예제

```js
// http://mozilla.org/foo.html에서 다음 스크립트를 실행.
let stateObj = { foo: "bar" };

history.pushState(stateObj, "page 2", "bar.html");
```

결과는

- http://mozilla.org/bar.html로 URL이 변경됨.
- 브라우저가 `bar.html`를 실제로 로드하지 않고 `bar.html`의 존재 여부를 확인하지 않음

위 상태에서 google.com 갔다가 뒤로가기 눌러보자.

- URL은 `http://mozilla.org/bar.html`이고
- `history.state`는 `stateObj`를 포함한다.
- `popstate` event는 일어나지 않는다.
  - page가 reload 되지 않았기 떄문이다.

또 뒤로가기 눌러보자.

- URL은 `http://mozill.aorg/foo.html` 이고
- document는 `popstate` event를 얻는다.
- state object는 null이다.
- 마찬가지로 문서의 contents 변화는 없다.

## pushState 메서드 톺아보기

3가지 파라미터

1. state object
2. title
3. URL

**state object**
state object는 `pushState`로 생성된 new history entry와 연관이 있다. 유저가 new state로 이동할 때마다, `popstate` event는 발생하고 이벤트의 `state` 프로퍼티는 history entry의 state object의 카피본을 가지고 있다.
