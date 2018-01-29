# HOC

1. 컴포넌트를 인자로 받아서 새로운 컴포넌트를 반환하는 것이다.
2. 리액트 컴포넌트 로직을 재활용할 수 있는 기법
3. 리액트에서 공식적으로 제공하는 API가 아닌 **단순 아키텍처**

```javascript
const HOC = ReactComponent => EnhancedReactComponent;
```

EnhancedReactComponent는 

- ReactComponent의 props를 변경하거나
- ReactComponent에 새로운 props를 추가하여 전달하거나
- 아예 새로운 컴포넌트를 return 할 수 있다.

예시를 통해서 알아보자.

```javascript
function withSay(WrappedComponent) {
    return class extends React.Component {
        say() {
            return 'hello';
        }
        render() {
            return (
                <WrappedComponent
                  {...this.props}
                  say={this.say} />
            )
        }
    }
}
```

WithSay 함수는 WrappedComponent를 인자로 받아 **원하는 속성들을 결합해** 새로운 컴포넌트를 반환한다. 이렇게 만들어진 withSay 함수는 아래와 같이 사용 가능하다. 

```javascript
@withSay
class withoutSay extends React.Component {
    render() {
        return (
            <div>
                {this.props.say()}
            </div>
        )
    }
}
```

withoutSay컴포넌트는 say 메서드를 가지고 있지 않다. **컴포넌트를 인자로 받아 입맛에 맞게 바꾼뒤 새로운 컴포넌트로 반환하는 기법을 HOC라고 한다.**

## 주로 언제 쓸까?

- Container 컴포넌트와 Presentational 컴포넌트의 분리 : 비즈니스 로직을 담당하는 container와 뷰를 담당하는 presentational을 분리하여 사용할 때, 컨테이너 컴포넌트를 HOC를 만들어서 사용 가능

- 로딩 중 화면 표시 : SPA에서 화면이 로딩 중일 때, skeleton 화면 보여주고, 로딩 완료시 데이터를 보여줄 때 사용 가능

- 유저 인증 로직 처리 : **컴포넌트 내에서 권한 체크나 로그인 상태 체크 하기보다는** 인증 로직을 HOC로 분리하면 컴포넌트 재사용성도 높일 수 있고, 컴포넌트에서 역할 분리도 쉽게 할 수 있다.

- 에러 메세지 표시 : 컴포넌트 내에서 분기문을 통해 처리할 수도 있지만, **분기문을 HOC로 만들어 처리하면** 컴포넌트를 더욱 깔끔하게 사용 가능.

### Cross Cutting Concerns

