# 304 Not Modified
ㅁ만약 클라이언트가 conditional GET request를 수행하고 접근이 허용된다면, but 문서가 수정되지 않았다면 서버는 304로 응답해야한다.

## 304는
- message-body를 포함하지 않아야한다
  - 따라서 header filed 다음 first empty line에서 종료된다
- response는 다음 헤더 필드를 포함해야한다
  - `Date`, Clockless Origin Server operation
  - 몇몇 origin server implementations은 clock이 이용 불가능할 수 있다
  - 만약 만약 이러한 값이 system or reliable clock을 가진 유저의 자원과 연관되어 있지 않다면
  - clock 없는 origin server는 Expires or Last-Modified를 응답값에 포함하지 않아야 한다
  - 그것은 알려진 Expires value를 할당한다.

  - Etag 및 COntent-Location
  - Expires, Cache-Control,

- 조건적 GET이 강한 캐시 검증자를 사용했다면 응답은 다른 Entity-Header를 포함해서는 안된다. 그렇지 않으면 (조건적 GET이 약한 캐시 검증자를 사용할 때)응답은 Entity-Header를 포함해서는 안된다. 이렇게 하여 캐시 된 Entity-Body와 갱싱된 헤더 사이의 불일치를 방지할 수 있다.




## 6 Response

요청 메시지를 받고 해석한 후에, 서버는 HTTP response msg로 응답한다.

Response = Status-Line
          *((general-header
            | response-header
            | entity-header) CRLF)
            CRLF
            [ message-body ] (7.2)

## 7.2 Entity Body
entity-body는 entity-header filed에 정의된 인코딩으로
entity-body는 `message-body`가 존재할 때 오직 보여진다. entity-body는 `Transfer-Encoding`을 디코딩하여 메시지 바디에서 얻어진다.

## 14.3 Accept-Encoding
Accept-Encoding request-header filed는 Accept와 비슷하다. 하지만 응답에서 수용가능한 content-coding을 제한한다.

서버는 Accept-Encoding field에 따라 content-coding이 허용가능인지를 테스트한다.
1. 1
2. 2
3. 3
4. 4

만약 Accept-Encoding field가 요청에서 존재한다면, 만약 서버가 Accept-Encoding header에 따라 허용가능한 응답을 보내지 못한다면, 서버는 err 응답을 보내야한다 (406에러오 ㅏ같이)
만약 Accept-Encoding field가 요청에서 제시되지 않는다면, 서버는 클라가 어떠한 컨텐츠 코딩도 허용된다는 걸로 가정한다. 이 경우에 identity가 이용 가능한 컨텐츠-코딩중의 하나면 서버는 아이덴티티를 컨텐츠 코딩으로 사용한다.
