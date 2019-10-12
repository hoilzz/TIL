# split reducer or not

[using combioneReducer](https://redux.js.org/recipes/structuring-reducers/using-combinereducers)

## Core Concepts

리덕스 앱의 가장 일반적인 state 모양은 top level 에서 도메인 위주 데이터를 slice를 포함한 JS 객체다.

"slice reducer" 함수는 state 의 특정 슬라이스의 모든 업데이트에 대한 책임을 갖는다. 여러개의 슬라이스 리듀서는 동일한 action에 응답할 수 있다. 독립적으로 필요에 따라 자신의 slice를 업데이트할 수 있다. 그리고 업데이트된 슬라이스는 새로운 상태 object로 결합된다.

`combineReducers`를 사용 할 때 알아둬야할 중요한 아이디어

- 리듀서 작성할 때 사용하는 단순한 유틸함수다. 그러니까 필수로 안써도 됨.
- 그럼 언제 씀?
  - 앱이 점점 커지면서, reducer 함수를 분리시키면서 그 분리된 리듀서는 상태의 독립적인 부분만 관리.
- 모든 child reducer를 호출하고 그 결과물들을 single state object로 모은다.
  - 그래서 단 한개의 액션이라도 dispatch 되면 모든 reducer를 호출한다.
  - new state tree를 완성하기 위해, 각 slice reducer를 현재 slice state와 action으로 업데이트하고 응답할 기회를 준다.

> Notes
> 리덕스 자체는 너의 상태가 어떻게 구성되어있는지 상관하지 않는다. 하지만 comebineReducer는 에러를 피하기 위해 규칙을 강제한다.
>
> - 인식되지 않는 action에 대해, 첫번째 인자로 주어진 state를 리턴해야한다.
>   - swtich문을 사용한다면 default를 반드시 이용하여 인자로 받은 state를 그대로 리턴
>   - 왜냐하면 slice reducer들의 결과를 모아서 single state tree 완성해야하기 때문.
> - `undefined` 절대 리턴 ㄴㄴ. 걍 state에 Es6 optional argument 문법 이용해서 initialState를 넣어놔
