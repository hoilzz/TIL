# Store
- 스토어는 어플리케이션의 현재 상태를 지니고있음,
- 리덕스를 사용하는 어플리케이션은 단 하나의 스토어가 있어야함.
- 스토어를 만들려면 리덕스에서 createStore를 부른 다음에 리덕스를 인수로 전달하여 해당함수 실행

## 스토어가 하는 일
### dispatch(action)
- action을 리듀서로 보낸다
- 디스패치가 실행되면 스토어는 리듀서 함수에 현재 자신의 상태와 방금 전달받은 액션을 전달해준다.
- 그러면 리듀서가 어떠한 변화가 필요한지 알아내서 변화를 주고 새상태를 주면 현상태에 갈아끼운다.

### getState()
- 현재 상태를 반환하는 함수

### subScribe(listner)
- 상태가 바뀔때마다 실행할 함수 등록
- 리스너가 콜백함수

### replaceReducer(nextReducer)
- 핫리로딩과 코드분할을 구현할 때 사용.보통사용할 일 업승ㄴ 안다룬

초기 상태가 프린트 된걸 볼 수 있다. 그러면 상태 변화가 있을 때마다 특정함수 실행해보자.


## index.js
```javascript
const store = createStore(reducers);
```
- 이렇게 하면 스토어 생성 완료
- 스토어 생성시 인수로 `reducer`를 전달
- 스토어를 컴포넌트에 연결하기 전에 리덕스에 대한 이해를 위해 먼저 사용해보자.
- 현재 상태를 기록하게 해보자

```javascript
console.log(store.getState());
store.subscribe(()=>console.log(store.getState()));
store.dispatch(actions.increment());
```

- 그러면 상태 변화가 있을 때마다
- `subscribe` 함수를 이용, 스토어 변화 있을 때마다 `store.getState()` 실행

```javascript
const unsubscribe = store.subscribe(()=>console.log(store.getState()));
```
- 액션을 보내보자
- 직접 만들어도 되고 actionCreate함수를 통해 만들어도된다.
- 일단 액션을 보내려면 dispatch 함수 이용

- 만약에 리스너를 언스크라이브 즉 더이상 알림 받기 싫다
```javascript
const unsubscribe = store.subscribe(()=>console.log(store.getState()));

unsubscribe();

store.dispatch(actions.setColor([21, 21, 21]));
```
- `unsubscribe()` 후에 dispatch해도 unsubscribe이기 때문에 아무것도 프린트 되지 않는다.

컴포넌트에서 리덕스 스토어 안에 있는 데이터를 사용 혹은 변화를 줄텐데, 그렇게 하려면 AppComponent의 스토어를 props로 전달해서 하위 컴포넌트에서 `getState()`, `dispatch()`를 통해 데이터를 읽어오거나 변화를 줄 수 있다. **하지만!** 구조가 굉장히 복잡해진다. 리액트에서 리덕스를 더 편하게 쓸 수 있는데 그건 **react-redux** 라는 `뷰 레이어 바인딩` 도구 사용하는 것이다.
