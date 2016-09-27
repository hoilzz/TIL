# packeet

# wireshark
- PC로 들어오고 나가는 메시지들을 캡처
- 캡처된 메시지의 protocol 분석 가능

# packet sniffer structure
-

# packet analyzer
- protocol msg 내의 모든 필드 dp
- 위와 같이 하기 위해, packet analyzer는 protocol에 의해 교환된 메시지의 구조를 이해해야 한다.

## Example; HTTP Msg
- HTTP 최상위 레이어


# Wireshark

## assignment
1 7가지 단계에서 필터되지 않은 패킷 리스트 내에서 protocol column에서 나타나는 다양한 프로토콜 리스트
  - pdf의 가장 뒤에 나와있는 문제
   - 10개의 스텝들을 간략하게 보여준거.. 어떤 주소의 웹 페이지를 띄우고 그거 10갸의 스텝 나와있음 그 과정에서 패킷을 캐버를 시작하고 종료까지 과정에서
   패킷 캡처 언필터됐을 때 프로토콜 되게 많이 나와있다 DNS TCP 등등 저거 다섯 개 프로토콜 이름만 적어도 됨..

2 http get 메시지를 보낸 다음부터 ok msg 받을 때까지 얼마나 소요됨?
  - 요청과 응답 사이의 텀 시간값(요청 시간 - 응답 시간)

3 ip protocol 안에 포함된 ip address 즉 서버의 IP address, 응답 메시지를 받을 내 PC IP address
