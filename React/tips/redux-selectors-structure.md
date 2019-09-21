# 리덕스 셀렉터 구조화하기

[selector 구조화하기](https://cmichel.io/redux-selectors-structure)를 번역

## 셀렉터에서 우리가 원하는건 뭘까?

일반적인 이슈를 요약 해보자.

1. 컴포넌트는 **selectors** 를 통해 상태에 접근하고 모든 셀렉터는 **root** 상태를 인자로 전달해줘야한다.
   이것은 combineReducers로 된 _sub-reducer_ 의 경우도 동일하다. 이러한 방식으로 컴포넌트는 **내부** 상태 표현과 완전히 디커플링 될 수 있다.

2. 첫번째 포인트는 **root** 상태를 인자로 전달하는 _global_ selector를 작성하는거다.
   하지만 개발 편의를 위해 **root상태의 자식을 인자로 받는** **local** selector를 작성한다.
   이러한 방식으로 우리는 상태를 unpack(.으로 풀어주지 않아도됨) 다른 root state의 부분이 접근하지 못하여 sub-reducer가 올바르게 디커플링될 수 있다.

3. _local_ selector를 global selector와 매핑하는 케머니즘이어야한다. 그래서 **셀렉터를 딱 한번 구현하고 1개의 파일만 만들어야한다.** 이렇게 하면 코드 중복성이 없고 시간이 더 효율적이다.

## 리덕스 파일 구조

![img](https://d33wubrfki0l68.cloudfront.net/70db2fa6a1b1b6c6dd586dcf3d4c89bd0796b829/e85d3/static/statetree-65d6460f53e1fe9b42582625a121cc86.svg)

3개의 sub 상태를 가진다: navigation, noti, settings.

- 이것은 서로 독립적이어야 한다.
- 3개의 리듀서를 만들고 combineReducer로 결합해야 한다.

리덕스 파일을 store를 분리하듯이 3개의 서브 폴더로 분리했다.

![img](https://d33wubrfki0l68.cloudfront.net/a0118266540ce3559f6ae51662d66a55356171d7/d55f9/static/reduxfilestructure-c555a3970977d0d9e5221b1a9270eb6e.svg)

각 서브 폴더는 reducer, local selector, action을 포함한다.
스토어 폴더는 모든 로컬 셀럭터를 모으고 그것들을 **globalize** 하는 selectors.js 파일을 포함한다.

## 리듀서와 셀렉터가 동일한 파일에 있다면?

어떤 사람들은 리듀서 파일에 셀럭터를 놓는다. 하지만 나는 분리하는 것을 선호한다.
일단, 순환 import 의존성을 피하기 위해서다. 하지만 아래와 사진과 같은 문제에 직면한다면 좋지 않은 설계를 한거다. 만약 리듀서에내에서 몇몇 settings selector를 가져온다면 풀 수 없는 순환 의존 그래프 갖게 된다

![img](https://d33wubrfki0l68.cloudfront.net/c9a514b782ebee33722af7b2d430dedcbca6856c/705b1/static/reduxcirculardependency-3dcf9ac5177dc7c0994f664a9ee0a219.svg)

## Globalizing Selectors

셀렉터를 global 하게 만드는 방법은 동일한 이름을 가진 함수 set을 export하면 된다. 이것의 유일한 목적은 state selection과 local selector 호출이다.

```js
// store/navigation/selectors.js
export function getActiveScene(state) {
  return state.activeScene;
}

// store/selectors.js

/**
 * Accumulates all the different selectors
 */
import * as navigationSelectors from './navigation/selectors';
import * as notificationSelectors from './notifications/selectors';
import * as settingsSelectors from './settings/selectors';

const selectors = {};
Object.keys(navigationSelectors).forEach(
  funcName =>
    (selectors[funcName] = state =>
      navigationSelectors[funcName](state.navigation))
);

Object.keys(notificationSelectors).forEach(
  funcName =>
    (selectors[funcName] = state =>
      notificationSelectors[funcName](state.notifications))
);

Object.keys(settingsSelectors).forEach(
  funcName =>
    (selectors[funcName] = state => settingsSelectors[funcName](state.settings))
);

// We want to be able to import like this: "import { name1, name2 } from 'selectors'"
// Below code behaves like "export {...selectors}" because of this relationship:
// var module = {}
// var exports = module.exports = {}
module.exports = selectors;
```

```js
// someComponent.js
import { getActiveScene } from '../store/selectors';
const mapStateToProps = state => ({
  activeScene: getActiveScene(state),
});
```

## Summary

원래는 셀렉터를 하나만 작성했다. 예를 들어서.. bookReducer가 있고 books를 가져와야한다면..

```js
function getBooks(state) {
  return state.books.datas;
}

function getBooksFetchStatus(state) {
  return state.books.status;
}
```

- 테스트할 때 전체 state를 만들어서 넣어줘야한다.

```js
// books/localSelector.js
function getBooks(state) {
  return state.datas;
}

function getBooksFetchStatus(state) {
  return state.status;
}

// redux/globalSelector.js
import * as fromBooks from '../books/localSelector';

function getBooks(state) {
  return fromBooks.getBooks(state.books);
}

function getBooksFetchStatus(state) {
  return fromBooks.getBooksFetchStatus(state.books);
}
```

- 테스트할 때 해당 state의 부분만 인자로 전달하여 테스트한다.
- 즉, 테스트 뿐만 아니라 실제 서비스 코드에서도 다른 root state 부분이 접근하지 못하도록 하여 sub-reducer나 selector가 올바르게 디커플링 될 수 있다.
