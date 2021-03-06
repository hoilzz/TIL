### 4장 커넥션 관리

#### 4.1 TCP 커넥션
* 일단 커넥션이 맺어지면 클라이언트와 서버 컴퓨터 간에 주고받는 메시지들은 손실 혹은 손상되거나 순서가 바뀌지 않고 안전하게 전달

##### 4.1.1 신뢰할 수 있는 데이터 전송 통로인 TCP
* HTTP 커넥션은 몇몇 사용 규칙을 제외하고는 TCP 커넥션에 불과
* TCP 커넥션은 인터넷을 안정적으로 연결
* TCP 커넥션의 한쪽에 있는 바이트들은 반대쪽으로 순서 에 맞게 정확히 전달

![TCP는 충돌 없이 순서에 맞게 HTTP 데이터를 전달한다.](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-2.png)

##### 4.1.2 TCP 스트팀은 세그먼트로 나뉘어 IP 패킷을 통해 전송된다
* TCP는 IP 패킷(혹은 IP 데이터그램)이라고 불리는 작은 조각을 통해 데이터를 전송
* HTTP가 메시지를 전송하고자 할 경우, 현재 연결되어 있는 TCP 커넥션을 통해서 메시지 데이터의 내용을 순서대로 보냄
* TCP는 세그먼트라는 단위로 데이터 스트림을 잘게 나누고, 세그먼트를 IP 패킷라고 불리는 봉투에 담아서 인터넷을 통해 데이터를 전달
* 각 TCP 세그먼트는 하나의 IP 주소에서 다른 IP 주소로 IP 패킷에 담겨 전달

##### 4.1.3 TCP 커넥션 유지하기
* 컴퓨터는 항상 TCP 커넥션을 여러 개 가지고 있음
* TCP는 포트 번호를 통해서 이런 여러 개의 커넥션을 유지
* TCP 커넥션은 네 가지 값으로 식별
* 네 가지 값으로 유일한 커넥션을 생성

```
<발신지 IP 주소, 발신지 포트, 수신지 IP 주소, 수신지 포트>
```

##### 4.1.4 TCP 소켓 프로그래밍
* 운영체제는 TCP 커넥션의 생성과 관련된 여러 기능을 제공
* 소켓 API를 사용하면, TCP 종단(endpoint) 데이터 구조를 생성하고, 원격 서버의 TCP 종단에 그 종단 데이터 구조를 연결하여 데이터 스트림을 읽고 쓸 수 있음
* TCP API는, 기본적인 네트워크 프로토콜의 핸드셰이킹, 그리고 TCP 데이터 스트림과 IP 패킷 간의 분할 및 재조립에 대한 모든 세부사항을 외부로부터 숨김

#### 4.2 TCP의 성능에 대한 고려

##### 4.2.1 HTTP 트랜잭션 지연
* 클라이언트나 서버가 너무 많은 데이터를 내려받거나 복잡하고 동적인 자원들을 실행하지 않는 한, 대부분의 HTTP 지연은 TCP 네트워크 지연 때문에 발생

![HTTP 트랜잭선이 처리되는 과정](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-7.png)

##### 4.2.2 성능 관련 중요 요소
* **TCP 커넥션의 핸드셰이크 설정**
* **인터넷의 흔잡을 제어하기 위한 TCP의 느린 시작(slow-start)**
* **데이터를 한데 모아 한 번에 전송하기 위한 네이글(nagle) 알고리즘**
* **TCP의 편승(piggyback) 확인응답(acknowledgment)을 위한 확인응답 지연 알고리즘**
* **TIME WAIT 지연과 포트 고갈**

