# binding

클라의 뷰 렌더링 시 실제 효과를 느낄 수 있는 기능이 바인딩.
- 뷰 엘리먼트와 JS오브젝트를 연결하는 것을 의미
- JS 오브젝트가 바뀌면 새로 바뀐 오브젝트를 자동으로 뷰에 반영

즉, **뷰와 모델을 바인딩하면 애플리케이션의 모델이 바뀔 때마다 뷰가 자동으로 갱신**된다.

바인딩은 중요하다.
바인딩 덕분에 **레코드 변경이 자동으로 반영**이 되고, 컨트롤러가 처리할 작업이 줄어든다. **바인딩 기능은 실시간 애플리케이션의 기반**이기도 하다.

JS 오브젝트와 뷰를 바인드하려면 오브젝트의 프로퍼티가 바뀔 때 뷰를 업데이트할 콜백이 필요하다.

JS 오브젝트와 뷰를 바인드 하기 위해 **오브젝트의 프로퍼티가 바뀔 때 뷰를 업데이트할 콜백이 필요**하다. 문제는 JS 자체에서 이 방법을 제공하지 않는다. JS 게터와 세터를 이용해도 이 기능을 흉내낼 순 없다.

```javascript
var addChange = function(ob){
	ob.change = function(callback){
		if(callback){
			if( !this._change ) this._change = [];
			this._change.push(callback);
		} else{
			if( !this._change ) return;
			for( var i = 0; i<this._change.length; i++){
				this._change[i].apply(this);
			}
		}
	}
}
```

`addChange()`는 자신에게 전달한 오브젝트에 `change()` 함수를 추가하는 함수다.

`change()`함수는 jQuery의 change 이벤트와 같은 방식으로 동작한다.

```javascript
var object = {};
object.name = "Foo";

addChange(object);

object.change(function(){
	console.log("change now", this);
});

object.change();

object.name = "Bar";
object.change();
```

## .change()

jQuery의 change

JS event `change`의 이벤트 핸들러를 바인딩 하거나
엘리먼트의 이벤트를 trigger 한다.

> .change(handler)
handler : 이벤트 트리거 될 때마다 실행될 함수.

>.change([eventData], handler)
eventData : 이벤트 핸들러에 전달될 데이터를 포함한 객체
handler   : 이벤트가 트리거 될 때마다 실행될 함수

이 메서드는 `.on("change", handler)`에 대한 shortcut이다.

`change` event는 값이 변할 때 엘리먼트에 전송된다. 이 이벤트는 `<input>`, `<textarea>` boxes and `<select>` element에 제한되어있다. `select`, `checkbox`, `radio` 들은 유저가 마우스로 선택할 때 이벤트는 즉시 발생한다. 하지만 다른 엘리먼트 타입의 경우, 엘리먼트가 focus가 빠질 때 이벤트가 발생한다.

```html
<form>
  <input class="target" type="text" value="Field 1">
  <select class="target">
    <option value="option1" selected="selected">Option 1</option>
    <option value="option2">Option 2</option>
  </select>
</form>
<div id="other">
  Trigger the handler
</div>
```

이벤트 핸들러는 text input과 select box에 바운드 된다.

```javascript
$( ".target" ).change(function() {
  alert( "Handler for .change() called." );
});
```

2번째 옵션이 드롭다운에서 선택 되면, alert는 dp된다. 만약 너가 필드 안의 텍스트를 바꾸고 click away 하면 또 dp된다. 만약 컨텐츠가 바뀐거 없이 필드가 focus를 잃으면 이벤트는 트리거 되지 않는다. 이벤트를 수동으로 트리거하려면 인자 없이 apply `.change()`해라.

## 모델 바인딩

이제 바인딩을 모델에 적용해보자.

모델 레코드를 만들거나, 갱신하거나, 제거할 때마다 change 이벤트를 발생시켜 뷰를 갱신한다. 아래 예제에

	- 이벤트 바인딩과 발생을 설정
	- change 이벤트에 리스너를 등록
	- 이벤트가 발생하면 뷰를 갱신하는 작업을 수행하는 기본적인 User 클래스

```html
<script type="text/javascript">
var User = function(name){
	this.name = name;
}

User.records = [];

User.bind = function(ev, callback){
	var calls = this._callbacks || (this._callbacks = {});
	(this._callbacks[ev] || (this._callbacks[ev]=[])).push(callback);
}

User.trigger = function(ev){
	var list, calls, i, l;
	if (!(calls = this._callbacks)) return this;
	if (!(list = this._callbacks[ev])) return this;
	$.each(list, function(){this()});
}

User.create = function(name){
	this.records.push(new this(name));
	this.trigger("change");
}

$(function($){
	User.bind("change", function(){
		// 현재 유저만 추가하는 방법
		var template = $("#userTmpl").tmpl(User.records);

		$("#users").empty();

		$("#users").append(template);
	});
})
</script>
<script id="userTmpl" type="text/x-jquery-tmpl">
	<li>${name}</li>
</script>
<ul id="users">
</ul>

<script>
	User.create("Sam Seaborn");
</script>
```
