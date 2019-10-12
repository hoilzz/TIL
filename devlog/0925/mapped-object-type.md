# 인덱스 시그니처의 key의 특정 스트링만 정하기

```ts
interface IFilter {
  selected: boolean;
}

type IFilterNames = 'country' | 'price'

interface IFetchFilterResponse {
  // An index signature parameter type cannot be a union type. Consider using a mapped object type instead.
  [key: IFilterNames]: IFilter
}
```

index signature 파라미터 타입은 union type이 될 수 없다.
mapped object type을 대신 사용해라.

## mapped object type?

[mapped-types](http://www.typescriptlang.org/docs/handbook/advanced-types.html#mapped-types)


A mapped object type operates on a set of singleton types and produces a new object type where each of those singletons is turned into a property name

매핑 된 객체 유형은 일련의 singleton type에서 작동하며 각 singleton type이 속성 이름으로 바뀌는 새 object type을 생성합니다.
