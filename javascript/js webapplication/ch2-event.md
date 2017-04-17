# 이벤트와 이벤트 관찰

이벤트는 JS의 비표준 문제를 일으킨다.

## 2.1 이벤트 수신

`addEventListener()`는 이벤트의 핵심 함수로 세 가지 매개변수인 type(이벤트 종류), listener(콜백), useCaptuer를 포함한다. 이 중 type, listener두 매개변수로 DOM 엘리먼트에 함수 연결 가능하다.

```javascript
var button = document.getElementById("createButton");
button.addEventListener("click", function(){}, false);
```

addEventListener()를 호출시 넘겨준 매개변수를

removeEventListener()에 그대로 사용하는 방법으로 기존에 등록한 리스너를 제거할 수 있다.

리스너 함수를 익명 함수로 정의하면서 함수를 가리키는 레퍼런스를 보존하지 않았다면

엘리먼트 자체를 삭제하지 않고는 등록한 리스너를 삭제할 수 없다.

- 첫번쨰 인자로 이벤트 관련 정보를 포함하는 event 오브젝트를 전달한다.

e 오브젝트는 event propogation, 기본 동작 실행 방지 등 다양한 함수 제공.


## 2.2 이벤트 순서

특정 타입의 이벤트 처리하는 이벤트 핸들러를 엘리먼트와 엘리먼트의 부모가 동시에 포함하고 있는 상황을 가정하자.

이 떄 이벤트가 발생하면 누구의 이벤트 핸들러가 먼저 실행될까?

브라우저마다 다르다.

넷스케이프 4는 가장 상위 부모에서, 즉 바깥쪽에서 안쪽으로 이벤트를 실행하는 `이벤트 캡처링` 지원

MS는 엘리먼트에서 부모로 이벤트를 전파하는 즉, 안쪽에서 바깥쪽으로 이벤트를 실행하는 `이벤트 버블링` 지원

특별한 이유가 없다면 대부분은 event bubbling을 사용한다.


## 2.3 이벤트 취소

`stopPropogation()` 함수로 이벤트 버블링 중단 가능.

브라우저는 이벤트에 기본 동작을 제공한다.

예를 들어 브라우저는 링크를 클릭하면, 새 페이지 로드하고
체크박스 클릭시, 체크박스를 설정한다.

이러한 기본동작은 이벤트 전달과정이 끝난 다음 실행된다.

원한다면 이벤트 전달 과정에서 기본 동작을 취소할 수 있다.

`event.preventDefault()` 를 통해 기본동작을 막을 수 있다.

또는 핸들러에서 false를 반환해도 기본 동작이 실행되지 않는다.


## 2.4 Event Object

## 2.5 이벤트 라이브러리

대부분의 상황에서 JS로 이벤트 관리를 한다.

jQuery의 이벤트 관리 API를 사용하는 방법을 알아보자.

jQuery API는 브라우저 종류와 관계없이 이벤트 리스너를 추가할 수 있도록 `bind()` 함수를 제공한다.

jQuery 인스턴스에서 bind()를 호출할 수 있다. 이 때 이벤트 이름과 핸들러를 인자로 전달한다.

```javascript
$('#element').bind(eventName, handler);
```

jQuery는 click, submit, mouseover 등과 같은 이벤트 타입의 단축형을 제공한다.

```javascript
$('#myDiv').click(function(){})
```

페이지를 로드한 다음(엘리먼트 생성 후) 이벤트 추가할 수 있다.

윈도우 load 이벤트를 기다렸다가 load 이벤트가 발생하면 리스너를 추가할 수 있다.


결론적으로 커스텀 이벤트 사용시, 다른 개발자가 쉽게 **확장**할 수 있다.

## 2.10 DOM 이외의 이벤트

이벤트 기반 프로그래밍은 애플리케이션 구조를 `비결합화`할 수 있어서 강력하다.

비결합화하면, 독립성을 갖추며 유지보수하기 쉬워진다.

