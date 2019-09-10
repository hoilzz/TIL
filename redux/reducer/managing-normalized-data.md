# Managing Normalized Data

[Managing Normalized Data](https://redux.js.org/recipes/structuring-reducers/updating-normalized-data)

Normalizr는 중첩된 응답 데이터를 normalized 모양으로 변형하는데 사용된다. 그러나 그것은 normalized 데이터를 업데이트 하는 문제를 해결하지 못한다. 이에 대한 해결 방법은 많다. Post에 새로운 코멘트를 추가하는 예제를 보자.

## 표준 접근

### Simple Merging

기존 상태에 action에 담긴 컨텐츠를 머지하는 것이다. **이 경우에 shallow copy가 아닌, deep recursive merge를 해야한다.** Lodash `merge` 함수가 이것을 처리해줄거다.

```js
function commentsById(state = {}, action) {
  switch (action.type) {
    default: {
      if (action.entities && action.entities.comments) {
        return merge({}, state, action.entities.comments.byId);
      }
      return state;
    }
  }
}
```

reducer 측면에서 최소 양의 작업을 필요로한다. 하지만 dispatch 되기 전에 데이터를 state shape에 맞추는 작업을 하기 위해 action creator가 잠재적으로 꽤 많은 양의 작업을 필요로한다. 이것은 아이템을 삭제하는 작업을 처리할 수 없다.

## Reducer Composition 자르기

만약 슬라이스 리듀서의 중첩된 트리를 가진다면, 각 슬라이스 리듀서는 action에 응답하는 방식을 알아야한다. 우리는 action에서 관련 데이터를 포함해야한다. comment의 ID를 가진 Post 객체를 업데이트 하고, ID를 키로 이용하여 새로운 Comment 객체를 생성하고 Comment IDs 배열에 해당 코멘트 ID를 포함해야한다.

```js
// actions.js
function addComment(postId, commentText) {
  // Generate a unique ID for this comment
  const commentId = generateId('comment')

  return {
    type: 'ADD_COMMENT',
    payload: {
      postId,
      commentId,
      commentText
    }
  }
}

// reducers/posts.js
function addComment(state, action) {
  const { payload } = action
  const { postId, commentId } = payload

  // Look up the correct post, to simplify the rest of the code
  const post = state[postId]

  return {
    ...state,
    // Update our Post object with a new "comments" array
    [postId]: {
      ...post,
      // comments 배열에 새로 생성된 코멘트의 commentId를 추가.
      comments: post.comments.concat(commentId)
    }
  }
}

unction postsById(state = {}, action) {
  switch (action.type) {
    case 'ADD_COMMENT':
      return addComment(state, action)
    default:
      return state
  }
}

const postsReducer = combineReducers({
  byId: postsById,
  allIds: allPosts
})

// reducers/comments.js
function addCommentEntry(state, action) {
  const { payload } = action
  const { commentId, commentText } = payload

  // Create our new Comment object
  const comment = { id: commentId, text: commentText }

  // Insert the new Comment object into the updated lookup table
  return {
    ...state,
    [commentId]: comment
  }
}

function commentsById(state = {}, action) {
  switch (action.type) {
    case 'ADD_COMMENT':
      return addCommentEntry(state, action)
    default:
      return state
  }
}

function addCommentId(state, action) {
  const { payload } = action
  const { commentId } = payload
  // Just append the new Comment's ID to the list of all IDs
  return state.concat(commentId)
}

function allComments(state = [], action) {
  switch (action.type) {
    case 'ADD_COMMENT':
      return addCommentId(state, action)
    default:
      return state
  }
}

const commentsReducer = combineReducers({
  byId: commentsById,
  allIds: allComments
})
```

이 예제는 약간 길다. 왜냐하면 모든 slice reducer와 case reducer가 서로 어떻게 fit해야 하는지를 보여줘야 하기 때문이다. 관련 위임을 주목하자.

`postsById` slice reducer는 `addComment`에게 해당 동작을 위임했다. 이것은 해당 Post item에 새로운 comment ID를 추가한다. 반면에, `commentById`와 `allComments` 슬라이스 리듀서는 자신의 리듀서를 가진다. 이것은 Comments lookup table과 comment ID 리스트를 업데이트한다.