##### 4.2.3 TCP 커넥션 핸드셰이크 지연
* TCP커넥션이핸드셰이크를하는순서
  * 클라이언트는 새로운 TCP 커넥 션을 생성하기 위해 작은 TCP 패킷(보통 40~60바이트)을 서버에게 보낸
  * 서버가 그 커넥션을 받으면 몇 가지 커넥션 매개변수를 산출하고, 커넥션 요청이 받아들여졌음을 의미하는 'SYN'과 'ACK' 플래그를 포함한 TCP 패킷을 클라이언트에게 보냄
  * 마지막으로 클라이언트는 커넥션이 잘 맺어졌음을 알리기 위해서 서버에게 다시 확인응답 신호를 보냄

![TCP는 데이터를 전송하기 전에, 커넥션 설정을 위해 두 개의 패킷 전송을 해야 한다.](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-8.png)

##### 4.2.4 확인응답 지연
* TCP는 성공적인 데이터 전송을 보장하기 위해서 자체적인 확인 체계를 가짐 (?)
* 각 TCP 세그먼트는 순번과 데이터 무결성 체크섬을 가짐
* 세그먼트의 수신자는 세그먼트를 온전히 받으면 작은 확인응답 패킷을 송신자에게 반환
* 송신자가 특정 시간 안에 확인응답 메시지를 받지 못하면 패킷이 파기되었거나 오류가 있는 것으로 판단하고 데이터를 다시 전송
* 확인응답은 그 크기가 작기 때문에, TCP는 같은 방향으로 송출되는 데이터 패킷에 확인응답을 '편승(piggyback)' 시킴
* 요청과 응답 두 가지 형식으로만 이루어지는 HTTP 동작 방식은, 확인 응답이 송출 데이터 패킷에 편승할 기회를 감소 시킴
* TCP 스택에 있는 매개변수를 수정할 때는, 지금 무엇을 하고 있는지 항상 잘고 수정 (수정 할 일이 있을까?)

##### 4.2.5 TCP 느린 시작(slow start)
* TCP 커넥션은 시간이 지나면서 자체적으로 '튜닝'되어서, 처음에는 커넥션의 최대 속도를 제한하고 데이터가 성공적으로 전송됨에 따라서 속도 제한 을 높여나감

##### 4.2.6 네이글(Nagle) 알고리즘과 TCP_NODELAY
* 애플리케이션이 어떤 크기의 데이터든지(심지어 1바이트라도) TCP 스택으로 전송 할 수 있도록, TCP는 데이터 스트림 인터페이스를 제공
* 네트워크 효율을 위해서, 패킷을 전송하기 전에 많은 양의 TCP 데이터를 한개 의 덩어리로 합침
* 문제점
 * 크기가 작은 HTTP 메시지는 패킷을 채우지 못하기 때문에, 앞으로 생길지 생기지 않을지 모르는 추가적인 데이터를 기다리며 지연될 것
 * 네이글 알고리즘은 확인응답 지연과 함께 쓰일 경우 형편없이 동작
* HTTP 애플리케이션은 성능 향상을 위해서 HTTP 스택에 TCP NODELAY 파라미터 값을 설정하여 네이글 알고리즘을 비활성화하기도 함

##### 4.2.7 TIMEWAIT의 누적과 포트 고갈 (?)
* TCP 커넥션의 종단에서 TCP 커넥션을 끊으면, 종단에서는 커넥션의 IP 주소와 포트 번호를 메모리의 작은 제어영역(control block)에 기록
  * 주소와 포트 번호를 사용하는 새로운 TCP 커넥션이 일정 시간 동안에는 생성되지 않게 하기 위한 것

#### 4.3 HTTP 커넥션 관리

##### 4.3.1 흔히 잘못 이해하는 Connection 헤더 (?)
* HTTP C○nncction 헤더 필드는 커넥션 토큰을 쉼표로 구분하여 가지고 있으며, 그 값들은 다른 커넥션에 전달되지 않음

##### 4.32 순차적인 트랜잭션 처리에 의한 지연
* 각 트랜책션이 새로운 커넥션을 필요로 한다면, 커넥션을 맺는데 발생하는 지연과 함께 느린 시작 지연이 발생할 것

![네 개의 트랜잭션(순차)](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-10.png)

