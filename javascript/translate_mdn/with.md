# with

with 문은 scope chain을 확장한다.

## syntax

> with(expression)
>   statement

expression
: statement를 평가할 때 사용된 scope chain에 주어진 표현식을 추가한다. 표현식 주변에 {}는 필수다.

statement
: Any statement. 여러개의 statement를 실행하기 위해, 여러개의 statements를 그루핑 하기 위해 block statement를 사용해라.

## description

JS는 실행 컨텍스트에서 연관된 scope chain을 검색하여 값을 찾을 수 없는 변수 or 함수를 찾는다.

`with` statement는 statement 본문을 평가하는 동안 해당 scope chain의 head(가장 위에?)에 주어진 object를 추가한다.

만약 값을 찾을 수 없는 이름이 scope chain의 프로퍼티와 매치된다면, 그 이름은 그 프로퍼티와 프로퍼티를 포함한 오브젝트에 바운딩된다.

만약 scope chain에 매치되는 프로퍼티가 없다면, `ReferenceError`가 발생한다.

> with 사용하기는 추천되지 않는다. ES5 strict mode에서 사용 금지 되었다. 추천하는 대안은 너가 임시 변수로 접근하기를 원하는 프로퍼티를 가진 오브젝트를 할당하는 것이다.

### performance pro & contra

Pro

with statement는 성능 페널티 없이 매우 긴 오브젝트 레퍼런스를 반복할 필요를 감소시켜서 file size를 감소시는데 도움을 준다. `with`에 필요한 scope chain 변경은 계산적으로 비용이 들지 않는다. `with`의 사용은 인터프리터가 반복된 object 참조를 파싱 하는 횟수를 감소시킨다..? 그러나, 대부분의 경우에, 원하는 객체에 대한 참조를 저장하는 임시 변수를 사용하여 이러한 이점이 성취된다.

Contra

`with` statement는 명시된 오브젝트가 모든 이름 검색에서 첫번째로 검색되도록 한다. 그러므로 명시된 오브젝트의 멤버가 아닌 모든 식별자는 `with` block에서 더 천천히 발견된다. 성능이 중요한 곳에서 `with`는 지정된 객체의 멤버에 접근하는 코드 블록을 포함하는 데만 사용해야 한다. (상위 scope에서 데이터 가져오는 경우 추가 처리 시간 소요된다,)


### Ambiguity contra

Contra: `with` 문은 사람이 읽기에도, js compiler가 unqualified 이름을 scope chain에서 찾을지 만약 그렇다면 어떤 객체인지 결정하기에도 어렵다. 다음 예제를 보자.

```javascript
function f(x, o){
    with (o){
        console.log(x);
    }
}
```

`f`가 호출 됐을 때, `x`는 찾아질 수도 있고 아닐 수도 있다.

만약 찾아진다면 `o` 안에서 혹은 (그러한 property는 존재하지 않는다면) x가 첫번째 형식 매개변수인 곳 `f`의 AO(activation object)안에 있다.

만약 2번째 객체로 통과 시킨 객체 내에서 `x`를 정의하는 것을 잊는다면

혹은 만약 비슷한 버그가 있으면 에러를 걱정하지 마라. 단지 예상치 못한 결과가 있다.

Contra: `with`를 사용한 코드는 특히 plain object가 아닌 것으로 사용될 때, 하위 호환되지 않을 수 있다. 다음 예제를 보자.

```javascript
function f(foo, values){
	with(foo){
		console.log(values);
	}
}
```

만약 ECMAScript 5에서 `f([1,2,3], obj)`를 호출한다면,

`with`문 내의 `values`값 참조가 `obj`로 해석된다.

그러나, ECMAScript 6은 `values` property를 `Array.prototype`으로 소개한다. (그래서 모든 array 에서 이용할 수 있다.)

그래서 ES6을 지원하는 JS 환경 안에서는, `with`문 내의 `values` 참조 값은 `[1,2,3].values`로 해석된다.


## Example

다음 `with`문은 `Math` object가 default object인 것을 명시한다.

`with`문 다음의 명령문은 `PI` property와 `cos`, `sin` method를 객체 명시 없이 참조할 수 있다.

```javascript
var a, x, y;
var r = 10;

with(Math){
	a = PI * r * r;
	x = r * cos(PI);
	y = r * sin(PI / 2);
}
```

`with`를 효율적으로 사용하는 방법.

```html
<div id="divWith0">Click me! DIV 0</div>
<div id="divWith1">Click me! DIV 1</div>
<div id="divWith2">Click me! DIV 2</div>

<script>
var i, len = 3;
for (i = 0; i < len; i++) {
	with ({num: i}) {
		document.getElementById("divWith" + num)
				.addEventListener("click", function () {
					 alert("You clicked div #" + num); }, false);
	}
}
</script>
```

JS의 비동기적인 콜백 함수의 특성과, scope의 지속성이 합쳐진 결과.

- 차이를 알고싶다면 `with` 줄을 제거하고, `num`을 `i`로 변경하면 된다.


## summary

정의

- with문은 scope chain을 확장한다.
- with문은 괄호안의 객체를 해당 scope chain에 추가한다.

장점

- 성능 페널티 없이 긴 object reference 반복을 감소할 수 있다. 이로 인해 file size도 감소한다.
- 하지만 이것은 원하는 객체에 대한 참조를 저장하는 임시변수를 사용하면 해결된다.

단점

- 명시된 object는 all name lookup에서 먼저 검색된다. 반대로 명시된 object의 멤버가 아닌 모든 식별자는 `with`문에서 더 천천히 발견된다.
	- 퍼포먼스가 중요한 곳에서, `with`은 무조건 명시된 object의 멤버를 접근하는 코드 블록 내에서만 사용되어야 한다.

**모호성 문제**

```javascript
function doSomething(value, obj) {
	with (obj) {
		value = "which scope is this?"; console.log(value);
	}
}
```

- 여기서 value는 obj의 property 혹은 function formatting argument일 수 있다. 이러한 상황을 방지하기위해 with문 사용을 자제해야 한다.
- 대신 임시변수에 저장하는 것을 활용하자.

## 참고

[with 명령에 대하여](http://unikys.tistory.com/304)
[with in MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/with)
