# typesafe actions

## Constants

action-helper를 이용하여 action type을 static property로 가지는 action-creator를 이용하면,
string 상수를 export하거나 재사용할 필요가 없다.
**string 상수** 를 이용하여 보일러플레이트 코드를 제거하고 간소화시켜준다.

여튼 string을 `as const`를 이용하여 선언하면, 동적 string operation 때문에 string으로 추론되는게 아닌 상수값 그대로 추론된다.

## Actions

Basic actions을 사용하여 action creator 만들기 ({ type, payload, meta })

> recommendation
> `RootAction`을 생성하여 모든 가능한 action type을 나타내자.

```ts
// types.d.ts
// example of including `react-router` actions in `RootAction`
import { RouterAction, LocationChangeAction } from 'react-router-redux';
import { TodosAction } from '../features/todos';

type ReactRouterAction = RouterAction | LocationChangeAction;

export type RootAction = ReactRouterAction | TodosAction;
```

## Action Helpers

Important thing to notice is that all these helpers are acting as a type-guard so they'll narrow tagged union type (RootAction) to a specific action type that we want.

Using action-creators instances instead of type-constants
