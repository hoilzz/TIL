# Thinking in React

리액트는 javascript로 big, fast Web apps을 만들기 위한 최고의 방식이다. 페이스북과 인스타그램에서 잘 스케일링 되어있다. 리액트의 훌륭한 부분 중 하나는 앱을 구축할 때, 앱에 대해 어떻게 생각하느냐는 것이다. 이 문서에서 React를 사용하여 검색 가능한 제품 데이터 테이블을 구축하는 과정을 안내할 것이다.


## Start With A Mock

JSON API를 이미 가지고 있고 디자이너로부터 mock도 받았다고 하자.

## Step 1: UI를 컴포넌트 계층으로 나누기

`자체 컴포넌트`(its own component)가 되어야만 하는 것은 어떻게 알 수 있을까? **새로운 함수 혹은 객체를 생성해야만 하는지를 결정하기 위한 동일한 기법을 사용하자** 그러한 테크닉 중 하나는 `single responsibility principle` 이다. 컴포넌트는 이상적으로 한 가지 일만 해야한다. 만약 역할이 더 커지게 된다면, 더 작은 서브 컴포넌트로 쪼개야 한다.

하지만 자체 컴포넌트가 무엇인지 어떻게 알 수 있을까? 너가 새로운 함수 혹은 객체를 만들어야하는지 결정할 때와 동일한 기법을 사용해라. 그러한 기법 중 하나는 `single responsibility principle`이다. 이것은 컴포넌트는 이상적으로 1가지 일만 해야 한다는 것을 의미한다. 만약 역할이 커지게 된다면, 더 작은 서브 컴포넌트로 분해 해야한다.

user에게 JSON 데이터를 보여줘야 하기 때문에, 너의 모델이 올바르게 빌드 됐는지, 너의 UI(컴포넌트 구조)가 좋게 매핑 됐는지 확인해야 한다. **UI와 데이터 모델이 동일한 *information architecture*를 따르는 경향이 있기 때문이다.** (이것은 UI를 컴포넌트로 분해하는 것은 종종 사소한 작업이다.) **정확히 하나의 데이터 모델을 나타내는 컴포넌트로 분해해야 한다.**

