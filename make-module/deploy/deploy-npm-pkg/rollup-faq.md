## peer-dependencies

- dependency: 내가 만든 모듈에서 사용하는 패키지
- peerDependencies : 반대로 내가 만든 모듈이 다른 모듈과 **함꼐** 동작할 수 있는 호환성 표시

예컨대, 내가 만든 모듈이 gulp의 모든 버전이 아니라 1.3버전과만 동작한다면 그 정보를 표시해야 하는데 이 때 사용하는 것이 peerDependencies임

예시로 자세히 보자.

React와 Lodash를 peer(친구) dependency 로 가지는 라이브러리를 만들어보자.
만약 위 설명대로 external로 세팅한다면, rollup 은 all imports를 번들링할 것이다.

```
import answer from 'the-answer';
import _ from 'lodash'
```

external로 다뤄지고 번들링되는 imports들을 미세하게 조정할 수 있다.
예를 들어 `lodash`를 external로 취급하고, `the-answer`는 걍 냅두자.

```typescript
// rollup.config.js
import resolve from "rollup-plugin-node-resolve";

export default {
  input: "src/main.js",
  output: {
    file: "bundle.js",
    format: "cjs"
  },
  plugins: [
    resolve({
      // pass custom options to the resolve plugin
      customResolveOptions: {
        moduleDirectory: "node_modules"
      }
    })
  ],
  // 어떤 모듈이 external로 처리되야 하는지 선언
  external: ["lodash"]
};
```

`lodash`는 external로 취급되고 너의 라이브러리에 번들링 되지 않는다.

`external` 키는 모듈 이름들을 가진 배열 혹은 만약 external로 다뤄진다면 true를 리턴하는 module 이름을 받는 함수를 받는다

## rollup 명령어

```
rollup -c
rollup --config
```

config file명이 없다면 default로 root의 rollup.config.js를 이용하여 빌드

```
rollup -c -w
rollup -c --watch
```

소스 파일이 변경될 때마다 rebuild

## plugins

### rollup-plugin-peer-deps-external

자동으로 rollup 번들에서 peerDependencies를 extrnalize함. 또한 선택적으로 dependencies를 externalize할 수 있음

> external 되면 bundle에 미포함.

## rollup-plugin-babel, rollup-plugin-node-resolve

## babel의 external-helper 옵션

babel은 해당 파일에서 여러번 인라인되지 않기 위해, 필요하다면 생성된 코드의 상단에 위치된 헬퍼 함수를 가진다. (여러개 파일을 갖고 있다면 이슈가될 수 있다. 특히, 브라우저에 그것들을 보낼때)

파일의 상단에 선언하지 말라고 바벨에서 말할 수 있다.
대신에 외부 헬퍼 내부에 포함된 참조값을 가리키도록 할 수 있다.
