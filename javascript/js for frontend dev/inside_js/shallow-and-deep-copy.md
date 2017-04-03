# shallow and deep copy

## jQuery.extend()

2개 이상의 객체를 하나의 객체로 머지한다.

### syntax

`jQuery.extend(target [,object1][,objectN])`

target (Object)
: 만약 추가 객체가 인자로 전달되거나 jQuery namespace가 유일한 인수인 경우, 새 속성을 수신할 객체다.

object
: 머지하기 위한 추가 속성을 가진 오브젝트

2개 이상의 오브젝트 인자가 `$.extend()`에 전달될 때, 모든 오브젝트의 속성들은 타겟 오브젝트에 추가된다. null이나 undefined는 무시된다.

만약 1개의 인자만 전달된다면, 이것은 타겟 인자가 생략됐다는 것을 의미한다. 이 경우에, jQuery object를 타겟으로 간주한다. 이렇게 해서, 너는 jQuery namespace에 새로운 함수를 추가할 수 있다.

target object(첫번째 인자)는 수정되는 점을 기억해라.
그리고 `$.extend()`로부터 반환 될 것이다.
그러나 만약 original object를 보호하고 싶다면, target에 빈 객체를 전달하면 된다.

```javascript
var object = $.extend({}, object1, object2);
```

`$.extend()`의 머지는 기본적으로 리커시브는 아니다.

만약 첫번째 인자의 프로퍼티가 `object`나 `array`면,

2번째나 뒤이은 오브젝트에서 동일한 키를 가진 프로퍼티에 의해 완전히 덮어쓰기가 된다.

값은 머지되지 않는다. 아래 예제에서 바나나 값을 조사해보면 알 수 있다.

**그러나**, 첫번째 인자로 `true`를 전달하면, 오브젝트는 리커시브하게 머지될 것이다.
