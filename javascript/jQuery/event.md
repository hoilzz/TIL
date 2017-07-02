# bind, trigger

jQuery에서 custom global event 트리거 할 수 있다.

```javascript
jQuery.event.trigger('mycustomevent', [arg1, arg2, arg3]);
```

이것은 어떠한 엘리먼트에서도 트리거 될 수 있다.

jQuery는 DOM object 기반이므로, DOM object에 이벤트를 바인딩 해야한다. element 없이 이벤트를 바인드 할 방법이 있다. 근데 그건 지원되는 방법이 아니다.

만약 개별 페이지 엘리먼트에 바인딩 하기를 원치 않는다면 global DOM object에 이벤트를 바인딩 할 수 있다.
