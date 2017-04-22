## 3.5 데이터를 로딩할 때 일어날 수 있는 일

웹 어플리케이션이 브라우저의 기능과 데이터만 이용하는 상황이 아니라면 결국 서버에서 원격으로 데이터를 로드해야 한다.

일반적으로, 애플리케이션은 실행 시점에 일부 데이터를 로드하고 사용자와 상호작용 하면서 추가로 데이터를 로드한다.

애플리케이션 타입이나 로드하는 데이터 양에 따라 다르겠지만 때에 따라서는 **초기 페이지 로드 시점에 모든 데이터를 가져올 수 있다.**

그런 경우, 사용자가 데이터 로드 시간을 기다리지 않아도 된다.

그러나 브라우저의 메모리는 한정적이므로 모든 데이터를 처음에 가져올 수 없는 경우가 많다.

따라서, 웬만한 웹 어플리케이션은 초기 페이지 로드 시점에 전체 데이터를 로드하지 못한다.



그럼에도 사용자 대기시간을 줄여 매끄럽고 빠른 애플리케이션 동작을 보여주려면 미리 데이터를 로드해야 한다.

그런데 실제 사용하는 데이터가 있고 아예 사용하지 않을 데이터가 있기 때문에 미리 데이터를 로드하는 방법에도 한계가 있다.

따라서 사용자가 어떤 종류의 데이터를 사용할 것인지 예측해서 데이터를 로드해야 한다.


`여러 페이지로 구성된 리스트`를 표시하는 상황이라면

미리 다음 페이지를 로드해서 다음 페이지로 바로 넘어갈 수 있도록 처리하며 어떨까?

또는 더욱 세련된 방법으로, 긴 리스트를 일단 모두 표시하고 리스트를 스크롤할 때마다 자동으로 데이터를 로드해서 추가하는 방법은 어떨까?

`사용자를 덜 기다리게 할수록 좋다`는 격언은 변치 않는 원칙이다.

데이터 가져올 때, UI가 블록되지 않도록 주의해야 한다.

예를 들어 데이터 가져올 때에는 로딩 중임을 표시하는 `인디케이터` 등을 이용해

인터페이스가 블록되지 않고 사용할 수 있는 상태임을 보여줘야 한다.

어떻게든 UI를 블록하는 상황을 최소한으로 줄여야 한다.


초기 페이지는

	1. 데이터를 인라인으로 보여주거나
	2. Ajax나 JSONP 기법으로 별도의 HTTP로 데이터 로드하기

많은 데이터를 인라인으로 추가시 페이지 크기가 너무 커진다.

개인적으로는 병렬 요청으로 빠르게 데이터를 로드할 수 있는 Ajax나 JSONP기법을 추천.

이외에 HTML페이지 캐시 기능도 제공한다.


## 3.5.1 데이터 인라인 포함하기

데이터 인라인 기법은 별로 추천 ㄴㄴ한다.

그러나 상황에 따라서 작은 데이터 로딩시 인라인 기법 유요하다.



## 3.5.2 Ajax로 데이터 로딩하기

원격 데이터를 로딩하는 백그라운드 요청이라는 말은, Ajax를 떠올릴 수 밖에 없다.

어쩄든 Ajax API를 추상화하는 jQuery 같은 라이브러리를 이용해 브라우저 간 불일치 문제를 해결할 가능성이 크다.

jQuery의 Ajax API는 한개의 저수준 함수 `jQuery.ajax()`와 이를 추상화하는 여러 고수준 추상화 함수로 이루어져 있다.

여러 고수준 추상화 함수 이용시 코딩 양을 줄일 수 있다.

jQuery.ajax() 는 여러 요청 파라미터 설정, 컨텐츠 타입, 콜백 등을 인자로 받는다.

jQuery.ajax() 함수를 호출하면 백그라운드에서 비동기 방식으로 요청을 보낸다.

---

url
:요청 url. 현재 페이지가 기본 값.

...

Ajax는 요청이 발생한 **`도메인`, `서브도메인`, `페이지의 포트가 같아야 한다`는 원칙에 제한을 받는다**. (동일한 Origin 정책)

이런 제한이 생긴 이유는

Ajax 요청을 보낼 때마다 도메인의 모든 쿠키 정보를 요청과 함께 전달한다.

요청을 받는 원격 서버는 요청을 로그인한 사용자가 보내는 것이라고 착각할 수 있다.

따라서 같은 오리진 정책이 없다면 해커는 맘대로 다른 사람의 지메일에 저장된 메일을 가져올 수 있고 페북 상태 갱신도 가능하다.

같은 오리진 정책은 웹 보안의 필수요소지만 정당하게 원격 자원을 접속하려는 개발자에게 큰 타격을 준다.

현재 Ajax도 다른 도메인 간의 자원 공유 문제를 해결할 수 있는 `CORS`라는 크로스 오리진 자원 공유 기법을 제공한다.

CORS의 사용 방법은 간닿나다.

반환된 응답의 헤더에 몇 줄 추가하면 서브 접근 권한을 승인한다.

```
Access-Control-Allow-Origin: example.com
Acccess-Control-Request-Method: GET, POST
```

클라는 커스텀 헤더 Ajax 요청에 추가 가능

```javascript
var req = new XMLHttpRequest();
req.open("POST", "/endpoint", true);
req.setRequestHeader("Authorization", oauth_signature);
```

IE 8과 상위 버전은 CORS 지원.

## 3.5.3 JSONP

JSON with padding을 의미하는 JSONP는 원격 서버 데이터를 가져오는 다른 방법 중 하나로

CORS가 표준화되기 전에 탄생한 기법이다.

JSONP의 핵심은