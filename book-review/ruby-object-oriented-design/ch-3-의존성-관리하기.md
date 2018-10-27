# 3. 의존성 관리하기

객체간 서로 협업하려면 서로에 대해 지식이 있어야함. **이 지식은 의존성을 만듬**

## 3.1 의존성 이해하기

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
    return this.ratio * new Wheel(rim, tire).diameter();
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

### 3.1.1 의존성 있다는 거 알기

객체는 다음과 같은 내용을 알고 있을 때 의존성을 가짐

- 다른 클래스의 이름
  - Gear 는 Wheel 이라는 이름의 클래스가 있다는 걸 알고 있음
- 자기 자신을 제외한 다른 객체에게 전송할 메시지의 이름
  - Gear 는 Wheel 의 인스턴스가 diameter 라는 메서드를 이해할 수 있다는 것을 알고 있음
- 메시지가 필요로 하는 인자들
  - Gear 는 Wheel.new 를 위해 rim 과 tire 를 인자로 넘겨야 한다는 것을 알고 있음
- 인자들을 전달하는 순서
  - Gear 는 Wheel.new 의 첫번째 인자가 rim, 두번쨰 인자가 tire 라는 것을 알고 있음

위에서 나열한 의존성은 Wheel 을 변경시 어쩔 수 없이 Gear 도 수정해야 하는 상황을 만듬
협업 과정에서 의존성이 생기는 것은 어쩔 수 없지만, 불필요한 의존성은 Gear 클래스의 수정을 강제함

### 3.1.2 객체들 간의 결합

이런 의존성은 Gear 를 Wheel 에 결합(couple) 시킴.

둘 이상의 객체가 강력하게 coupling 되어있을 때

- 이들은 한덩어리로 움직이고 재사용하는 것 불가능
- 하나 바꾸면 다른 모든 것을 변환

## 3.2 약하게 결합된 코드 작성하기

### 3.1.2 의존성 주입하기

클래스의 이름을 통해 다른 클래스를 참조하는 방식은 코드의 결합도를 높임
아래 예제는 **gear_inches 메서드는 Wheel 클래스를 명시적으로 참조**

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

  gear_inches() {
    return this.ratio * new Wheel(rim, tire).diameter();
  }
}
```

Wheel 클래스를 직접 참조하면

- gear_inches 메서드는 Wheel 인스턴스의 기어 인치만을 계산하겠다고 명시적 선언
- 즉, Gear 는 다른 객체와 협업하기를 거부

중요한 것은 `객체의 클래스가 무엇인지`가 아닌, `우리가 전송하는 메시지가 무엇인지`가 중요
**Gear 에게는 diameter 메서드에 반응할 수 있는 객체가 필요**

- Gear 는 대상이 되는 객체가 뭔지 알필요 1 도 없음
- Wheel 이 초기화 되기 위해 rim 과 tire 가 필요하다는 것도 알필요 ㄴㄴ

**Gear 는 diameter 를 알고 있는 객체만 있으면됨**

#### 의존성 주입

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

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * this.wheel.diameter();
  }
}

Gear.new(52, 11, Wheel.new(26, 1.6)).gear_inches();
```

위 코드에서

- Gear 는 wheel 객체가 Wheel 클래스의 인스턴스라는 것을 알지도 못하고 관심도 없음

`의존성 주입` 후 장점은

- **Wheel 인스턴스를 Gear 클래스 바깥에서 생성하기 때문에 Gear 와 WHeel 사이의 결합이 없어짐**
- 이제 Gear 는 diameter 를 구현하고 있는 어떤 객체와도 협업 가능

### 3.2.2 의존성 격리시키기

_불필요한 의존성을 모두 제거하면 좋지만 현실적으로 불가능한 경우 있음_

의존성 제거 어려운 경우, 의존성을 클래스 안에서 격리시켜야함

의존성은

- 간결하게 정리되고
- **명시적으로 드러나고**
- 격리되어야함

#### 인스턴스 생성을 격리시키기

Gear 에 Wheel 을 주입할 수 없다면
새로운 Wheel 인스턴스를 만드는 과정을 Gear 클래스 내부에 격리시켜야 함

이는

- 의존성을 명시적 노출
- Wheel 이 Gear 클래스 내부에 스며들지 않도록 하기 위함

다음 두 개의 예시를 보자.

