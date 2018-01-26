# Higher-Order Components

...

```javascript
// 이 함수는 component 를 갖는다
function withSubscription(WrappedComponent, selectData) {
    // ... 그리고 다른 컴포넌트를 리턴한다.
    return class extends React.Component {
        constructor(props) {
            super(props);
            this.handleChange = this.handleChange.bind(this);
            this.state = {
                data: selectData(DataSource, props)
            };
        }

        componentDidMount() {
            // subscription 역할한다
            DataSource.addChangeListener(this.handleChange);
        }

        componentWillUnmount() {
            DataSource.removeChangeListener(this.handleChange);
        }
    }

}
```

> componentWillUnmount()
> 컴포넌트가 unmount되고 제거되기 전에 즉시 호출된다. 이 메서드 안에서 timer 초기화, network 요청 취소, `componentDidMount()`에서 생성된 subscription을 clean up 하는 것과 같은 필요한 cleanup을 수행해라.

고차 컴포넌트는 입력 컴포넌트를 수정하지 않으며 상속을 사용하여 동작을 복사하지도 않는다. 오히려 컨테이너 컴포넌트에 원래 컴포넌트를 래핑하여 *조정합니다?* HOC는 사이드 이펙트가 없는 퓨어 함수다.

이게 전부다. 래핑된 컴포넌트는 출력물을 렌더링하는데 사용되는 data, 새로운 prop을 포함한 컨테이너의 모든 props를 받는다. 고차 컴포넌트는 데이터가 사용되는 이유 및 방법과 연관이 없다. wrapped component는 데이터가 어디서 왔는지 연관이 없다.

..

*고차 컴포넌트와 컨테이너 컴포넌트라 불리는 패턴이 유사함을 느낄 수 있다..*