그러나 이벤트가 DOM에만 국한되는 것은 아니므로 자신만의 이벤트 핸들러 라이브러리를 만들 수 있다.

이벤트 핸들러 패턴으로는 `발행자/구독자 패턴`(PUB/SUB)이 있다.

발행자와 구독자라는 두 배우가 메시지를 주고 받는다.

발행자가 특정 채널로 메시지 발행시, 채널 구독자는 발생자가 메시지를 발행했다는 알림 수신한다.

여기서 핵심은 발행자와 구독자 서로 완전히 `비결합` 상태라는 점이다.

PUB/SUB 간 존재를 알지 못한다. 오직 채널 이름만 공유할 뿐이다.


공급자와 구독자의 비결합 특성을 적용하면, 상호연관성과 결합성을 만들지 않으면서 애플리케이션 기능 확장 가능하다.

애플리케이션에서 PUB/SUB 활용 방법은?

	1. **이벤트 이름과 관련한 핸들러를 저장**한 다음

	2. **각 핸들러를 호출할 수 있는 방법**을 마련하면 PUB/SUB 사용 가능

```javascript
var PubSub = {
    subscribe: function(ev, callback){
        // console.log("this === subscribe ", this === PubSub.subscribe);
        // _callbacks 오브젝트가 없으면 새로 만든다.
        var calls = this._callbacks || (this._callbacks = {});

        // 이벤트 키에 해당하는 배열이 없으면 배열을 만든 다음 콜백을 배열에 추가한다.
        (this._callbacks[ev] || (this._callbacks[ev] = [])).push(callback);
        return this;
    },

    publish:function(){
        // argumnets 오브젝트를 진짜 배열로 바꾼다
        var args = Array.prototype.slice.call(arguments, 0);

        // 이벤트 이름을 포함하는 첫 번째 인자를 추출한다
        var ev = args.shift();

        // callbacks 오브젝트가 없거나 해당 이벤트의 배열을 포함하지 않으면 반환한다
        var list, calls, i, l;
        if(!(calls = this._callbacks)) return this;
        if(!(list = this._callbacks[ev])) return this;

        // 콜백을 호출한다
        for (i = 0, l = list.length; i<l; i++){
            list[i].apply(this, args);
        }
    }
};


PubSub.subscribe("wem", function(){
    console.log("wem!");
});

PubSub.subscribe("user:create", function(name){
    console.log("user ", name, " created");
});

PubSub.publish("wem");
PubSub.publish("user:create", "hoil");
```

`콜론(:)` 같은 분리자를 이용해 이벤트 namespace를 만들 수 있다.

```javascript
PubSub.subscribe("user:create", function(){/*...*/})
```

jQuery를 이용하는 애플리케이션은 벤 알만이 제공하는 라이브러리를 활용해보자.

```javascript
(function($){
	var o = $({});
	$.subscribe = function(){
		o.bind.apply(o, arguments);
	}
	$.unsubscribe = function(){
		o.unbind.apply(o, arguments);
	}
	$.publish = function(){
		o.trigger.apply(o, arguments);
	}
})(jQuery);
```

jQuery는 jQuery 오브젝트에 직접 함수가 존재한다.

반면 벤 알만의 API는 publish()와 subscribe()로 호출한다.

```javascript
$.subscribe("/some/topic", function(e, a, b, c){
	console.log(e, a+b+c);
})

$.publish("/some/topic", "a", "b", "c");
```

```javascript
var Asset = {};

jQuery.extend(Asset, PubSub);

Asset.subscribe("create", function(){..})
```

jQuery의 `extend()` 함수를 이용해 PubSub의 프로퍼티를 Asset 오브젝트로 복사하였다.

이 방법으로 모든 `publish()`, `subscribe()` 호출을 Asset 범위로 한정하였다.

**`ORM의 이벤트`, `상태 머신 변화`, `Ajax 요청 종료시 발생하는 콜백` 등의 상황에서 이 기법을 유용하게 활용할 수 있다.**
