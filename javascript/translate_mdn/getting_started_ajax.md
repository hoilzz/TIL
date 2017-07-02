# Ajax 시작하기

Ajax의 기본을 익히며, 두 가지 훈련용 예제를 해보자.

## Ajax란?

비동기 Javascript와 XML을 말한다.
간단히 말하면, 서버측 scripts와 통신하기 위한 XMLHttpRequest 객체를 사용하는 것이다.
서버측으로 다양한 형식(JSON, XML, HTML 및 일반 텍스트 형식 등)의 정보를 주고 받을 수 있다. AJAX의 강력한 특징은 페이지 전체를 refresh하지 않고도 수행 되는 `비동기성`이다. **이러한 비동기성을 통해 사용자의 Event가 있으면 전체 페이지가 아닌 일부분만 업데이트할 수 있다.**

정리하면,

	- 페이지 일부분을 업데이트하기 위해 정보를 서버에 요청 가능
	- 서버로부터 받은 데이터로 작업하기

## 1. HTTP Request 만들기

JS를 이용하여 서버로 보내지는 HTTP Request를 만들기 위해 이런 기능을 제공하는 `클래스 인스턴스`가 필요하다.

IE는 XMLHTTP라고 불리는 ActivX object다.
MS의 ActiveX객체의 메서드와 프로퍼티를 제공하기 위해 Mozilla, safari 등 다른 브라우저는 XMLHttpRequest클래스를 구현하고 있다.

따라서 다음과 같이 하면 모든 브라우저에서 사용가능한 인스턴스 생성

```javascript
var httpRequest;
if(window.XMLHttpRequest){
	httpRequest = new XMLHttpRequest();
}
```

다음 서버로 보낸 요청에 대한 응답을 받았을 때 어떤 동작 수행할지 정의해야 한다.

```javascript
httpRequest.onreadyStatechange = function(){
	// process the server response
}
```

다음으로, 응답 받은 후 동작 결정한 다음에, 실제 request를 하는 것이다.

HTTP request class의 `open()`과 `send()`파일을 아래와 같이 호출해야 한다.

```javascript
httpRequest.open('GET', 'http://www.example.org/some.file', true);
httpRequest.send(null);
```

- `open()`
	- 첫번째 파라미터는 reqeust method, 걍 표준대로 대문자로 표기
	- 요구할 페이지의 URL. permission denied 에러를 받지 않기 위해 정확한 도메인 네임 사용해야 한다.(예를 들어 `domain.tld` 하지 말고, `www.domain.tld`로 해야 한다.)
	- 세번째 파라미터는 Asynchronous 수행 여부 결정한다.

- `send()`
	- 파라미터는 POST 방식으로 request 보낼 경우, 서버로 보낼 어떠한 데이터라도 가능.

	- 이때 데이터는 서버에서 쉽게 parse할 수 있는 형식이어야 한다.

	```javascript
	"name=value&anothername="+encodeURIComponent(myVar)+"&so=on"
	```

	- `json`, soap 등과 같은 다른 형식도 가능하다.
	- 만약 `POST`로 보낸다면 request의 MIME type은 `Content-Type : application/x-www-form-urlencoded`로 설정해야 한다.

## 2. 서버 응답에 대한 처리

해당 함수에서는 요구의 상태값을 검사할 필요가 있다. 만약 상태값이 4라면 서버로부터 모든 응답을 받았고 이를 처리할 준비가 되었다는 뜻이다.

```javascript
if (http_request.readyState == 4) {
    // 이상 없음, 응답 받았음
} else {
    // 아직 준비되지 않음
}
```

- readyState가 가질 수 있는 값의 목록은
	- 0 : uninitialized
	- 1 : loading
	- 2 : loaded
	- 3 : interactive
	- 4 : complete

다음으로 검사할 것은 HTTP 서버 응답의 상태 코드다.
200의 경우만 검사하자.

```javascript
if (http_request.status == 200){
	// 이상 없음
} else{
	// 요구 처리 과정에서 문제가 생김
	// 404(not found) or 500(internal server err)
}
```

request와 response의 상태 코드를 검사했다.
서버에서 받은 데이터를 통해 원하는 작업을 수행하자.
위의 데이터에 접근하기 위한 2가지 옵션이 있다.

	1. http_request.responseText : 서버의 응답을 텍스트 문자열로 반환할 것이다.
	2. http_request.responseXML : 서버의 응답을 XMLDocument 객체로 반환하여 JS의 DOM 함수들을 통해 이 객체를 다룰 수 있다.

## 3. 간단한 예제

간단한 HTTP 요구를 수행해보자.
`I'm a test`라는 문장이 적힌 `test.html`이라는 HTML 문서를 요구하여 문서의 내용을 파라미터로 `alert()`함수 호출해보자.

```html
<span id="ajaxButton">
	Make a request
</span>
<script type="text/javascript">
(function(){
	var httpRequest;
	document.getElementById("ajaxButton").onclick = function() {makeRequest('test.html');}

	function makeRequest(url) {
		if(window.XMLHttpRequest) {
			httpRequest = new XMLHttpRequest();
		} else if (window.ActiveXObject){
			try{
				httpRequest = new ActiveObject("Msxml2.XMLHTTP");
			} catch(e){
				try{
					httpRequest = new ActiveXObject("Microsoft.XMLHTTP");
				}
				catch(e){}
			}
		}
		if(!httpRequest){
			alert('Giving up : ( Cannot create an XMLHTTP instance)');
			return false;
		}
		httpRequest.onreadystatechange = alertContents;
	    httpRequest.open('GET', url);
	    httpRequest.send();
	}

	function alertContents(){
		if (httpRequest.readyState === 4){
			if(httpRequest.status === 200){
				alert(httpRequest.responseText);
			} else{
				alert('There was a problem with the request');
			}
		}
	}
})();
</script>
```

이 예제에서
	- Make a request 링크 클릭
	- 같은 디렉토리 내의 HTML 파일의 이름인 test.html을 파라미터로 하여 makeRequest() 함수 호출.
	- 브라우저는 서버로 요청 보냄. onreadyStatechange에 설정된 alertContents() 함수 수행
	- alertContents() 함수는 서버로부터 응답을 받았는지, 정상적으로 처리된 응답인지 검사
	- 제대로 되있다면 test.html 파일의 내용을 파라미터로 alert 호출

주 1
: IE에서 동작하는 page 만들 경우, Mozilla용에서 추가적으로 다음과 같은 작업 필요. 정적 XML 파일이 아니라, XML을 받기 위한 요청 보낼 때, 응답헤더 설정해야 한다. 헤더에 `Content-Type:application/xml` 설정하지 않으면, IE는 접근하고자 하는 XMl 요소 다음라인을 수행한 직후 `Object Expected` JS error를 발생시킨다.

주 3
: http_request 변수가 전역 사용시, makeRequest()함수를 호출하는 여러 함수 사이에서 경쟁 상태가 발생할 수 있다. 이 경우 다른 데이터를 덮어쓰게 된다. 이를 방지하기 위해 http_request 변수를 함수 내의 지역 변수를 선언해야 한다.

## summary

1. HTTP Request 만들기
	- `.onreadyStatechange` : 서버로 보낸 요청에 대한 응답 받았을 때 수행할 동작 정의하기

	- `open(HTTPmethod,url,isAsynchronous)`, `send()` : POST일 경우 데이터 같이 전송

2. 서버 응답에 대한 처리
	- 요구의 상태값 조사
	- HTTP 서버 응답의 상태 코드
	- 서버에서 받은 데이터 접근하기(`.responseText`, `.responseXML`)
