# Action

## 비동기 액션 생성자

미들웨어는 모든 액션을 보내기 전에 임의의 로직을 삽입할 수 있게 해준다. 비동기 액션은 미들웨어의 대표적인 예시다.

미들웨어 없이 `dispatch`가 평범한 객체만을 받을 수 있다. 그래서 Ajax 호출을 컴포넌트 안에서 해야만 한다.

`actionCreator.js`

```javascript
export function loadPostsSuccess(userId, response) {
    return {
        type: 'LOAD_POSTS_SUCCESS',
        userId,
        response
    };
}

export function loadPostsFailure(userId, error) {
    return {
        type: 'LOAD_POSTS_FAILURE',
        userId,
        error
    };
}

export function loadPostsRequest(userId) {
    return {
        type: 'LOAD_POSTS_REQUEST',
        userId
    }
}
```

`UserInfo.js`

```javascript
import { Component } from 'react';
import { connect } from 'react-redux';
import { loadPostsRequest, loadPostsSuccess, loadPostsFailure } from './actionCreators';

class Posts extends Component {
  loadData(userId) {
    // Injected into props by React Redux `connect()` call:
    let { dispatch, posts } = this.props;

    if (posts[userId]) {
      // There is cached data! Don't do anything.
      return;
    }

    // Reducer can react to this action by setting
    // `isFetching` and thus letting us show a spinner.
    dispatch(loadPostsRequest(userId));

    // Reducer can react to these actions by filling the `users`.
    fetch(`http://myapi.com/users/${userId}/posts`).then(
      response => dispatch(loadPostsSuccess(userId, response)),
      error => dispatch(loadPostsFailure(userId, error))
    );
  }

  componentDidMount() {
    this.loadData(this.props.userId);
  }

  componentWillReceiveProps(nextProps) {
    if (nextProps.userId !== this.props.userId) {
      this.loadData(nextProps.userId);
    }
  }

  render() {
    if (this.props.isFetching) {
      return <p>Loading...</p>;
    }

    let posts = this.props.posts.map(post =>
      <Post post={post} key={post.id} />
    );

    return <div>{posts}</div>;
  }
}

export default connect(state => ({
  posts: state.posts
}))(Posts);
```

서로 다른 컴포넌트들이 같은 API 엔드포인트에서 데이터를 요청하기 때문에 *반복*이 생기게 된다. 또한 로직의 일부(캐시된 데이터가 있으면 일찍 종료하기)를 여러 컴포넌트에서 재사용하기를 원한다.

**미들웨어는 좀 더 표현력 있는 비동기 액션 생성자를 작성하게 해준다.** 미들웨어는 평범한 객체 외의 다른 것들을 보낼 수 있게 해주고 그 값을 변환해준다. **예를 들어 미들웨어는 약속이 보내지면 "잡아서" 요청과 성공/실패 액션으로 바꿔줄 수 있다.**

미들웨어의 간단한 예는 `redux-thunk`다. **"썽크" 미들웨어는 액션 생성자를 함수를 반환하는 함수인 "썽크"로 작성할 수 있게 해준다.** (이는 제어를 역전한다.) 즉, `dispatch`를 인자로 받기 떄문에 액션을 여러번 보내는 액션 생산자를 작성할 수 있다.

위 코드를 redux-thunk를 리용하여 재작성해보자.

`actionCreators.js`

```javascript
export function loadPosts(userId) {
  // Interpreted by the thunk middleware:
  return function (dispatch, getState) {
    let { posts } = getState();
    if (posts[userId]) {
      // There is cached data! Don't do anything.
      return;
    }

    dispatch({
      type: 'LOAD_POSTS_REQUEST',
      userId
    });

    // Dispatch vanilla actions asynchronously
    fetch(`http://myapi.com/users/${userId}/posts`).then(
      response => dispatch({
        type: 'LOAD_POSTS_SUCCESS',
        userId,
        response
      }),
      error => dispatch({
        type: 'LOAD_POSTS_FAILURE',
        userId,
        error
      })
    );
  }
}
```

`UserInfo.js`

```javascript
import { Component } from 'react';
import { connect } from 'react-redux';
import { loadPosts } from './actionCreators';

class Posts extends Component {
  componentDidMount() {
    this.props.dispatch(loadPosts(this.props.userId));
  }

  componentWillReceiveProps(nextProps) {
    if (nextProps.userId !== this.props.userId) {
      this.props.dispatch(loadPosts(nextProps.userId));
    }
  }

  render() {
    if (this.props.isFetching) {
      return <p>Loading...</p>;
    }

    let posts = this.props.posts.map(post =>
      <Post post={post} key={post.id} />
    );

    return <div>{posts}</div>;
  }
}

export default connect(state => ({
  posts: state.posts
}))(Posts);
```

코드가 훨씬 줄었다. "Smart" `loadPosts` 액션 생성자 대신 `loadPostsSuccess`와 같은 "평범한" 액션 생성자를 사용할 수 있다.





미들웨어 직접 작성할 수 있다. 비동기 액션 생산자를 아래 처럼 하는 대신에:

```javascript
export function loadPosts(userId) {
    return {
        types: ['LOAD_POSTS_REQUEST', 'LOAD_POSTS_SUCCESS', 'LOAD_POSTS_FAILURE'],
        shouldCallAPI: (state) => !state.users[userId],
        callAPI: () => fetch(`http://myapi.com/users/${userId}/posts`),
        payload: {userId}
    }
}
```

이런 액션들을 변환해주는 미들웨어를 만들 수 있다.

```javascript
function callAPIMiddleware({ dispatch, getState }) {
  return function (next) {
    return function (action) {
      const {
          types,
          callAPI,
          shouldCallAPI = () => true,
          payload = {}
      }
    }
  }
}
```