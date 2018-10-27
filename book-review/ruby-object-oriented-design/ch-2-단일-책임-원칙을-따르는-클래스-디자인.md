# 2. 단일 책임 원칙을 따르는 클래스 디자인하기

디자인의 핵심인 메시지, 하지만 가장 명시적으로 드러나는 것은 클래스.
이번에 집중할 것

- **무엇이 클래스에 속하는지**
- **어떻게 알 수 있는지**
  - 어떤 클래스를 만들어야 할까?
  - 몇 개나 만들까?
  - 어떤 행동을 구현해야 할까?
  - **하나의 클래스는 다른 클래스에 대해 얼마나 알고 있어야 할까?**
  - **다른 클래스에게는 어느 정도까지 열려있어야 할까?**

**클래스는 단순해야 한다** 에 집중. 클래스는

- 지금 당장 해야 할 일을 할 줄알고
- 나중에도 쉽게 수정할 수 있는

클래스를 모델링 하자

## 2.1 무엇을 클래스에 넣을지 결정하기

우리는 코드 짤 줄 아는데, 코드를 **어떻게 구성하고**, **어디에 배치할지** 모름

### 2.1.1 메서드들을 묶어 클래스로 만들기

클래스는 `우리가 애플리케이션에 대해 어떻게 생각하는지`에 대해 영원히 영향을 미침

- 다른 개발자가 이 애플리케이션이 무엇인지 상상할 수 있는 범위를 규정
- **변화를 잘 수용할 수 있어야함**
  - 스펙은 계속 바뀌니까

그래서 디자인이란, 완벽함을 추구하는 것보단 **코드의 수정가능성을 보정하는 기술**

### 2.1.2 수정하기 쉽도록 코드 구성하기

먼저 **수정하기 쉽다** 를 정의하기

- 수정이 예상치 못한 부작용을 낳지 않음
- 요구사항이 조금 변했을 때 연관 코드를 조금만 수정하면 됨
- 현재 코드 재사용하기 쉬움
- 코드 수정하기 가장 쉬운 방법은 이미 수정하기 쉬운 코드에 새로운 코드 추가

작성하는 코드는 다음 특징을 가짐

- 투명하다
  - 수정된 코드 속에서, 이 코드와 연관된 코드 속에서 **수정의 결과가 뚜렷하게 드러나야함**
- 적절하다
  - 모든 수정 비용은 수정 결과를 통해 얻은 이득에 비례
- 사용 가능하다
  - 예상치 못한 상황에서 현재 코드 사용 가능
- 모범이 된다
  - 나중에 수정하는 사람이 위 특징을 이어갈 수 있음

## 2.2 하나의 책임만을 지는 클래스 만들기

요번 챕터의 예시 주제로 자전거, 그리고 기어비를 계산 하는 애플리케이션 만드는거

일단 클래스가 될만한거는 `자전거`(근데 지금 필요한거 아님)
반면 기어는 앞 톱니바퀴, 뒷 톱니바퀴, 기어비를 가짐.

- 데이터(앞 톱니바퀴 외 2 개),
- 행동(기어비 구하기)

둘 다 가지기 때문에 클래스 만들 수 있음

```typescript
class Gear {
  constructor(readonly cog: number, readonly chainRing: number) {}
  ratio() {
    return this.chainRing / this.cog;
  }
}

let myGear = new Gear(52, 11).ratio();
let friendGear = new Gear(20, 5).ratio();
```

기어계산기 만듬.

요구사항이 늘어남

- 다양한 크기의 바퀴를 고려할 수 있는 계산기
  - 기어와 연결된 뒷바퀴가 큰바퀴일 경우, 한 바퀴 돌 때 멀리감
  - 작은바퀴일 경우 한 바퀴 돌려도 얼마 못감

> 위와 관련된 스펙이 미국에서 기어인치(=바퀴 지름 x 기어비)라고 함
> 이 때, 바퀴 지름은 = 바퀴테(rim) 지름 + 타이어 높이의 두 배

Gear 에 새로운 행동 추가

```typescript
class Gear {
  readonly cog: number;
  readonly chainRing: number;
  readonly rim: number;
  readonly tire: number;

  constructor(cog: number, chainRing: number, rim: number, tire: number) {
    this.cog = cog;
    this.chainRing = chainRing;
    this.rim = rim;
    this.tire = tire;
  }

  ratio() {
    return this.chainRing / this.cog;
  }

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * (this.rim + this.tire * 2);
  }
}

let myGearInches = new Gear(52, 11).gear_inches();
let friendGearInches = new Gear(20, 5).gear_inches();
```

현재 모습이 코드 최선으로 배치하는 방법일까?
정답은 **상황에 따라 다르다** 이다.

### 2.2.2 단일 책임 원칙은 왜 중요한가?

쉽게 수정할 수 있는 애플리케이션은 재사용하기 쉬운 클래스로 구성

재사용하기 쉬운 클래스란 쉽게 가져다 쓸 수 있는 코드(pluggable units)

- 잘 정의되어 있는 행동의 묶음
- 레고블록 같은거

한 개 이상의 책임이 있는 클래스는 재사용이 어려움

