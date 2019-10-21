# 순수 함수

순수 함수가 뭔지 알아보기 전에, 함수에 대해 자세히 알아보자. FP를 이해하기 쉽게 만들어주는 다른 방법이 있을 수 있다.

## 함수는 뭘까

함수는 **arguments** 라 불리는 input을 받고 **return value** 라 불리는 ouput을 만든다.
함수는 다음 목적을 제공한다.

- **Mapping** : 주어진 input으로 output 만들기. 함수는 input과 ouput을 **매핑** 한다.
- **Procedures** : 함수는 일련의 스텝을 수행하기 위해 호출된다. 시퀀스는 절차고 이 스타일의 프밍은 **절차형 프밍** 이라 알려져 있다.
- **I/O** : 몇몇 함수는 시스템의 다른 부분(screen, storage, system logs, network)과 통신 하기 위해 존재한다.

## Mapping

pure 함수는 매핑에 대한 모든 것이다.
...

## Pure Fn

순수함수는

- 동일 input이 주어진다면, 항상 동일 output을 리턴한다.
- side effect가 없다.

> 함수가 불완전(impure)하다는 공짜는 리턴값을 이용하지 않고 호출하는 것이 합리적이다.
> 순수 함수를 원한다면, 이건 멍청한 짓이다.

순수 함수를 선호하는 것이 좋다. 순수함수는 가장 간단한 재사용 가능한 코드다. 가장 중요한 원칙 중 하나인 KISS(Keep It Simple, Stupid)다. 순수 함수는 가장 간단하다.

순수함수는 함수형 프로그래밍의 기초다.

- 순수 함수는 완전히 상태 독립적이다.
  - 변경가능한 공유 상태를 처리해야하는 클래스의 버그에 영향을 받지 않는다.
- 독립적인 환경은 여러 CPU에서 병렬 처리를 가능하게 한다.

순수함수는 극도로 독립적이다.
코드 이동, 리팩토링 및 재구성하기 쉬워서 변경에 유연하게 대응할 수 있다.

## 공유되는 상태의 문제

웹 플레이어에서 뮤직 플레이리스트와 아티스트를 db에서 검색하는 app을 만들었다. 타이핑 할 때마다 순간적으로 검색 결과를 보여준다. ajax 기반 자동완성은 화를 불러일으켰다.

API 자동완성시 응답값이 리턴되는 것보다 타이핑이 빠를 때 문제가 발생한다. 이것은 이상한 버그를 유발한다. 오래된 응답값이 새로운 응답값으로 교체되는 race condition이다.

왜 일어날까? AJAX 성공 핸들러는 use에게 보여주는 suggestion UI를 직접 업데이트하기 떄문이다. 가장 느린 AJAX 요청이 대체된 결과값이 새로운 결과일지라도 결과값을 무조건적으로 대체한다.

이 문제를 해결하기 위해 suggestion manager를 만들었다. 쿼리 suggestion의 상태를 관리하는 단일 상태관리다.

...

## 동일 input! 항상 동일 output!