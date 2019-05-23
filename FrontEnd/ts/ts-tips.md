# TypeScript tips

```ts
function getToken() {
  return localStorage.getItem('token');
}
```

위 코드는 컴파일러 에러가 없다.

인자는 없고, 리턴은 있는데.. localStorage는 브라우저 API다. localStorage에 마우스를 올려보자.

얘의 파일을 보면 lib.dom.d.ts 다. 얘는 구현체가 아니다. 구현체를 보려면 구글링하면된다.

이 명세는 어디서 어떻게 정할까? tsconfig에서 정할 수 있다. lib는 일단 보면 주석처리 되어있다.

---

다른거 axios 보자.

얘는 내장된 얘도 아니고 구현체 자체도 쓰지 않음. 여튼 axios 모듈 설치해보자.

import 하면 관련 에러 없어진다.

이유는?

axios 노드모듈안에는 구현체도 있고, 타입스크립트가 ㅇ이 노드모듈 사용할 수 있게 타이핑 된 파일이 있을 거다. ??d.ts 처럼 제공할거다.

index.d.ts를 어케 찾냐?

package.json에 typings가 가리키는 파일을 ts 컴파일러가 찾아간다.

## 두가지 타입 이상이 추론되는 경우

보통 `type(string, number, ..) | null`이 추론되는 경우가 있다.

우리가 선택할 수 있는 3가지는

1. type guard

2. type assertion

3. non-null assertion

위 세가지 중 가장 좋은거는?

타입가드다.

1. type guard

- 리터럴 타입가드.
- null은 리터럴 "값"이다.

> **타입가드는 꼭 배워놓자.**

```ts
```

2. type assertion

```ts
<string>token;
token as string; // 보통은 요고
```

위와 같이 사용하는 경우 a는 오염된 상태가 된다.

```ts
const a = token as string;
a.split('/'); // runtime error 발생 가능성
```

그럼 언제 쓸까? 해당 변수는 100% 이 타입이다. 라고 확신할 수 있을 때.

아래 listElement는 `HTMLElement | null`로 타입 추론되는데, 우리는 HTMLElement라고 확신할 수 있다. 왜냐하면 html에 있는 DOM이니까..

```ts
const listElement = document.querySelector('#list');
listElement.append(...)
```

3. non-null assertion

- 변수 뒤에 ! 붙여서 null 없애기