- 여러 책임들이 서로 얽힐 가능성 높음
- 특정 행동만 재사용하고 싶어도 우리가 원하는 부분만 가져오기 어려움
- 이 상황에서 할 수 있는 거
  - 코드 복붙하기
  - 리얼 끔찍. 유지보수 어렵게 만들고 버그 양산

재사용하려는 클래스는 스스로의 역할에 대해 혼란스럽고 책임들이 뒤얽힘

- 수저애향함
- 클래스가 바뀔 때마다 이 클래스를 사용하는 모든 클래스에서 문제 발생 가능성 높음

### 2.2.3 클래스에게 하나의 책임만 있는지 알아보기

1. 클래스가 인격이 있는 것처럼 질문하기. 예컨대,

- ex. Gear 님, 당신의 기어비는 무엇인가여?

2. 클래스의 책임을 한 문장으로 만들어보기

- 최대한 작으면서 유용한 것만 행해야 하는 것(smallest possible useful thing)
- 가장 단순한 표현이 `그리고`, `또는` 이라는 단어 사용시 연관된지 않은 둘 이상의 책임을 가지고 있다고 판단

**응집력**
클래스 안의 모든 것들이 1 개의 핵심 목표와 연관되어있을 때 이 클래스는 강하게 응집되어 있음.
또는 1 개의 책임을 가진다고 말할 수 있음

> Gear 클래스의 책임을 표현하자면
> "앞, 뒤 톱니바퀴 사이의 기어비를 계산한다": Gear 클래스는 많은 거 하고 있음
> "자전거에 기어가 미치는 영향을 계산한다": 더 어울림
> 그렇다면 gear_inches 는 Gear 에 속하는 것이 맞음. 하지만 **타이어 높이는 애매**

### 2.2.4 언제 디자인 결정할지 판단하기

Gear 처럼 불안한 클래스를 본다면,
"지금 암것도 안하면 나중에 어떤 대가 치를까?" 라고 질문하기

현재 Gear 는 다른 객체와의 의존성이 생길 경우 `투명함`과 `적절함`을 잃게 됨
바로 이 순간이 코드 재구성해야할 때

## 2.3 변화를 받아들일 수 있는 코드 작성하기

### 2.3.1 데이터가 아닌 행동에 기반한 코드 작성

객체는 행동과 함께 데이터를 가짐

- 데이터는
  - 인스턴스 변수를 참조하거나
  - 인스턴스 변수를 감싸는 `accessor method`를 통해 접근

#### 인스턴스 변수 숨기기

변수 직접 참조하기 보다 언제나 accessor 를 통해 접근하기

```typescript
class Gear {
  constructor(readonly cog: number, readonly chainRing: number) {}
  getCog() {
    return this.cog;
  }
  ratio() {
    // return this.chainRing / this.cog; // 멸망의 길
    return this.chainRing / this.getCog();
  }
}
```

`여러 곳에서 참조하고 있는 데이터` 에서 `단 한 번만 정의된 행동`으로 변경

- 직접 참조하기 단점
  - 만약 `cog`를 열 군데에서 참조시 내용 바꿔야 한다면 10 군데 전부 일일히 수정해야함
- accessor 의 장점
  - cog 수정시 getter 메서드만 수정하면 됨.

데이터를 마치 `메시지를 이해하는 객체` 처럼 취급하는 것은 두 가지 새로운 이슈를 발생

1. 가시성

- public vs private (4 장 유연한 인터페이스 만들기에서 다시 다룸)

2. 추상적

- 모든 변수를 래퍼 메서드로 감싸고 변수를 객체처럼 사용할 수 있음
- 이 때문에, 데이터와 객체 사이의 구분이 무의미
- 가끔 애플리케이션의 특정 부분을 행동과 무관한 데이터라 생각하는게 편리하지만
- 대부분의 경우 데이터를 일반적인 객체로 이해하는게 맘편함

#### 데이터 구조 숨기기

```typescript
class ObscuringReference {
  constructor(readonly data: array) {}

  diameter() {
    return this.data[0] + this.data[1] * 2;
  }
}
```

data 는 복잡한 구조여서 단순히 인스턴스 변수 감추는 것으로 불충분

- **data 메서드를 전송하는 객체는 배열의 어느 위치에 어떤 데이터가 들어있는지 알아야함**

diameter

- 메서드는 지름을 계산하는 방법만 아는게 아니라
- 배열의 어디에서 바쿠테 지름과 타이어 높이를 찾아야하는지도 알고 있다.
  - `[0]`: 바퀴테 지름, `[1]`: 타이어 지름
  - **이런 지식은 배열의 구조에 의존적**
  - 전혀 DRY 하지 않음
  - 이런 지식은 **단 한 곳에서 관리되어야 함**
- 왜냐면 복잡한 구조를 직접 참조시 진짜 데이터가 무엇인지 드러나지 않음
- 또한, 배열의 구조 변경시 그 영향이 코드 전체로 퍼짐

- **복잡한 구조를 직접 참조하면 진짜 데이터가 무엇인지 드러내지 않기 떄문에 헷갈림**
- 배열 구조 바뀔 때마다 모든 참조지점 찾아서 수정해야 하기 때문에 지옥의 유지보수 경험

