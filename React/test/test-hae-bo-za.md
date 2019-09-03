# Test zebal hae-bo-za

리억스의 대부분 코드는 함수고 pure하기 때문에, mocking 없이 테스트하기 쉽다.

## setting up

node환경(DOM에 접근할 필요가 없다)에서 실행되는 jest를 사용하자.

## 리듀서

리듀서는 이전 상태에 action을 적용한 후에 새로운 상태를 반환해야한다.

예제로 살펴보기

todo 추가하는 액션이 있다. 이 액션은 텍스트를 payload로 가진다.

```js
import { ADD_TODO } from '../constants/ActionTypes';

const initialState = [
  {
    text: 'Use Redux',
    completed: false,
    id: 0,
  },
];

export default function todos(state = initialState, action) {
  switch (action.type) {
    case ADD_TODO:
      return [
        {
          id: state.reduce((maxId, todo) => Math.max(todo.id, maxId), -1) + 1,
          completed: false,
          text: action.text,
        },
        ...state,
      ];

    default:
      return state;
  }
}
```

todo 추가 액션을 처리하는 리듀서에서 어떤 것을 테스트할 수 있을까?

- state에 아무것도 없을 때 todo 추가
- state에 todo가 있을 때 todo 추가

```js
import reducer from '../../structuring-reducers/todos';
import * as types from '../../constants/ActionTypes';

describe('todos reducer', () => {
  it('should handle ADD_TODO', () => {
    expect(
      reducer([], {
        type: types.ADD_TODO,
        text: 'Run the tests',
      })
    ).toEqual([
      {
        text: 'Run the tests',
        completed: false,
        id: 0,
      },
    ]);

    expect(
      reducer(
        [
          {
            text: 'Use Redux',
            completed: false,
            id: 0,
          },
        ],
        {
          type: types.ADD_TODO,
          text: 'Run the tests',
        }
      )
    ).toEqual([
      {
        text: 'Run the tests',
        completed: false,
        id: 1,
      },
      {
        text: 'Use Redux',
        completed: false,
        id: 0,
      },
    ]);
  });
});
```

> toEqual은 jest에서 제공해주는 함수로써, deepEqual 비교를 한다.
