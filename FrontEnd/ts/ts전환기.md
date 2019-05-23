# Typescript 전환기

[react-redux-ts-guide](https://github.com/piotrwitek/react-redux-typescript-guide) 번역 및 전환 일지.

> 이 가이드는 가장 중요한 패턴과 TS를 이용한 함수형 스타일에서 React를 사용하는법방법 레시피를 문서화 했다. 완전히 구현체로부터 타입 추론하는데 집중하며 type-safe하게 만든다. 그래서 과도한 타입 annotations에서 나오는 noise를 줄이고 쉽게 작성하고 올바른 types을 유지할 수 있다.

_TypeScript v3.1.6과 호환되는 문서다_

## Goals

- 타입 정보를 잃지 않으면서 완벽하고 안전하게 any타입에서 벗어나기.
- __타입추론__ 과 __Control flow analysis__ 와 같은 고급 TS 기능을 이용하여 타입 낭비를 제거하여 type annotation을 간결하게 만들기
- Type Inference을 이용해서 수동으로 입력하는 주석의 양 최소화
- Generics 및 Advanced Types 기능을 사용하여 심플한 유틸리티 기능으로 boilerplate를 제작.


## Interface VS Type

TS의 핵심 원리 중 하나는 __형태__ 에 초점을 맞추는 __타입 체킹__ 을 하는 것
(duck typing, structural subtyping)

- 인터페이스 구현하기
  - 클래스가 특정 계약을 충족하도록 명시적인 강제 역할

```ts
interface ClockInterface {
	currentTime: Date;
	setTime(d: Date);
}

class Clock implements ClockInterface {
	currentTime: Date;
	setTime(d: Date) {
		this.currentTime = d;
	}
	constructor(h: number, m: number) {}
}
```

- 인터페이스 확장하기
  - 인터페이스 멤버를 다른 인터페이스로 확장 가능
  - 인터페이스를 재사용 가능한 컴포넌트로 분리하는 방법