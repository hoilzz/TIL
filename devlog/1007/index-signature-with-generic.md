# 인덱스 시그니처의 키값을 제네릭으로 할당하기

##

```js
type MapWithDynamicKey <T extends string> = {
    [index in T]: string | string[];
}

type IParams = 'job' | 'age'

const asd: MapWithDynamicKey<IParams> = {
    'job': 'asd',
    'age': 'asd',
}
```
