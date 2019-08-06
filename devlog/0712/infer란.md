# infer

U 이내에서 infer 선언에 의해 도입된 각 유형 변수에 대해 T에서 U까지 유추하여 후보 type 집합을 모은다.
(generic function에서 type 추론 하는 것과 동일한 추론 알고리즘을 이용한다.)

주어진 infer type 변수 V는, 만약 co-variant(공동 변수) 위치에서 추론된 후보가 있다면,
V의 추론된 타입은 후보군과 union 된다.

그렇지 않다면, 만약 contra-variant position에서 후보군이 추론된다면, V로 추론된 타입은 그것들과 intersection된다.
그렇지 않다면 V의 추론된 타입은 never 다.

---

### 조건부 타입에서 타입 추론

조건부 타입의 extends에서, 추론된 타입 변수를 도입하는 `infer` 선언 할 수 있다.
이러한 추론된 타입 변수는 조건부 타입의 true 브랜치에서 추론될 수 있다.
동일 변수에서 여러개의 `infer`를 가질 수 있다.

예를 들어, 다음은 함수 타입의 리턴 타입을 추론한다.

```ts
type ReturnType<T> = T extends (...args: any[]) => infer R ? R : any;
```
