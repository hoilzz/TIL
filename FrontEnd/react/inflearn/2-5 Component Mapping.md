# Component Mapping

배열에 있는 데이터를 표현하기 위해 컴포넌트로 매핑 해보자

다음과 같은 연락처 데이터가 있다.

```javascript
contact: [
	{name:'police', phone:'112'},
	{name:'fire station', phone: '119'},
	{name:'법률 구조 공단', phone:'132' }
]
```

contact라는 컴포넌트의 state로 위와 같은 데이터가 저장되어있다.
위 데이터를 표현하기 위해 일일히 `<div>police:112</div>`다 입력할 수 없다.
반복되는 부분을 다른 컴포넌트를 생성하여 해결해보자.
반복되는 contact를 표현하기 위해 contactInfo 컴포넌트로 표현하자.

이 때, `map` 함수를 활용하여 각 연락처당 하나의 `contactInfo` 컴포넌트를 생성해보자.



먼저 App Component로 Contact 컴포넌트를 렌더링하자.

```javascript
class Contact extends React.Component{
	render(){
		return(
			<div></div>
		)
	}
}

class App extends React.Component{
	render(){
		return(
			<div>
				<Contact/>
			</div>
		)
	}
}

React.DOM('<App/>', document.getElementById('root'));
```

Contact 컴포넌트의 state에 연락처 정보를 초기화하자.

```javascript
class Contact extends React.Component{
	constructor(props){
		super(props);
		this.state = {
			contact:[
				{name:'police', phone:'112'},
				{name:'fire station', phone: '119'},
				{name:'법률 구조 공단', phone:'132'}
			]
		}
	}
	render(){
		return(
			<div></div>
		)
	}
}
```

render 함수에서 각 연락처당 하나의 contactInfo 컴포넌트를 만들어야 한다.
하나의 연락처를 표현하기 위한 contactInfo 컴포넌트를 정의해보자.

```javascript
class ContactInfo extends React.Component{
	render(){
		return(
			<div>{this.props.contact.name} : {this.props.contact.phone}</div>
		)
	}
}
```

render 함수에서 각 연락처당 하나의 contactInfo 컴포넌트를 만들기 위해 map 함수를 활용하는 `mapToComponent`라는 함수를 만들어보자.

```javascript
class Contact extends React.Component{
	constructor(props){
		super(props);
		this.state = {
			contact:[
				{name:'police', phone:'112'},
				{name:'fire station', phone: '119'},
				{name:'법률 구조 공단', phone:'132'}
			]
		}
	}

	render(){
		const mapToComponent = (data) => {
			return data.map( (contact, index) => {
				<ContactInfo 
					contact={contact}
					key={index}/>
			})
		}
		return(
			<div>{mapToComponent(this.state.contact)}</div>
		)
	}
}
```
