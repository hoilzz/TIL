## tcp 4-way 에서 time_wait 가 길어야 하는이유

길지 않으면 2 가지 문제 발생

1. 지연 패킷 발생

![img](http://docs.likejazz.com/images/2018/time-wait/duplicate-segment.png)

- 이미 다른 연결로 진행되었다면 지연 패킷이 뒤늦게 도달해 문제가 발생
- 매우 드문 경우이긴 하나 때마침 SEQ 까지 동일하다면 잘못된 데이타를 처리하게 되고 데이타 무결성 문제가 발생한다.

2. 원격 종단

- 원격 종단의 연결이 닫혔는지 확인해야할 경우
- 마지막 ACK 유실시 상대방은 LAST_ACK 상태에 빠지게 되고 새로운 SYN 패킷 전달시 RST 를 리턴
  - 새로운 연결은 오류를 내며 실패
  - 이미 연결을 시도한 상태이기 때문에 상대방에게 접속 오류 메시지가 출력될 것이다.

![img](http://docs.likejazz.com/images/2018/time-wait/last-ack.png)

**따라서 TIME_WAIT 이 일정 시간 남아 있어서 패킷의 오동작을 막아야 함**


---

## sliding window

실리 윈도우 문제

nagle(송신측)
기다렸다가 받기
- ack 올 때까지 기다려서 전송속도 느림

클라크 (수)
- 윈도우크기가 일정 될 때까지 기다림
- 