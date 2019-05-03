# UnionType

유니온 타입이 있는 값이 있으면 유니온의 모든 타입에 공통 멤버만 접근 가능

```ts
interface Bird {
  fly();
  layEggs();
}

interface Fish {
  swim();
  layEggs();
}

function getSmallPet(): Fish | Bird {
  // ...
}

let pet = getSmallPet();
pet.layEggs(); // 좋아요
pet.swim(); // 오류
```

getSmallPet 호출시, Fish 거나 Bird의 리턴타입을 갖지만,

**유니온 타입이 있는 값이 있으면, 유니온의 모든 타입에 공통 멤버에만 접근 가능**

Fish의 속성이거나 Bird의 속성이 아닌 공통 멤버만 접근 가능.
