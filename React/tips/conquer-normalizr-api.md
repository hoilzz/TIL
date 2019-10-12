# normalize API 매번 볼때마다 헷갈려

서버에서 보통 여러개의 데이터를 배열 안에 객체 데이터들을 담아서 보내준다. 예를 들어, 블로그 포스팅 데이터를 받아온다고 하자.

```json
[
  {
    "id": "1",
    "title": "My first post!",
    "author": {
      "id": "123",
      "name": "Paul"
    },
    "comments": [
      {
        "id": "249",
        "content": "Nice post!",
        "commenter": {
          "id": "245",
          "name": "Jane"
        }
      },
      {
        "id": "250",
        "content": "Thanks!",
        "commenter": {
          "id": "123",
          "name": "Paul"
        }
      }
    ]
  },
  {
    "id": "2",
    "title": "This other post",
    "author": {
      "id": "123",
      "name": "Paul"
    },
    "comments": [
      {
        "id": "251",
        "content": "Your other post was nicer",
        "commenter": {
          "id": "245",
          "name": "Jane"
        }
      },
      {
        "id": "252",
        "content": "I am a spammer!",
        "commenter": {
          "id": "246",
          "name": "Spambot5000"
        }
      }
    ]
  }
]
```

포스팅 정보, 작성자 정보, 코멘트 정보로 구성되어있다.

이 때, 단순히 조회의 성격이 강하다면 정규화 작업은 불필요하다.

하지만 위 데이터 구조에서 코멘트를 업데이트를 한다고 해보자.
중첩된 데이터구조에서는 리듀서 로직도 중첩될거다. 해당 포스팅들에 대해 반복문을 돌면서, 포스팅의 안의 comments를 또 반복문돌아야한다. 이 방법은 느리고 코드도 더러워지기 쉽다.

또, 코멘트를 여러개 작성한 작성자가 이름을 바꾼다고 해보자. (물론 닉네임 수정은 보통 포스팅 페이지에서 하지 않지만..) SPA에서 수정된 닉네임을 API 요청 후, comments에 있는 닉네임을 수정해야한다. 이 때, 유저 정보가 여러곳(posting객체의 author, comment 객체에서 commenter)에서 관리 되고 있기때문에, 전부 탐색하며 변경해줘야 한다.

이러한 단점들 때문에, 정규화를 한번 해놓으면 위 과정을 거치지 않고 쉽고 빠르고 간단하게 데이터를 관리할 수 있다. 정규화가 뭔지 모르겠다면 아래 정규화 결과를 보자.

```json
// output
{
  "entities": {
    "users": {
      "123": {
        "id": "123",
        "name": "Paul",
        "posts": ["1", "2"],
        "comments": ["250"]
      },
      "245": {
        "id": "245",
        "name": "Jane",
        "comments": ["249", "251"],
        "posts": []
      },
      "246": {
        "id": "246",
        "name": "Spambot5000",
        "comments": ["252"]
      }
    },
    "comments": {
      "249": {
        "id": "249",
        "content": "Nice post!",
        "commenter": "245",
        "post": "1"
      },
      "250": {
        "id": "250",
        "content": "Thanks!",
        "commenter": "123",
        "post": "1"
      },
      "251": {
        "id": "251",
        "content": "Your other post was nicer",
        "commenter": "245",
        "post": "2"
      },
      "252": {
        "id": "252",
        "content": "I am a spammer!",
        "commenter": "246",
        "post": "2"
      }
    },
    "posts": {
      "1": {
        "id": "1",
        "title": "My first post!",
        "author": "123",
        "comments": ["249", "250"]
      },
      "2": {
        "id": "2",
        "title": "This other post",
        "author": "123",
        "comments": ["251", "252"]
      }
    }
  },
  "result": ["1", "2"]
}
```

## 정규화된 상태 설계하기

정규화는

- 각 타입은 자신의 "테이블"을 가진다.
- 각 "data table"은 객체로 개별 아이템을 저장해야한다. 이 객체의 key는 item의 ID고 값은 아이템 객체다.
- ID의 배열은 순서를 저장하는데 이용된다.

이렇게 하면 좋은점은

- 각 아이템은 한곳에서만 정의되기 때문에, 아이템이 업데이트 되면 여러 장소에서 변경하지 않아도 된다.
- 리듀서 로직은 중첩된 뎁스를 처리하지 않아도 된다. 로직이 간단해진다.
- 주어진 아이템을 가져오거나 업데이트 할 때 간단하고 일관성 있다. 아이템의 타입과 ID만으로, 해당 아이템을 찾기 위해 반복문을 돌지 않고 데이터에 바로 접근 가능하다.

