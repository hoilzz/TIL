# module resolution

resolver는 절대 경로로 모듈 위치 잡아주는 라이브러리다.
모듈은 다른 모듈의 디펜던시를 필요로 한다.

```js
import foo from "path/to/module";
```

의존성 모듈은 어플리케이션 코드거나 서드파티 라이브러리다.
번들에 포함되야하는 모든 `require/import`문에 대해 resolver가 웹팩이 모듈 코드를 찾도록 도와준다.
웹팩은 모듈을 번들링하는 동안 file path를 resolve하기 위해 [enhanced-resolve](https://github.com/webpack/enhanced-resolve)를 사용한다.

## Resolving rules in webpack

enhanced-resolve를 이용하여, 웹팩은 file path의 종류를 3가지로 resolve한다.

### 1. Absolute Paths

```js
import '/home/me/file';

import 'C:\\Users\\me\\file';
```

이미 절대경로로 작성되서 resolution 불필요.

### 2. Relative paths

```js
import '../src/file1'
```

import가 발생한 리소스 경로는 context directory로 간주한다.
상대 경로는 모듈의 절대 경로로 만들기 위해 context path를 결합한다.

### 3. Module Paths

```js
import 'module'
import 'module/lib/file'
```

모듈은 `resolve.modules`에 명시된 모든 디렉토리 내부에서 검색된다.
`resolve.alias`를 이용하여 alias로 만든 대체 path는 original module path로 교체한다.

위 rule에 따라 path가 resolve되면, resolver는 path가 file을 가리키는지, directory를 가리키는지 확인한다.

- 만약 path가 file extension이면, 파일을 바로 번들링
- 그렇지 않다면, file extension은 `resolve.extensions` option을 이용하여 resolve한다.
  - 이것은 resolver에게 extensions가 허용된 얘만 resolve해 라고 말하는 거다.

만약 path가 folder라면, 올바른 file을 찾기 위해 다음 스텝 밟음

- ...

## summary

여튼 resolve 옵션은

- import/require 문의 경로를 절대경로로 잡음.
  - 이 때 module path일 경우,
    - resolve.modules에 명시된 모든 디렉토리 내부에서 검색됨.
    - 다 검색이 아닌 extension만 검색.
