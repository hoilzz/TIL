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

```javascript
$(window).bind("load", function(){
    $('#signinForm').submit(checkForm);
})
```

윈도우의 load를 기다리는 것보다 `DOMContentLoaded`를 기다리는 것이 실용적이다.

DOM이 준비된 다음에 페이지의 이미지와 스타일시트를 내려받는다.

`DOMContentLoaded`는 페이지의 이미지와 스타잏시트를 내려받기 전에 실행된다.

즉 사용자가 페이지와 상호작용을 하기 전에 항상 DOMContentLoaded가 먼저 호출된다.

근데, 모든 브라우저가 해당 이벤트를 지원하지 않는다.

그래서 jQuery는 `.ready(callback)` 함수로 이 기능을 추상화 했다.

## 2.6 컨텍스트 변경

**핸들러가 실행 될 때 컨텍스트가 바뀔 수 있는데** 이는 이벤트에서 가장 혼동을 줄 수 있는 부분이다.

addEventListener()를 이용시 `기존 지역 컨텍스트`가 대상 `HTML 엘리먼트 컨텍스트`로 바뀐다.

```javascript
new function(){
    this.appName = "wem";

    document.body.addEventListener("click", function(e){
        // 컨텍스트가 바뀌었으므로 appName이 정의되지 않음
        alert(this.appName);
    }, false);
}
```

원래 컨텍스트를 보존하려면 **`익명 함수`로 핸들러를 감싸서** 원래 컨텍스트의 레퍼런스를 유지해야 한다.

프록시 함수로 현재 컨텍스트를 유지하는 방법을 살펴 볼 때 이 패턴을 활용 했다.

jQuery의 proxy() 함수 패턴 즉, `실행할 함수`와 `원하는 컨텍스트`를 넘겨주는 방식을 널리 사용한다.

```javascript
$('signinForm').submit($.proxy(function(){..}, this));
```

이 부분은 잘 모르겠다..


## 2.7 이벤트 위임

이벤트 버블링은 자식의 이벤트를 검사할 수 있도록 부모에 리스너를 추가한다.

즉, 부모에 리스너를 추가하는 방식으로 이벤트 리스너 수를 줄인다

```javascript
// ul 리스트의 이벤트 위임
list.addEventListener("click", function(e){
    if(e.curentTarget.tagName == "li"){
        ...
        return false;
    }
}false)
```

jQuery는 이 기능을 편리하게 제공한다.

`delegate()` 함수에 자식 셀렉터, 이벤트 타입, 핸들러를 넘겨줘서 이벤트를 위임할 수 있다.

이 방법을 사용하지 않는다면 모든 li 엘리먼트에 클릭 이벤트를 추가해야 한다.

따라서, 이를 이용해 이벤트 리스너 수를 줄이고 성능 개선할 수 있다.

```javascript
// 모든 li 엘리먼트에 리스너를 추가하는 방식은 피하자.
$("ul li").click(function(){..});

한 개의 이벤트 리스너만 추가한다.
$("ul").delegate("lio", "click", /*..*/);
```

## 2.8 커스텀 이벤트

커스텀 이벤트는 라이브러리 구조를 만드는 데 필수적인 패턴이다.

그래서 많은 jQuery 플러그인이 사용하는 좋은 방법이다.

만드려면 jQuery나 Prototype 등의 라이브러리를 이용해야한다.

jQuery에서는 `trigger()` 함수로 커스텀 이벤트 발생시킬 수 있다.

`이벤트 이름`을 이용해 namespace를 사용할 수 있다. namespace는 마침표와 역순으로 구분한다.

```javascript
// 커스텀 이벤트 바인드
$(".class").bind("refresh.widget", function(){});

// 커스텀 이벤트 발생
$(".class").trigger("refresh.widget");
```

trigger() 함수에 인자를 추가하여 이벤트 핸들러로 데이터 전달 가능하다.

```javascript
$('.class').bind("frob.widget", function(event, dataNumber){
    console.log(dataNumber);
})

$(".class").trigger("frob.widget", 5);
```

네이티브 이벤트(브라우저 기본 이벤트)와 마찬가지로 커스텀 이벤트도 DOM 트리에서 전파된다.


## 2.9 커스텀 이벤트와 jQuery 플러그인