* HTTP 커넥션의 성능을 향상시킬 수 있는 여러 최신 기술
  * 병렬(parallel) 커넥션 : 여러 개의 TCP 커넥션을 통한 동시 HTTP 요청
  * 지속(persistent) 커넥션 : 커넥션을 맺고 끊는 데서 발생하는 지연을 제거하기 위한 TCP 커넥션의 재활용
  * 파이프라인(pipelined) 커넥션 : 공유 TCP 커넥션을 통한 병렬 HTTP 요청
  * 다중(multiplexed) 커넥션 : 요청과 응답들에 대한 중재(실험적인 기술이다)

#### 4.4 병렬 커넥션

##### 4.4.1 병렬 커넥션은 페이지를 더 빠르게 내려받는다
* 단일 커넥션의 대역폭 제한과 커넥션이 동작하지 않고 있는 시간을 활용하면, 객체가 여러 개 있는 웹페이지를 더 빠르게 내려받을 수 있을 것
* 각 커넥션의 지연 시간을 겹치게 하면 총 지연 시간을 줄일 수 있고, 클라이언트의 인터넷 대역폭을 한 개의 커넥션이 다 써버리는 것이 아니라면 나머지 객체를 내려받는 데에 남은 대 역폭을 사용할 수 있음

##### 4.4.2 병혈 커넥션이 항상 더 빠르지는 않다
* 여러 개의 객체를 병렬로 내려받는 경우, 이 제한된 대역폭 내에서 각 객체를 전송받는 것은 느리기 때문에 성능상의 장점은 거의 없어짐
* 서버는 특정 클라이언트로부터 과도한 수의 커넥션이 어졌을 경우, 그것을 임의로 끊어버릴 수 있음

##### 4.4.3 병렬 커넥션은 더 빠르게 '느껴질 수' 있다
* 병렬 커넥션이 실제로 페이지를 더 빠르게 내려받는 것은 아니지만, 화면에 여러 개의 객체가 동시에 보이면서 내려받고 있는 상황을 볼 수 있기 때문에 사용자는 더 빠르게 내려받고는 것처럼 느낄 수 있음

#### 4.5 지속 커넥션
* 사이트 지역성 (site locality) : 서버에 HTTP 요청을 하기 시작한 애플리케이션은 웹페이지 내의 이미지 등을 가져오기 위해서 그 서버에 또 요청하게 될 것
* HTTP/1.1(HTTP/1.0의 개선 버전)을 지원하는 기기는 처리가 완료된에도 TCP 커 넥션을 유지하여 앞으로 있을 HTTP 요청 에 재사용할 수 있음
* 처리가 완료된 후에도 계속 연결된 상태로 있는 TCP 커넥션을 지속 커넥션이라고 부름
* 지속 커넥션은 클라이언트나 서버가 커넥션을 끊기 전까지는 트랜잭션 간에도 커넥션을 유지

##### 4.5.1 지속 커넥션 vs 병렬 커넥션
* 지속 커넥션 장점
  * 커넥션을 맺기 위한 사전 작업과 지연을 줄여주고, 튜닝된 커넥션을 유지하며, 커넥션의 수를 줄여줌
* 지속 커넥션은 병렬 커넥션과 함께 사용될 때에 가장 효과적
* HTTP/1.0+에는 'keep-alive' 커넥션이 있고 HTIP/1.1에는 '지속' 커넥션 (?)

##### 4.5.2 HTTP/1.0+의 Keep-Alive 커넥션
* 많은 HTTP/1.0 브라우저와 서 버들은 일찍부터 다소 실험 적 이 었던 keep-alive 커션이라는 지속 커넥션을 지원하기 위해 확장

![네 개의 트랜책션(연속 vs 지속)](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-13.png)

