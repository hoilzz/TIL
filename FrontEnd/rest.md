# REST API

REST는 Representational state transfer라는 용어의 약자다.

## 구성

REST는 다음 3가지로 구성되어있다.

	- 자원(RESOURCE) - URI
	- 행동(Verb) - HTTP METHOD
	- 표현(Representations)

## REST의 특징

1. Uniform

Uniform Interface는 URI로 지정한 리소스에 대한 조작을 통일되고 한정적인 인터페이스로 수행하는 아키텍처 스타일이다.

2. Stateless

작업을 위한 상태정보를 따로 저장하고 관리하지 않습니다.

세션 정보나 쿠키 정보를 별도로 저장하고 관리하지 않기 때문에 API 서버는 들어오는 요청만을 단순히 처리한다.

결과적으로, 서비스 자유도가 높아지고 서버에서 불필요한 정보를 관리하지 않음으로써 구현이 단순해진다.

3. Cacheable

HTTP라는 기존 웹표준을 사용한다. 그러므로 웹에서 사용하는 기존 인프라의 활용이 가능하다.

따라서 HTTP가 가진 캐싱 기능이 적용 가능하다.

HTTP 프로토콜 표준에서 사용하는 Last-Modified태그나 E-Tag를 이용하면 캐싱구현이 가능하다.