1. 새로운 Wheel 인스턴스 생성하는 과정을 Gear 의 gear_inches 메서드에서 initialize 메서드로 이동
   - initialize 메서드를 통해 hweel 에 대한 의존성 명시적 표현
   - 대신, Gear 가 새 인스턴스 만들 때마다 무조건 Wheel 인스턴스 생성

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

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * this.wheel.diameter();
  }
}
```

이를 보완한 거는

2. 명시적으로 정의된 wheel 메서드를 통해 Wheel 인스턴스 생성하기
   - || 를 이용하여 객체가 필요한 순간에, WHeel 인스턴스 생성

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

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * this.wheel.diameter();
  }

  wheel() {
    return this.wheel || Wheel.new(this.rim, this.tire);
  }
}
```

위 두 예시에서도 Gear 는 너무 많은 것을 알고 있음

- 여전히 rim 과 tire 를 초기화 인자로 넘겨야 하고
- Gear 를 위해 Wheel 인스턴스 생성해야 함

  - Wheel 이 아닌 다른 객체로는 gear_inches 메서드 이용 불가

- 그래도 나아진 점은
  - gear_inches 가 갖고 있던 의존성을 줄이고
  - Gear 가 Wheel 에 의존하고 있다는 사실 또렷하게 드러낼 수 있음

#### 외부로 전송하는 메시지 중 위험한 것 격리시키기

외부 클래스 이름 참조하는 지점을 격리시켰으니 `외부로 전송되는 메시지`를 보자.

> 외부로 전송되는 메시지: 나 자신이 아닌 객체에게 보내는 메시지

```typescript
gear_inches() {
    // 무시무시한 수학 공식 몇 줄
    foo = this.ratio * this.wheel.diameter();
    // 무시무시한 수학 공식 몇 줄
}
```

wheel.diameter 가 복잡한 메서드에 파묻힐 경우

- 이런 외부에 대한 의존성을 gear_inches 메서드 속에 심어 놓는 것을 불필요
- gear_inches 를 취약하게 만듬

외부에 대한 의존성을 걷어내고, 의존성을 클래스 내부의 메서드 속에 캡슐화 시켜서
gear_inches 메서드를 수정할 일을 줄이자.

```typescript
gear_inches() {
    // 무시무시한 수학 공식 몇 줄
    foo = this.ratio * this.diameter();
    // 무시무시한 수학 공식 몇 줄
}

// 클래스 내부에 메서드 속에 캡슐화
diameter() {
    return wheel.diameter();
}
```

- gear_inches 에서 외부에 대한 의존성 걷어내기
- Wheel 이 diameter 메서드의 이름과 시그너처 바꿔도
  - **Gear 에 미치는 영향은 이 작은 래퍼 메서드에 한정**

_정리하자면_

클래스가 내부에서 변하기 쉬운 메시지를 참조하고 있을 때 이 기술 유용하게 사용

- 참조하는 지점을 격리시키는 것은 이런 변화의 영향에 안전하게 대응 가능

### 3.2.3 인자 순서에 대한 의존성 제거

인자를 해시로 바꾸기. javascript 로 하면 object 로 전송하기

이점

- 순서에 대한 의존성 제거
  - 순서가 고정도니 인자는 코드 덜 작성하지만, 위험도 증가
  - 대신 키의 이름에 의존하게됨
- 새로운 초기화 인자 및 기본값 설정 넘나 쉬움
- 다른 코드에 아무런 영향 ㄴㄴ

#### 멀티파라미터 초기화 고립시키기

우리가 메서드 수정할 수 없는 경우도 있음. _프레임워크를 사용할 경우_

상황을 우리가 통제할 수 없지만,
**wrapper 메서드를 통해 프레임워크 메서드를 감싸서 코드를 DRY 하게 만들기 가능**

```typescript
// Gear가 외부 프레임워크의 한 부분일 때
// Gear/index.js

class Gear {
  readonly cog: number;
  readonly chainRing: number;
  readonly wheel: Wheel;

  constructor(cog: number, chainRing: number, wheel: Wheel) {
    this.cog = cog;
    this.chainRing = chainRing;
    this.wheel = wheel;
  }
}

// GearWrapper.js
// 외부 인터페이스를 감싸는 모듈을 만들어 변화를 받아들이자.
import Gear from 'Gear';
export gear (arg) {
    Gear.new(arg.cog, arg.chainRing, arg.wheel)
}

// myCode.js
import * as GearWrapper from './GearWrapper';

GearWrapper.gear({
    chainring: 15,
    cog: 11,
    wheel: new Wheel(26, 1.6).gear_inches()
})
```

위 코드에서 GearWrapper 의 두 가지를 기억하자

1. 래퍼 모듈
   - GearWrapper 인스턴스 안만들어도 gear 메세지를 전송하는 명시적이고 독립적인 객체