##### 4.5.3 Keep-Alive 동작
* keep-alive는 사용하지 않기로 결정되어 HTTP/1.1 명세에서 빠짐
* HTTP/1.0 keep-alive 커넥션을 구현한 클라이언트는 커넥션을 유지하기 위해서 요청에 Connection:Keep-Alive 헤더를 포함
* 이 요청을 받은 서버는 그다음 요청도 이 커넥션을 통해 받고자 한다면, 응답 메시지에 같은 헤더를 포함

##### 4.5.4 Keep-AIive 옵션
* Keep-AIive 헤더는 커넥션을 유지하기를 바라는 요청일 뿐
* 클라이언트나 서버가 keep-alive 요청을 받았다고 해서 무조건 그것을 따를 필요는 없음

```
Connection: Keep-AIive
Keep-Alive: max=5, timeout=12O
```

##### 4.5.5 Keep-Alive 커넥션 제한과 규칙
* keep-alive는 HTTP/1.0에서 기본으로 사용되지는 않음
* 클라이언트는 keep-alive 커넥션을 사용하기 위해 Connection: Keep-AIive 요청 헤더를 보내야 함
* 커넥션을 계속 유지하려면 모든 메시지에 Connection: Keep-Alive 헤더를 포함해 보내야 함 (클라이 언트가 Connection: Keep-Alive 헤더를 보내지 않으면 서버는 요청을 처 리한 후 커넥션을 끊을 것)
* 클라이언트는 Connection: Keep-Alive 응답 헤더가 없는 것을 보고 서버가 응답후에 커넥션을 끊을 것임을 알 수 있음

##### 4.5.6 Keep-Alive와 멍청한(dumb) 프락시

###### Connection 헤더의 무조건 전달
* 특히 문제는 프락시에서 시작되는데, 프락시는 Connection 헤더를 이해하지 못해서 해당 헤더들을 삭제하지 않고 요청 그대로를 다음 프락시에 전달

![keep-alive는 Connection 헤더를 지원하지 않은 프락시와는 상호작용하지 않는다](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-15.png)

###### 프락시와 흡별 헤더
* 프락시는 Connection 헤더와 Connection 헤더에 명시된 헤더들은 절대 전달하면 안 됨

##### 4.5.7 Proxy-Connection 살펴보기

![ProxyConnection 헤더는 단일 무조건 전달 문제를 해결해준다.](/assets/images/books/네트워크_해킹_보안/네트워크일반/HTTP완벽가이드/figure_4-16.png)

##### 4.5.8 HTTTP/1.1 의 지속 커넥션
* HTTP/1.1에서는 keep-live 커넥션을 지원하지 않는 대신, 설계가 더 개선된 지속 커넥션을 지원
* 지속 커넥션의 목적은 keep-alive 커넥션과 같지만 그에 비해 더잘 동작
* HTTP/1.0의 keep-alive 커넥션과는 달리 HTTP/1.1의 지속 커넥션은 기본으로 활성화
* HTTP/1.1에서는 별도 설정을 하지 않는 한, 모든 커넥션을 지속 커넥션으로 취급
* HTTP/1.1 애플리케이션은 트랜잭션이 끝난 다음 커넥션을 끊으려면 Connection: close 헤더를 명시
* HTTP/1.1 클라이언트는 응답에 Connection: close 헤더가 없으면 응답 후에도 HTTP/1.1 커넥션을 계속 유지하지는 것으로 추정
* 클라이언트와 서버는 언제든지 커넥션을 끊을 수 있음
* Connection: close를 보내지 않는 것이 서버가 커넥션을 영원히 유지하겠다는 것을 뜻하지는 않음

###### 4.5.9 지속 커넥션의 제한과 규칙
* 클라이언트가 요청에 Connection: close 헤더를 포함해 보냈으면, 클라이언트는 그 커넥션으로 추가적 인 요청 을 보낼 수 없음
* 클라이언트가 해당 커넥션으로 추가적인 요청을 보내지 않을 것이라면, 마지막 요청에 Connection: close 헤더를 보내야 함