이제 각설하고, normalizr API 사용 방법을 간단히 알아보자.

## API

```js
import { normalize, schema } from 'normalizr';

const myData = { users: [{ id: 1 }, { id: 2 }] };

const user = new schema.Entity('users');
const mySchema = { users: [user] };

const normalizedData = normalize(myData, mySchema);
```

```json
//output
{
  "result": { "users": [1, 2] },
  "entities": {
    "users": {
      "1": { "id": 1 },
      "2": { "id": 2 }
    }
  }
}
```

```js
const user = new schema.Entity('users');
```

Entity의 첫번째 인자는 key인데, 필수값이다. 정규화되고 나서 결과값에서 작성된 key에 정규화된 결과값이 있다. 위에서 보면 entities.users에 정규화된 결과값이 있다는 것을 알 수 있다.

하지만 key에 id값이 들어간걸 볼 수 있는데 어떻게 알까?

normalizr는 데이터에 id 프로퍼티를 가진다면 unique하다고 판단하여 key로 사용한다.

그리고 result는 뭘까?

result는 순서를 유지하기 위해, 기존 데이터의 배열 순서대로 id를 저장한다.

아래에서 자세한 API 번역을 보자.

#### schema.Entity(key, definition = {}, options = {})

- `key`: **require**, 결과값에서 해당 키 아래에 모든 엔티티가 정규화된 응답값을 가진다.
- `definition` : 이 entity 내부에서 발견된 중첩된 엔티티 정의. default 값은 빈 객체다. 정규화된 엔티티의 출력값에 모든 값이 카피될 것이다.
- `options`:
  - `idAttribute` : 해당 entity 타입의 unique ID, `key`나 unique id에 해당하는 `value`를 리턴하는 함수. (기본 값은 'id'다.) 함수에서는 다음 인자를 받는다ㅣ.
    - `value` : entity의 input value
    - `parent` : input 배열의 부모 객체
    - `key` : 부모 객체에서 input 배열이 나타나는
  - mergeStrategy(entityA, entityB): 동일 `id`를 갖는 2개의 entity를 머지할 떄 이용하는 전략 함수. 기본적으로 더 최근의 값을 이전값에 머지한다.
  - processStrategy(value, parent, key): entity 전처리할 때 사용하는 전략 함수. 정규화 하기 전에 데이터를 추가하거나 완전히 entity를 변경하기 위한 메서드로 이용한다. 디폴트로 input entity의 shallow copy를 리턴한다.

**instance method**

- define(definition): 사용할 때, 전달된 `definition`은 `Entity` 생성자에 전달된 original definition으로 머지된다. 이 메서드는 스키마에서 순환 참조를 생성할 때 유용하다.

**instance attributes**

- key: 생성자에 제공된 키를 리턴한다.
- idAttribute: 생성자에 제공된 idAttribute를 리턴한다.

```js
const data = {
  id_str: '123',
  url: 'https://twitter.com',
  user: { id_str: '456', name: 'Jimmy' }
};

// 서버에서 id로 attribute를 주지 않는 경우 3번째 인자와 같이 id를 알려줄 수 있다.
// 위 데이터에서 user 데이터가 중첩되어있기 때문에, entity type을 하나 더 선언해준다.
const user = new schema.Entity('users', {}, { idAttribute: 'id_str' });

// 한 데이터에서 2가지의 엔티티를 정규화하기 위해 선언한다.
const tweet = new schema.Entity(
  'tweets',
  // userEntity가 중첩되어있다고 알려준다. 이렇게 하면 twwet, user 엔티티가 최상위 레벨로 정규화된다.
  { user: user },
  {
    idAttribute: 'id_str',
    // Apply everything from entityB over entityA, except for "favorites"
    mergeStrategy: (entityA, entityB) => ({
      ...entityA,
      ...entityB,
      favorites: entityA.favorites
    })
    // Remove the URL field from the entity
    // processStrategy: entity => omit(entity, 'url')
  }
);

const normalizedData = normalize(data, tweet);
```

output

```js
{
  entities: {
    tweets: { '123': { id_str: '123', user: '456', url: "https://twitter.com" } },
    users: { '456': { id_str: '456', name: 'Jimmy' } }
  },
  result: '123'
}
```

요기까지는 튜토링얼이다. 사실 여러 객체를 담고 있는 배열 데이터를 정규화 할일이 많다. 아래에서 어떻게 정규화하는지 알아보자.

#### Array(definition, schemaAttribute)

**스키마 배열** 을 정규화 하기 위해 스키마 배열을 생성한다. 이 배열은 먼저 특정 엔티티를 선언해주고, Array메서드의 definition에 엔티티를 전달해면 된다.

