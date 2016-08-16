# Location 객체

Location 객체는 문서의 주소와 관련된 객체로 Window 객체의 프로퍼티다.

- 이 객체를 이용해서 윈도우 문서 URL 변경 가능.
- 문서의 위치와 관련된 다양한 정보 얻을 수 있음


### 현재 윈도우의 URL 알아내기

> console.log (location.toString(), location.href);

### URL Parsing
location 객체는 URL을 의미에 따라서 별도의 프로퍼티로 제공

>console.log(location.protocol, location.host, location.port, )


### URL 변경하기

현재 문서를 http://egoing.net 으로 이동

> location.href = "http://egoing.net"

같은 효과를 낸다

> location = "http://egoing.net";

현재 문서를 리로드하는 간편한 방법

> location.reload();