![react ex](https://reactjs.org/static/thinking-in-react-components-eb8bda25806a89ebdc838813bdfa3601-82965.png)

위 예제 사진에서 5개의 컴포넌트를 볼 수 있다. 

1. FilterableProductTable(orange) : 전체 예제를 담고 있다.
1. SearchBar(blue) : 모든 유저 인풋을 받는다.
1. ProductTable(green): 유저 인풋 기반 데이터 콜렉션을 필터링하고 보여준다. // 왜때문에 2가지 역할을 하는가 위에서 1개만 하라면서
1. ProductCategoryRow(turquioise) : 각 카테고리의 헤더를 나타낸다.
1. ProductRow(red): 각 product 마다 row를 보여준다.

`ProductTable`에서 tableHeader(Name과 Price label를 포함하고 있다)가 그 자체 컴포넌트가 아닌 것으로 보인다. 이것은 개취다. 그리고 논쟁도 있다. 예를 들어, `ProductTable`의 부분으로 남겨둘 수 있다. 왜냐하면 Product Table의 역할은 data collection 렌더링의 부분이기 때문이다. 그러나 만약 이 헤더가 복잡해진다면(소팅을 넣는다던가), 그것은 확실히 `ProductTableHeader` component로 만들어져야한다.

위 목업에서 컴포넌트를 정의했다. **계층으로 정리해보자**. 개쉽다. 다른 컴포넌트 안에서 나타나는 컴포넌트는 계층에서 자식으로 보여져야한다. 

- FilterableProductTable
  - SearchBar
  - ProductTable
    - ProductCategoryRow
    - ProductRow


## Step 2: Build A Static Version in React

컴포넌트 계층 구조가 있으니까 구현해보자. 가장 쉬운 방법은 데이터 모델을 가진 버전을 빌드하고 **인터랙션 없이 UI를 렌더링 하는 것이다.** 이러한 프로세스를 분해하는 것이 최고다. 왜냐하면 static version을 빌드하는 것은 많은 타이핑을 필요로 하고 많은 생각을 필요로 하지 않는다. 그리고 인터랙션을 추가하는 것은 많은 생각을 필요로 하고 많은 타이핑이 필요 없다. 

static version을 빌드하는 것은 `props`를 이용하여 데이터를 전달하고 컴포넌트를 재사용하는 컴포넌트를 빌드하는 것이다. `props`는 부모가 자식에게 데이터를 전달하는 방식이다. 만약 state의 개념에 친숙하다면, static version에서 **state를 절대 이용하지 않기**를 추천한다. **`State`는 인터랙션을(시간이 지남에 따라 변경되는 데이터) 위한 예약어다.** 그래서 static version에서 필요 없다

top-down or bottom-up으로 빌드할 수 있다. 계층 구조에서 상위로 컴포넌트를 혹은 하위부터 빌드하는 것으로 시작할 수 있다. **간단한 예제에서는 일반적으로 top-down 진행이 쉽다. 대형 프로젝트는 bottom-up이 더 쉽다.**

이 스텝이 끝나고, 데이터 모델을 렌더링하는 재사용가능한 컴포넌트 라이브러리를 가질 것이다. 컴포넌트는 `render()` 메서드만 가진다. (static version이니까) 계층의 top에 있는 컴포넌트(FilterableProductTable) 데이터 모델을 가져오고 `ReactDOM.render()`를 호출한다. 그리고나서 UI는 업데이트 된다. 복잡한 일이 없기 때문에 UI가 어떻게 업데이트되고 어디에서 변경해야 하는지 쉽게 볼 수 있다. React의 **one-way data flow**는 모든것을 모듈러로 그리고 빠른 상태 유지한다.

## Step 3: UI 상태를 최소로(but complete) 정의하기

**UI를 인터랙티브하게 만들기 위해, 앱에 필요한 가변적인 state의 최소 set을 생각해야 한다.** 핵심은 **DRY: Don't Repeat Yourself**다. 너의 앱이 필요로 하는 상태를 절대적으로 최소 상태로 표현하고 필요할 때(on-demand) 필요한 모든것을 계산하는 것이 좋다. 예를 들어, 만약 TODO list를 만들면, TODO item의 배열을 유지해라. 카운트에 대한 분리된 상태 변수를 유지하지 않기를 추천한다. 대신에, TODO count를 렌더링할 때, 간단히 TODO item 배열의 길이를 사용해라. 

예제 어플리케이션에서 모든 데이터를 생각해보자.

- original products 리스트
- 유저가 입력한 search text
- checkbox 값
- filtered product 리스트

**각각을 살펴보고 어느 것이 state인지 알아보자. 각 데이터에 대해 3가지 질문을 하면 된다.**

1. props을 통해 부모로부터 전달되는가? 만약 그렇다면 state 아니다.
1. 시간이 지남에 따라 불변으로 유지되는가? 그렇다면 state 아니다.
1. 다른 state 혹은 컴포넌트 내 props 기반으로 계산할 수 있는가? 그렇다면 state 아니다. 

product의 original list가 props로 전달될 때, 그것은 state가 아니다. search text와 checkbox는 state처럼 보인다. 왜냐하면 시간이 지남에 따라 그것들은 변하고 어떤 것으로부터 계산 될 수 없기 때문이다. checkbox의 값과 search text와 original list of products를 결합하여 계산되기 때문에 filtered list of products는 state가 아니다. 

그래서 state는

- user가 입력한 search text
- checkbox의 값

이다.

## Step 4: Identify Where Your State Should Live

앞에서 app state의 최소 set을 정의했다. 다음, **어떤 컴포넌트가 state를 소유하고 변경하는지 정의해야 한다.**

Remember: React는 one-way data flow에 대한 모든것이다. 어떤 컴포넌트가 어떤 state를 소유해야하는지 바로 명확하게 알 수 없다. **이것은 종종 뉴비가 이해하기에 가장 어려운 부분이다**. 다음을 따르자.

앱에서 각 state마다:

- state 기반으로 무언가를 렌더링하는 모든 컴포넌트를 확인해라.
- common owner(공통 소유자) component를 찾아라. (계층 구조에서 state를 필요로 하는 모든 컴포넌트 위의 single component)
- common owner(공통 소유자)의 상위에 있는 다른 컴포넌트가 state를 소유해야 한다.
- 만약 어떤 컴포넌트가 state를 가지는 것이 아무 의미가 없다면, state를 가지는 new component를 걍 만들어라 그리고 common owner component위, 계층 구조에서 그것을 추가해라.

이 전략을 우리 앱에 적용해보자.

- ProductTable은 state 기반으로 product list를 filter해야 한다. SearchBar는 search text와 checked state를 dp해야한다.
- common owner component는 FilterableProductTable이다.
- 개념적으로 filter text와 checked value가 FilterableProductTable에 존재하는 것은 개념적으로 의미가 있다. 

이것으로, state가 FilterableProductTable에서 존재하도록 결정했다. 먼저, instance 프로퍼티인 `this.state = {filterText: '', inStockOnly: false}`를 FilterableProductTable의 constructor에 추가하여 app의 초기 state에 반영한다. 그러고나서, `filterText`와 `inStockOnly`를 `ProductTable`과 `SearchBar`에 prop으로 전달해라. 이 props를 `ProductTable`에서 row 필터하기 위해, `SearchBar`에서는 form fields의 값을 세팅하기 위해 사용한다.

## Step 5 : 역방향 데이터 흐름 추가하기

`filterText`에 `"ball"`을 세팅하고 앱을 리프레쉬 해보자. data table이 올바르게 업데이트 된 것을 확인할 수 있다. 지금까지 계층 구조 아래로 흐르는 state와 prop의 함수로 올바르게 렌더링하는 앱을 만들었다. 이제 다른 방식으로 흐르는 데이터를 지원해야한다. (: 계층구조에서 깊숙한 form component는 `FilterableProductTable`에서 상태를 업데이트 해야한다.)

React는 data flow를 명시적으로 이해하기 쉽게 만들었다. 하지만 two-way data binding보다 약간 더 타이핑이 필요하다.

만약 타이핑 하거나 박스에 체크한다면, React는 너의 input을 무시할 거다. 이것은 의도된 것이다. FilterableProductTable에서 전달된 state를 동일하게 유지하기 위해 input의 `value` prop을 세팅 했다.

유저가 form을 변경할 때마다 user input에 반영하기 위해 state를 업데이트 했다. components는 자신의 state만 업데이트해야만 하기 때문에, FilterableProductTable 은 SearchBar에게 state가 업데이트되야할 때마다 호출되는 콜백을 전달한다. 콜백을 호출하기 위해 input에 onChange event를 사용할 수 있다. FilterableProductTable에 의해 전달된 callback은 setState를 호출할 거고 앱은 업데이트 될거다.
## Summary

검색 가능한 제품 데이터 테이블 구축 예제를 통해 리액트 방식으로 생각하기 공부해보자.

1. UI를 컴포넌트 계층으로 나누자.
    - single responsibility principle : 나누는 기준은 컴포넌트는 (이상적으로) 한 가지 일만 해야 한다.
        - 역할이 커지면 더 작은 서브 컴포넌트로 나누자.
        - 근데 가끔 1개 이상 역할 할 때가 있다. 개취다. 하지만 그 컴포넌트가 복잡해질 때가 생기면 바로 서브 컴포넌트로 분해하자.

2. React로 Static Version 만들기
    - 인터랙션 없이 UI 만들기
    - `props`만을 이용하여 데이터 전달 및 재사용 가능한 컴포넌트 만들기
    - **이 단계에서는 state 절대 이용하지 않기**
        - state는 interaction을 위한 예약어다.
    - 이 단계에서는 render() 메서드만 가진다.
> NOTE: 간단한 예제는 top-down, 대형 프로젝트는 bottom-up이 쉽다.

3. UI 상태를 최소로 하지만 완벽하게 정의하기
    - 어플리케이션 혹은 해당 컴포넌트에서의 모든 데이터를 생각하자.
        - UI를 interactive하게 만들기 위해, 가변적인 state의 최소 set을 생각하자.
            - 이 때, 핵심은 DRY다.
            - 앱이 필요로 하는 상태를 절대적으로 최소 상태로 표현하고 필요할 때 필요한 모든 것을 계산하자.
            - Ex. TODO list 만들 때, 카운트에 대한 분리된 상태 변수 유지하지 말고, TODO item 배열 길이 사용해라. **핵심은 최소 set이다**

    > 3가지 질문을 통해 state인지 확인하기
    > 1. props를 통해 부모로부터 전달되는가?
    > 1. 시간이 지남에 따라 불변으로 유지되는가?
    > 1. 다른 state 혹은 컴포넌트 내 props 기반으로 계산 가능한가? 
    > 위 질문에 YES가 하나라도 있다면 state 아니다.

4. state가 선언되야 하는 곳 정의하기
    - 어떤 컴포넌트가 state를 **소유하고 변경하는지** 정의해야한다.
    - 뉴비는 다음을 따르자: 앱에서 각 state마다
        - state 기반으로 무언가를 렌더링하는 모든 컴포넌트를 확인해라.
        - common owner component를 찾아라. (계층 구조에서 state를 필요로 하는 모든 컴포넌틔 위의 single component)
        - Either common owner or another component에서 상위에 있는 다른 컴포넌트가 state를 소유한다
        - 만약 어떤 컴포넌트가 state를 가지는 것이 아무 의미가 없다면, state를 가지는 new component를 걍 만들어라. 그리고 그것을 common owner component위에 추가해라.
    - owner component에서 state 선언 및 초기화
    - state를 prop으로 하위 컴포넌트에 전달.

5. 역방향 데이터 흐름 추가하기
    - state가 업데이트 될 때마다 호출되는 콜백도 전달
    - 콜백 호출을 위해 onChange 이벤트를 사용
