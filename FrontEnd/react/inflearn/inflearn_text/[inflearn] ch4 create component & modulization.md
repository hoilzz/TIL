# Create Component and modulization

### src/components/App.js

```javascript
import React from 'react';

class App extends React.Component {
    render(){
        return  (
            <div>
                <Header/>
                <Content/>
            </div>
        );
    }
}

export default App;
```
컴포넌트를 만들때는 `React.Component` 클래스를 상속하여 만들자.
`<Header/>`, `<Content/>`는 앞으로 만들 컴포넌트

### src/components/Content.js

```javascript
export default class Content extends...{
  ...
}
```
모듈들을 `export` 했으니 App.js에서 `import` 하자.
