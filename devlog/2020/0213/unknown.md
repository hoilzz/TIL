# unknwon

[ts 3.0](https://engineering.huiseoul.com/%ED%83%80%EC%9E%85%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8-3-0-99e5d45ec439)

least-capable 타입을 사용하고 싶을때.
"API에서 이것은 어떤 값이든 될 수 있으니 사용 전에 어떤 타입인지 확인하시오"의 경우.

이렇게 하면 반환된 값을 **안전하게 검사해야한다.**

any와 마찬가지로 어떤 값이든 unknown에 할당 될 수 있다.

**any와 다른점은**

- unknwon 타입의 값의 경우 접근 불가.
- 인스턴스도 생성 불가
- unknwon이나 any에만 할당 가능.

**그럼 어케 접근?**

**타입 체킹 수행한다**

```ts
let foo: unknown = 10;
```
