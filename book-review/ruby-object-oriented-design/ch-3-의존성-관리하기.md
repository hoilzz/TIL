# 3. 의존성 관리하기

객체 사이의 상호 작용, 메시지를 통해 문제의 해결책을 제공.
- 각 메시지는 하나의 객체에서 시작되며 특정 행동을 유발하기 위해 존재
- 그러므로 어떤 행동을 유발하고자 할 때
  - 객체는 그 행동을 이미 알고 있거나: 얘는 2장에서
  - 상속받았거나: 6장 상속을 통해 새로운 행동 얻기
  - 그 행동에 대해 알고 있는 다른 객체에 대해 알아야 함: 얘는 의존성 관리하기

서로 협업하려면 객체는 다른 객체에 대한 지식이 있어야함.
_이 지식은 의존성을 만들어냄_

## 3.1 의존성 이해하기

만약 1개 객체를 수정했을 때, 다른 객체를 수정해야 한다면 후자는 전자에 대해 의존적

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

class Wheel {
  readonly rim: number;
  readonly tire: number;

  constructor(rim: number, tire: number {
    this.rim = rim;
    this.tire = tire;
  }

  diameter() {
    return this.rim + (this.tire * 2);
  }
}

Gear.new(52, 11, 26, 1.5).gear_inches();
```

### 3.1.1 의존성이 있다는 걸 알기

__객체가 다음 내용을 알고 있을 때__ 의존성을 갖음

- 다른 클래스의 이름
  - Gear는 Wheel이라는 이름의 클래스가 있다는 걸 알고 있음
- 자기 자신을 제외한 다른 객체에게 전송할 때 이름
  - Gear는 Wheel의 인스턴스가 diameter라는 메서드를 이해할 수 있다는 걸 알고 있음
- 메시지가 필요로 하는 인자들
  - Gear는 Wheel.new를 위해 rim과 tire를 인자로 넘겨야함
- 인자들을 전달하는 순서
  - Gear는 Wheel.new의 첫 번째 인자가 rim이고 두 번째 인자가 tire라는 걸 알고 있음

위에서 나열한 의존성들은 Wheel을 변경했을 때 어쩔 수 없이 Gear도 수정해야 하는 상황 만듬
- Wheel과 Gear는 꼭 협업해야 하니까 어쩔 수 없이 의존성은 생김
- 하지만 위에 나열한 의존성은 불필요함
- 불필요한 의존성은 코드를 덜 reasonable 하게 만듬
- 왜냐하면 이 의존성이 Gear 클래스의 수정을 강제하기 때문.(코드 수정이 애플리케이션 전체에 영향을 미쳐 여러 곳 수정해야하는 대공사도 유발)

### 3.1.2 객체들 간 결합

이런 의존성은 Gear를 Wheel에 결합(couple)시킴.
즉, 이런 결합이 의존성을 낳음.
- Gear가 Wheel에 대해 더 많이 알수록 강하게 결합됨

의존성이 높은 객체들은 마치 하나인 것처럼 행동. 이로인해,
- 이들 중 하나만 재사용하는 건 불가
- 하나 바꾸려면 다 바꿔야함

## 3.2 약하게 결합된 코드 작성하기

불필요한 의존성 제거하기 or 코드 결합도 낮추기

### 3.2.1 의존성 주입하기

클래스의 이름을 통해 다른 클래스를 참조하는 의존성은 겉으로 보기에 문제가 없음
- Wheel 클래스의 이름이 바뀌면 Gear의 gear_inches 메서드도 함께 변경
  - 사실 클래스 이름 변경되는 건 사소함(에디터 전체 변경하면됨)


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

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * Wheel.new(rim, tire).diameter();
  }
}
```

진짜 문제는
- Gear가 Wheel을 참조하는 부분을 gear_inches 메서드 속에 하드코딩 해놓았을 때
  - Gear는 Wheel 인스턴스의 gear_inches만을 계산하겠다고 명시적으로 선언
  - 즉, Gear의 gear_inches()는 다른 종류의 객체와 협업하기를 거부.
  - `Wheel.new(rim, tire)`가 하드코딩 되어있어서 diameter를 가진 다른 객체가 있어도 `gear_inches()` 사용 불가

중요한 것은 `객체의 클래스가 무엇인지`가 아닌 `우리가 전송하는 메시지가 무엇인지`이다
- __Gear는 대상이 되는 객체의 클래스가 무엇인지 알 필요 없음__
- `gear_inches()`를 계산하기 위해 __Gear가 Wheel의 존재를 알 필요 없음__
- __Gear에게는 diameter를 알고 있는 객체만 있으면 됨__

```typescript
class Gear {
  readonly cog: number;
  readonly chainRing: number;
  readonly wheel: object;

  constructor(cog: number, chainRing: number, wheel: object) {
    this.cog = cog;
    this.chainRing = chainRing;
    this.wheel = wheel;
  }

  // 새로 추가된 함수
  gear_inches() {
    // 타이어는 바퀴테를 가싸고 있어서, 지름 계산시 타이어 높이에 2를 곱함
    return this.ratio * Wheel.diameter();
  }
}

console.log(Gear.new(52, 11, Wheel.new(26, 1.5)).gear_inches());
```

Gear는 wheel 변수를 사용하고 wheel 메서드(getter)로 변수에 접근.
여기서 속지 말아야 할것
- Gear는 wheel 객체가 Wheel 클래스의 인스턴스 라는 것을 알지 못하고 관심도 없음
- __Gear가 아는 것은 자기 자신이 diameter 메서드에 반응할 줄 아는 객체를 가지고 있는 것 뿐__

위 코드 변화는 되게 작음. 하지만 엄청난 장점 있음
- __Wheel 인스턴스를 Gear 클래스 바깥에서 생성하기 떄문에 Gear와 WHeel 사이의 결합 없어짐__
- __이제 Gear는 diameter를 구현한 어떤 객체와도 협업 가능__

위 기술을 `의존성 주입`이라고 부름. 이를 통해 얻은 것은
- Wheel 초기화시 넘겨줘야 하는 인자와 인자의 순서에 대해 명시적 의존되고 있었음
- 의존성 주입을 통해 모든 의존성이 diameter 메서드에 대한 단 1개의 의존성으로 줄어듬
- 즉, Gear는 아는 것이 적어져서 더 똑똑해짐

정리하자면
- 클래스의 이름을 알아야할 의무
- 클래스에게 전송해야할 메시지를 알아야하는 의무
이 2개의 의무는 다른 객체가 책임져야할 문제 였음