> Note: [ mySchema ] 문법을 통해 동일한 동작을 수행할 수 있다.

- `definition`: **required** 이 배열에 포함된 단일 스키마 or 스키마를 속성값에 매핑
- `schemaAttribute`: **optional** (만약 `definition`이 단일 스키마가 아니라면 **required**) 정규화 할 때 스키마가 뭔지 정의하는 attribute. 문자열이나 함수가 될 수 있다. 만약 함수가 주어진다면, 다음 인자를 받는다.
  - `value`: entity의 input value
  - `parent`: input array의 부모 오브젝트
  - `key`: 부모 오브젝트의 input array를 가리키는 key값

**instance methods**

- `define(definition)`: 사용될 떄, 전달된 `definition`은 `Array` 생성자에 원래 정의와 머지된다. 이 메서드는 스키망에서 순환 참조를 생성할 때 유용하다.

```js
import { schema, normalize } from 'normalizr';

const data = [{ id: '123', name: 'Jim' }, { id: '456', name: 'Jane' }];
const userSchema = new schema.Entity('users');

//
const userListSchema = new schema.Array(userSchema);
// or use shorthand syntax:
const userListSchema = [userSchema];

const normalizedData = normalize(data, userListSchema);
```

**output**

```js
{
  entities: {
    users: {
      '123': { id: '123', name: 'Jim' },
      '456': { id: '456', name: 'Jane' }
    }
  },
  result: [ '123', '456' ]
}
```

만약 input data가 entity의 1개 이상의 타입의 배열이라면, schema mapping을 정의하는 것은 필수다.

> Note: 만약 데이터가 매핑을 제공하지 않는 객체를 반환하면, 결과값에 원래 객체가 반환되고 entity는 만들어지지 않는다.

예를 들어,

```js
const data = [{ id: 1, type: 'admin' }, { id: 2, type: 'user' }];

// 데이터의 최상위 레벨에 2가지의 스키마가 있기 때문에 2개의 schema 선언.
const userSchema = new schema.Entity('users');
const adminSchema = new schema.Entity('admins');

const myArray = new schema.Array(
  {
    admins: adminSchema,
    users: userSchema
  },
  (input, parent, key) => `${input.type}s`
);

const normalizedData = normalize(data, myArray);
```

```js
{
  entities: {
    admins: { '1': { id: 1, type: 'admin' } },
    users: { '2': { id: 2, type: 'user' } }
  },
  result: [
    { id: 1, schema: 'admins' },
    { id: 2, schema: 'users' }
  ]
}
```

## CheatSheat

[normalizr examples](https://github.com/paularmstrong/normalizr/tree/master/examples) 얘를 참고하면 되지만 주석을 달고 싶어서 재작성해본다.

1. 블로그 포스팅 데이터 정규화하기

[input.json](https://github.com/paularmstrong/normalizr/blob/master/examples/relationships/input.json)

[output.json](https://github.com/paularmstrong/normalizr/blob/master/examples/relationships/output.json)

```js
import { schema } from '../../src';

// user 데이터는 최상위 post 데이터에서 author로, 중첩된 comment데이터에서는 commenter로 선언되어있다. 각 엔티티 유형에 따라 구분하기 위해, 아래와 같이 전처리 함수를 작성.
const userProcessStrategy = (value, parent, key) => {
  switch (key) {
    case 'author':
      // 전처리시 key가 author로 작성된 경우 posts 배열에 post id를 추가한다.
      // 배열인 이유는 유저가 여러개의 포스트를 작성할 수 있기 때문이다.
      return { ...value, posts: [parent.id] };
    case 'commenter':
      return { ...value, comments: [parent.id] };
    default:
      return { ...value };
  }
};

const userMergeStrategy = (entityA, entityB) => {
  return {
    ...entityA,
    ...entityB,
    posts: [...(entityA.posts || []), ...(entityB.posts || [])],
    comments: [...(entityA.comments || []), ...(entityB.comments || [])]
  };
};

// user entity 선언
const user = new schema.Entity(
  'users',
  // 중첩 데이터 없음.
  {},
  {
    mergeStrategy: userMergeStrategy,
    processStrategy: userProcessStrategy
  }
);

const comment = new schema.Entity(
  'comments',
  // commenter 프로퍼티에 user entity type 중첩되어있음
  {
    commenter: user
  },
  {
    // 전처리시, parent인 post 데이터의 id를 가진다.
    processStrategy: (value, parent, key) => {
      return { ...value, post: parent.id };
    }
  }
);

const post = new schema.Entity('posts', {
  author: user,
  comments: [comment]
});

export default [post];
```
