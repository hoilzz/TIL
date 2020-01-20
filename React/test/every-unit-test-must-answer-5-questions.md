# 5 Questions Every Unit Test Must Answer

[5 questions every unit test must answer](https://medium.com/javascript-scene/what-every-unit-test-needs-f6cd34d9836d)

대부분의 개발자는 **every unit test** 의 필수 요소에 대해 알지 못한다.
단위 테스트가 실패한 횟수를 세지 못하고, 개발자가 테스트 해야하는 기능에 대해 모른다.

최근, 단위 테스트가 테스트 목적에 대한 설명도 없이 단위 테스트를 하려고 했고, 작성자만 이해할 수 있는 수많은 단위 테스트를 가지게 되었다.

이러한 일이 일어나지 않게 해야한다.

## Why Bother with Test Discipline?

테스트는 SW 결점에 대한 최고의 방어다. 테스트는 linting & static 분석(실제 프로그램 로직의 문제가 아닌, 서브 클래스의 에러만 찾을 수 있는..) 보다 훨씬 중요하다. 테스트는 구현체만큼 중요하다.(중요한 것은 코드가 요구사항을 충족한다는 뜻이다. 만약 구현이 덜 되었다면 구현 방법은 중요하지 않다)

유닛 테스트는 어플리케이션의 성공에 비밀 무기가 되는 많은 기능을 결합한다.

...

## What's in good test failure bug report?

좋은 테스트 실패 버그 리포트 무엇은가?

**1. 무엇을 테스트하는가?**
**2. 그것은 무엇을 해야 하는가?**
**3. output은 무엇인가(실제 동작)**
**4. 예상된 output은?(예상된 동작)**

## 무엇을 테스트하는가에 대한 대답하기

- 컴포넌트의 어떤 측면을 테스트하는가?
