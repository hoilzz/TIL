# Custom Event

`.on`, `.trigger`

`.on`
- `event type`과 `event handling` 함수를 인자로 받는다.
- event 관련 `데이터`도 옵션으로 받을 수 있다.(두번째 인자로 받는다. 이벤트 핸들링 함수는 세번째 인자가 된다.)
- 인자로 전달된 데이터는 이벤트 핸들링 함수에서 이벤트 오브젝트의 `data` property 이용가능하다. 이벤트 핸들링 함수는 항상 첫번째 인자로 이벤트 오브젝트를 받는다.

`.trigger`
- 인자로 이벤트 타입을 받는다.
- 옵션으로 값의 배열을 받는다. 이 값은 이벤트 핸들링 함수로 전달된다.

예제를 보자.

```javascript
$(document).on("myCustomEvent", {
	foo:"bar"
}, function(event, arg1, arg2){
	console.log(event.data.foo); // "bar"
	console.log(arg1, arg2);
});

$(document).trigger("myCustomEvent", ["bim", "baz"]);
```

## summary

커스텀 이벤트는 이벤트를 트리거 하는 엘리먼트가 아닌 행위의 대상에 중점을 둔다. 만약 어플리케이션의 작은 부분이 보여야 하는 동작을 설명해야 한다면 커스텀 이벤트는 그 동작들을 조사 할 수 있는 강력한 방법을 제공한다.