2. 오로지 다른 클래스의 인스턴스를 생성하기 위해 존재
   - 보통 Factory 패턴이라고 부름(Factory 는 객체를 만들기 위해 존재)

## 3.3 의존성의 방향 관리하기

```typescript
class Gear {
  readonly cog: number;
  readonly chainRing: number;

  constructor(cog: number, chainRing: number) {
    this.cog = cog;
    this.chainRing = chainRing;
  }

  ratio() {
    return this.chainRing / this.cog;
  }

  gear_inches(diameter) {
    return this.ratio * diameter;
  }
}

class Wheel {
  rim: number;
  tire: number;
  gear: Gear;

  constructor(rim: number, tire: number, gear: Gear) {
    this.rim = rim;
    this.tire = tire;
    this.gear = gear;
  }

  diameter() {
    return this.rim * (this.tire * 2);
  }

  gear_inches() {
    gear.gear_inches(diameter);
  }
}
Wheel.new(26, 1.6, 62, 11).gear_inches();
```

위에서는 Wheel 이 Gear 나 ratio 에 의존.

- 사실 바뀐거 없음
- 하지만 선택한 의존성의 방향은 이후 애플리케이션의 발전 과정에 영향을 미침

### 3.2.2 의존성의 방향 결정하기

클래스가 사람이라고 생각해보자. **자기 자신보다 덜 변하는 사람에게 의존해야 함**

위 간단한 문장은 단순한 진실 세 가지를 기반으로 다듬을 수 있음

1. 어떤 클래스는 다른 클래스에 비해 요구사항이 더 자주 바뀜
2. 구체 클래스는 추상 클래스보다 수정 횟수가 빈번
3. 의존성이 높은 클래스를 변경하는 것은 코드의 여러 곳에 영향을 미침

#### 1. 변경될 가능성이 얼마나 높은지 이해하기

다른 클래스와 비교하여 얼마나 변경되지 않는지를 기준으로 순위 매기기

#### 2. 구체적인 것과 추상적인 것을 인지하기

**추상적** 은 `구체적인 것으로부터 분리된` 것.

예륻 들어 알아보자.

1. Gear 가 Wheel, Wheel.new, Wheel.new(rim, tire)에 의존적일 때
   - Gear 는 `구체적인 코드`에 의존적
2. Wheel 을 Gear 에 주입하는 (의존성 주입) 방식으로 수정하면서
   - Gear 는 `추상적인 것`에 의존
   - Gear 는 `diameter 메시지에 반응하는 어떤 객체를 필요로 한다`라는 `추상적인 사실`에 의존

2 번에서 `interface`를 정의했다고 볼 수 있음

추상화의 훌륭한 점은

- 일반적이고 안정적 성질 지님
- 추상화된 인터페이스는 인터페이스가 기반하고 있던 구체 클래스보다 변경 적음
- interface 도 의존성이 있기 때문에 디자인할 때 중요

## 3.4 요약

의존성 주입은

- 느슨하게 결합된 객체
- 창의적으로 재사용 할 수 있는 객체 만들어줌

의존성 격리는

- 객체가 예상치 못한 변화에 빨리 적응할 수 있도록 해줌

이 때, `추상화`를 사용하는 것은

- 위와 같은 변경에 직면해야 하는 경우를 줄여줌

평온한 유지보수는 자기 자신보다 덜 변하는 것에 의존하는 클래스들로 덮여있음.

---

의존성 있다는 거 알기
어떤 객체가 다음 내용을 알고 있을 때 의존성 발생

- 다른 클래스의 이름
- 다른 객체에게 전송할 메시지의 이름
- 메시지가 필요로 하는 인자들
- 인자들 전달 순서

결합(coupling) 약하게 하기

- 의존성 주입하기
- 주입할 수 없다면 의존성 격리시키기
  - 격리가 걍 숨기는게 아닌
    - 의존성 명시적 노출
    - 격리될 객체가 내부에 스며들지 않게 하기 위해
  - 인스턴스 생성을 격리시키기
  - 외부로 전송하는 메시지 중 위험한 것 격리시키기 (메서드래퍼로 격리시키기)

인자 순서에 대한 의존성 제거

- 해시 이용하기
- 메서드를 직접 수정 불가능한 경우(프레임워크 이용 등)
  - wrapper 메서드를 통해 프레임워크 메서드 감싸기

의존성 방향 결정하기
기준은

- 클래스의 요구사항 바뀌는 횟수
- 구체적인 것과 추상적인 것 인지하기(추상적인 것에 의존하기)
  - 구체 클래스는 추상 클래스보다 수정횟수가 빈번