#### 4.6 파이프라인 커넥션
* HTTP/1.1은 지속 커넥션을 통해서 요청을 파이프라이닝할 수 있음
* HTTP 응답은 요청 순서와 같게 와야 한다. HTTP 메시지는 순번이 매겨져 있지 않아서 응답이 순서 없이 오면 순서에 맞게 정렬시킬 방법이 없음
* 멱등(idempotent) : 연산의 한 성질을 나타내는 것으로, 연산을 여러 번 적용하더라도 결과가 달라지지 않는 성질
* 비멱등(nonidempotent) : 연산이 한 번 일어날 때 마다 결과가 변할 수 있음을 뜻

#### 4.7 커넥션 끊기에 대한 미스터리

##### 4.7.1 '마음대로', 커넥션 끊기
* HTTP 클라이언트, 서버, 혹은 프락시든 언제든지 TCP 전송 커넥션을 끊을수 있음
* 보통 커넥션은 메시지를 다 보낸 다음 끊지만, 에러가 있는 상황에서는 헤더의 중간이나 다른 엉뚱한 곳에서 끊길 수 있음

##### 4.7.2 Content-Length와 Truncation
* 각 HTTP 응답은 본문의 정확한 크기 값을 가지는 Content-Length 헤더를 가지고 있어야 함
* 클라이언트나 프락시가 커넥션이 끊어졌다는 HTTP 응답을 받은 후, 실제 전달 된 엔터티의 길이와 Content-Length의 값이 일치하지 않거나 Content-Length 자체가 존재하지 않으면 수신지는 데이터의 정확한 길이를 서버에게 물어봐야 함

##### 4.7.3 커넥션 끊기의 허용, 재시도, 멱등성
* 한 번 혹은 여러 번 실행됐는지에 상관없이 같은 결과를 반환한다면 그 트랜책션은 멱등(idempotent)
* GET, HEAD, PUT, DELETE, TRACE 그리고 OPTIONS 메서드들은 멱등
* 비멱등인 요청을 다시 보내야 한다면, 이 전 요청 에 대한 응답을 받을 때까지 기다려야 함
* GET 기반의 동적인 폼을 사용할 경우에는 GET이 멱등하게 동작하는 것이 맞는지 확인이 필요

##### 4.7.4 우아한 커넥션 끊기

###### 전체 끊기와 절반 끊기
* 애플리케이션은 TCP 입력 채널과 출력 채널 중 한 개만 끊거나 둘 다 끊을 수 있음
* '전체 끊기' close()를 호출하면 TCP 커넥션의 입력 채널과 출력 채널의 커넥션을 모두 끊음
* '절반 끊기' 입력 채널이나 출력 채널 중에 하나를 개별적으로 끊으려면 shutdown()을 호출

###### TCP 끊기와 리셋 에러
* 보통은 커넥션의 출력 채널을 끊는 것이 안전
* 커넥션의 반대편에 있는 기기는 모든 데이터를 버퍼로부터 읽고 나서 데이터 전송이 끝남과 동시에 당신이 커넥션을 끊었다는 것을 알게 됨
* 클라이언트에서 더는 데이터를 보내지 않을 것임을 확신할 수 없는 이상, 커넥션의 입력 채널을 끊는 것은 위험
* 클라이언트에서 이미 끊긴 입력 채널에 데이터를 전송하면, 서버의 운영체제는 TCP 'connection reset by peer' 메시지를 클라이언트에 보냄

###### 우아하게 커넥션 끊기
* 일반적으로 애플리케이션이 우아한 커넥션 끊기를 구현하는 것은 애플리케이션 자신의 출력 채널을 먼저 끊고 다른 쪽에 있는 기기의 출력 채널이 끊기는 것을 기다리는 것
* 커넥션을 우아하게 끊고자 하는 애플리케이션은 출력 채널에 절반 끊기를 하고 난 후에도 데이터나 스트림의 끝을 식별하기 위해 입력 채널에 대해 상태 검시률 주기적으로 해야 함
