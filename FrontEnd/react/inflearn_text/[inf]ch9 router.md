# Router : URL에 따라서 다른 결과물 보여주자

Router는 사용자가 요청한 URL의 서브디렉토리에 따라 결과물을 렌더링
- Apache nginx등의 웹서버처럼 각 페이지마다 다른 디렉토리 및 파일을 사용하는 것과 달리
- 라우터를 사용하게 되면 **처음부터 웹앱에서 사용 할 모든 컴포넌트를 먼저 불러온다**.
- **페이지를 이동할 때마다 그때 그때 페이지를 처음부터 로딩하지 않고 필요한 컴포넌트만 다시 렌더링** (즉 Header 같은 부분처럼 변동이 없는 부분들은 유지되어있다는 의미)

## 1 React Router 설치하기

`<Link>`는 Router에 내장된 컴포넌트 중 하나다.
- github에서 렌더링 되는 부분 코드를 살펴보면 다음과 같다.
  - `return <a {...props} onClick={this.handleClick}/>`
  - 결국 링크를 해주는 `a태그`와 같지만 다른 점은 클릭했을 때 `<a href=".."` 이 태그는 페이지 자체를 리로딩하지만 `<Link>`는 `this.props.children` 부분만 리로딩한다.

- `this.props.children`은 따로 설정하는 props가 아닌, 모든 컴포넌트가 가진 컴포넌트로써, 컴포넌트를 사용할 때 `<Component><...></Component>` bold(...)로 표시된 부분에 들어가는 부분이 this.props.children으로 자동으로 설정된다.

## 4 ReactDOM 렌더링 및 Router 설정하기

> 지금까지 ReactDOM을 사용해 컴포넌트를 렌더링시, 바로 <App ../> 형태로 해왔지만
> 라우터 사용시 <Router...> 형태를 사용.
> 여기선 App Component가 Router의 props로 있는 셈
> browserHistory를 사용하여, 뒤로가기를 해도 새로 리로딩되지 않고 필요한부분만 리렌더링되게끔 해준다
> IndexRoute의 Index가 의미하듯, 라우터의 첫 페이지를 정의해준다.




## Summary
- 라우터 사용시 처음부터 웹앱에서 사용 할 모든 컴포넌트를 먼저 불러온다
- 페이지를 이동할 때마다 로딩하지 않고 필요한 컴포넌트를 다시 렌더링
- `<Link>`는 Router에 내장된 함수
  - a 태그는 페이지 자체를 리로딩
  - `<Link>`는 `this.props.children` 부분만 리로딩
- `this.props.children`은 따로 설정하는 props 아니다
  - 모든 컴포넌트가 가진 컴포넌트
- `<Component>...</Component>` bold(...)로 표시된 부분에 들어갈 부분이 this.props.children으로 자동 설정
- `ReactDOM` 렌더링 `Router` 설정

```javascript
ReactDOM.render(<Router history = {browserHistory}>
      <Route path = "/" component = {App}>
         <IndexRoute component = {Home} />
         <Route path = "home" component = {Home} />
         <Route path = "about" component = {About} />
         <Route path = "articles" component = {Articles} />
      </Route>
   </Router>, document.getElementById('root'));
```

  - `App` 컴포넌트가 Router의 props로 있는셈
  - `Route`는 클라 상에서 페이지를 라우팅할 주소
  - `browerHistory`는 뒤로가기를 해도 페이지가 새로 리로딩되지 않고 필요한 부분만 리렌더링하게끔 해준다
  - `IndexRoute`는 라우터의 첫페이지