해결해보자

- diameter 는 배열의 내부 구조에 대한 지식이 0
  - diameter 는 wheels 메시지가 enumerable 을 반환하는 것만 알고 있음
- 입력받은 배열의 구조에 대한 모든 지식은 wheelify 메서드 속에 격리됨
  - 만약 입력 값 변하면 여기만 바꾸면 됨

정리하자면, `데이터 구조를 들여다 보단 작업`을 `객체에 대한 메시지를 전송`으로 대체

- wheelify 메서드는 구조에 대한 지저분한 정보를 한쪽에 몰아 놓고 코드를 DRY 하게 만듬

```typescript
interface WheelInterface {
  rim: number;
  tire: number;
}

class Wheel implements WheelInterface {
  public rim: number;
  public tire: number;

  constructor(rim: number, tire: number) {
    this.rim = rim;
    this.tire = tire;
  }
}

class RevealingReferences {
  readonly wheel: Wheel;

  constructor(data: Array<number>) {
    this.wheel = this.wheelify(data);
  }

  wheelify(data: Array<number>) {
    const [rim, tire] = data;
    return new Wheel(rim, tire);
  }

  diameter() {
    return this.wheel.rim + this.wheel.tire * 2;
  }
}

console.log(new RevealingReferences([10, 20]).diameter());
```

### 2.3.2 모든 곳에 단일 책임 원칙을 강제하라

클래스 뿐 아니라 메서드에서도 단일 책임 원칙 강제하자

```typescript
gear_inches() {
  return ratio * (rim + (tire * 2));
}
```

gear_inches 속에 바퀴의 지름을 구하는 계산이 숨어있음

- 이 계산을 diameter 메서드로 추출하면 클래스의 책임을 좀 더 쉽게 파악 가능

```typescript
gear_inches() {
  return ratio * diameter;
}
diameter() {
  return rim + (tire * 2);
}
```

메서드가 하나의 책임을 질 때

- 클래스가 하는일이 무엇인지 명확해짐
- 주석 넣을 필요 없음
- **메서드 속에 있는 코드 한 조각에 주석을 달아야 한다면 별도의 메서드로 추출**
  - **메서드 이름이 주석과 동일한 역할**
- 재사용 유도
- 다른 클래스로 옮기기 쉬움

#### 클래스의 추가적인 책임들을 격리시키자

**너무 많은 책임을 지고 있는 클래스가 있다면, 이 책임을 다른 클래스 속으로 분리하자.**

- 핵심 클래스의 집중하자
- **아직 제거하기 어려운 추가적인 책임을 발견했다면 그 책임을 격리시키자**

## 2.4 드디어, 진짜 바퀴

```typescript
class Gear {
  readonly cog: number;
  readonly chainRing: number;
  readonly wheel: Wheel;

  constructor(cog: number, chainRing: number, wheel: Wheel) {
    this.cog = cog;
    this.chainRing = chainRing;
    this.wheel = wheel;
  }

  ratio() {
    return this.chainRing / this.cog;
  }

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * this.wheel.diameter();
  }
}

class Wheel {
  rim: number;
  tire: number;

  constructor(rim: number, tire: number) {
    this.rim = rim;
    this.tire = tire;
  }

  diameter() {
    return this.rim * (this.tire * 2);
  }
}
```

Gear 와 Wheel 모두 1 개의 책임안 지게 됨.

## 요약

수정하기 쉽고 OOP 소프트웨어 만드는 길은 **1 개의 책임을 지는 클래스** 만드는 것부터 시작

- 그 행동을 애플리케이션의 다른 부분들로 분리시키는것
- 이 분리가 예상치 못한 결과로부터 자유로운 수정을 할 수 있도록
- 중복 없이 코드 재사용할 수 있도록 함

클래스는 데이터와 행동을 가짐

- 어떤 행동을 구현할까?
- 1 개의 클래스는 다른 클래스에 대해 얼마나 알고 있을까?
- 다른 클래스에게 어느 정도까지 열려 있을까?
- `단순해야 한다` 라는 것에 집중하여 위 질문에 답하기

- 단일 책임 원칙
  - 클래스가 인격 있는 것처럼 물어봐서 확인하기 (Gear 님 당신의 기어비는 무엇인가여)
  - 클래스의 책임을 한문장으로 만들어보기

기법

- 인스턴스 변수 숨기기
  - 변수 직접 참조 말고, accessor 를 통해 접근하기
  - `여러 곳에서 참조하고 있는 데이터` 에서 `단 한 번만 정의된 행동`으로 변경
  - 데이터 구조 변경시 getter 만 수정하면 이득
- 데이터 구조 숨기기
  - 데이터 구조 복잡할 경우, 데이터 구조에 대한 지저분한 정보를 한쪽에 격리
- 단일책임 원칙을 클래스, 메서드에게 강제하기
- 클래스의 추가 책임을 격리시키기
  - 너무 많은 책임을 지고 있는 클래스가 있으면, 다른 클래스로 분리
ㅅ