![Cross Cutting Concenrs](https://d33ypg4xwx0n86.cloudfront.net/direct?url=https%3A%2F%2Fs3.ap-northeast-2.amazonaws.com%2Fzoyi-ghost%2Fzoyi-kr%2F2017%2F12%2FCCC-1512450546016.png&resize=w1408)

코드 디자인적인 측면에서 공통적으로 발생하지만 쉽게 분리 시키지 못하는 문제를 Cross Cutting Concerns라고 한다. 이 문제는 앱이 커질 수록, 코드는 스파게티가 되고 유지보수 하기 힘들어진다.

HOC와 decorator를 통해 해결해보자.

## 유저 인증 문제를 HOC로 해결

유저 인증 안될 경우 다른 페이지 보여주는 코드다.

```javascript
class TeamChat extends React.Component {
    constructor() {
        super();
        this.state = {
            unAuthenticated: false
        }
    }

    componentWillMount() {
        if (!this.props.user) {
            this.setState({ unAuthenticated: true})
        }
    }

    render() {
        if (this.state.unAuthenticated) {
            return <UnAuthenticatedComponent />
        }
        return <div>I'm TeamChat</div>
    }
}
```

당장 이 컴포넌트는 문제 없다. 하지만 유저 인증이 필요한 컴포넌트가 많아지면 상황이 달라진다. 100개의 컴포넌트에서 위와 같은 방식으로 유저 인증하는데, 유저 인증 하는 로지깅 변경되면 100개의 컴포넌트 모두 유저 인증 코드 바꿔야한다. 

```javascript
function mustToAuthenticated(WrappedComponent) {
    return class extends React.Component {
        constructor() {
            super();
            this.state = {
                unAuthenticated: false
            }
        }
        componentWillMount() {
            if (!this.props.user) {
                this.setState({ unAuthenticated: true})
            }
        }

        render() {
            if (this.state.unAuthenticated) {
                return <UnAuthenticatedComponent />
            }
            return <WrappedComponent {...this.props} />
        }
    }
    
}
```

HOC를 이용해 확장이 용이한 유저 인증 로직을 탄생시켰다. 이제 HOC를 적용해보자.

```javascript
@mustToAUthenticated
class TeamChat extends React.Component {
    render() {
        return <div>I'm chat</div>
    }
}

@mustToAuthenticated
class UserChat extends React.Component {
    render() {
        return <div>I'm userchat</div>
    }
}
```

기존 코드와 비교시 굉장히 간단해졌다. 또한, 

1. 유저 인증 로직이 컴포넌트와 분리되어 자신이 맡은 역할에만 집중 가능.
2. 유저 인증 로직이 변경될 경우 코드 수정될 곳은 한 곳이다.






## HOC 예제 (2)

유저가 메뉴 클릭시 children 컨텐츠를 보여주는 메뉴 컴포넌트를 확장성 있게 만들어보자. 부모 컴포넌트에서 state를 제어하는 대신에 일반적인 HOC를 이용하여 재사용성 및 확장성을 높이자.

<iframe src="https://codesandbox.io/embed/rlz4rrok3n?autoresize=1&hidenavigation=1" style="width:100%; height:500px; border:0; border-radius: 4px; overflow:hidden;" sandbox="allow-modals allow-forms allow-popups allow-scripts allow-same-origin"></iframe>

파일명과 역할을 함께 살펴보자.

`index.js`

- 메인

`MakeToggleable.js`

- 토글가능한 컴포넌트를 반환해주는 HOC
- toggle 상태값 및 함수가 부모에서 반복되는 것 방지
- toggle의 상태값(isShow)가 true일 경우 서브 메뉴 노출

`Menu.js`

- 메뉴 제목 노출
- 클릭 이벤트의 핸들러로 toggle 함수 세팅

## HOC 만들 때 지키면 좋은 규칙

### 네이밍 : HOC를 통해 새로운 prop을 주입 할 때 

Container HOC를 제외하고 HOC를 통해 새로운 prop을 주입할 때 사용하는 규칙은 `with`로 시작한다. (`withNewPropName`식으로 네이밍 하는게 좋음) 예를 들어, `withLoading`, `withAuth` 드응로 주입될 prop명을 적어주자. 이렇게 하면 실제로 HOC가 사용되는 컴포넌트에서 prop을 확인할 때, 이 prop이 어디에서 왔는지 명확히 알 수 있다.

### DisplayName

React Dev Tool에서 디버깅을 위해 [displayName](https://reactjs.org/docs/higher-order-components.html#convention-wrap-the-display-name-for-easy-debugging)을 명시해주자.

가장 일반적인 기법은 `wrapped component`의 display name을 래핑하는 것이다. 그래서 만약 HOC가 `withSubscription`으로 이름이 지어진다면, (wrapped component의 display name은 `CommentList`다.) WithSubScription(CommentList)로 display name을 사용하자. 

```javascript
function withSubscription(WrappedComponent) {
  class WithSubscription extends React.Component {/* ... */}
  WithSubscription.displayName = `WithSubscription(${getDisplayName(WrappedComponent)})`;
  return WithSubscription;
}

function getDisplayName(WrappedComponent) {
  return WrappedComponent.displayName || WrappedComponent.name || 'Component';
}
```

## 마무리

HOC의 단점

1. Component Unit Test 할 때 문제 발생 가능.
2. HOC를 몇 개 중첩시 디버깅 힘들 수 있다.
3. WrappedComponent에 직접 ref를 달 수 없어 우회 방법 사용해야 한다.
4. 비동기 작업과 같이 사용하다 보면 예상치 못한 결과를 만날 수 있다. 

이러한 단점에도 불구하고, 상속을 제공하지 않은 리액트에서 HOC는 많은 문제를 효율적으로 해결해준다. react-redux, redux-form은 HOC를 사용하여 편의 제공해왔다. 