# 4-2 Routing

## 라우팅

최종 목적지까지 찾아가는 과정

## 라우터

- 역할: 라우터는 네트워크 간 패킷 전달함

## 동적 라우팅

라우팅 프로토콜을 이용하여 자동으로 정보 수집하여 라우팅 테이블을 설정

### 라우팅 테이블에 목적지가 없을 경우

- 테이블이 모든 정보를 저장할 수 없는데, 목적지를 모를 경우
- 자기보다 더 많은 정보를 담고 있는 default router에게 물어봄

## NAT

private IP를 할당받은 호스트와 public IP를 할당받은 호스트는 서로 통신 못함. NAT를 이용하면 통신 가능

__호스트가 데이터 송신시 라우터의 NAT가 private addr를 router의 public IP로 변경__

### NAT의 제약 

1. 여러 호스트가 공교롭게 같은 port 번호 사용시 라우터는 응답을 어디로 보낼지 port만 보고 판단 불가
2. 또한, 외부에서 일방적으로 보낸 데이터는 NAT범위의 호스트에 전달 불가

#### 1번 문제의 해결책: NAPT

NAPT(network address __port translation__), 포트 번호 충돌을 막기 위해, 라우터에서 IP 어드레스 뿐만 아니라 포트 번호도 함께 변환.

- 

![img]('./img/snat-port-duplicate-problem.jpeg)

#### 2번 문제 해결책: 포트 포워딩

특정 포트 번호로 들어오면, 내부 특정 서버에 전달 될 수 있도록 설정

![img]('./img/sport-forwarding.jpeg)

