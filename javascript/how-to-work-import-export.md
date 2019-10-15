# ES6 In Depth

[ES6 In Depth](http://hacks.mozilla.or.kr/2016/05/es6-in-depth-modules/)
[JS Module System](https://velog.io/@doondoony/JavaScript-Module-System)

ES6 이전에는 브라우저의 표준 모듈 시스템이 없었다.

그래서 필요한 모듈을 CDN에 배포하여 `<script src="...">` 로 불러왔다.

외부 라이브러리는(ES6 이전이니까.. jQuery같은거..)는 cdnjs, unpkg에 존재하는 주소를 통하여 로드 했다. 혹은 빌드된 파일을 직접 다운로드하여 서비스 코드와 함께 배포 했다.

이제는 ES6에서 정식으로 모듈 시스템이 도입되었다.

`import`와 `export`다.

## basic

ES6 모듈은 JS 코드를 담고있는 일반 스크립트 파일처럼 보인다.
다른 점은

1. strict 모드가 자동 설정
2. import와 export문 사용 가능.

```js
// kittydar.js - 이미지에 존재하는 모든 고양이들의 위치 찾기.
// (Heather Arthur 가 정말로 이 라이브러리를 구현했음)
// (하지만 그녀는 모듈을 사용하지 않았음, 2013년에 작성했기 때문임)

export function detectCats(canvas, options) {
  var kittydar = new Kittydar(options);
  return kittydar.detectCats(canvas);
}

export class Kittydar {
  ... several methods doing image processing ...
}

// 이 함수는 export 되지 않음 (외부에 노출되지 않음).
function resizeCanvas() {
  ...
}
...
```

export는 top-level에 작성 가능하다.

해당 코드가 스크립트가 아닌 **모듈** 이기 때문에 모듈 스코프를 갖는다.
즉, IIFE나 callback에 넣어서 독립된 스코프를 만들 필요가 없다.
모듈의 공개 API만 export 키워드를 선언하자.

import 선언이 있는 모듈을 실행시키면, import 하는 모듈들이 먼저 로드된다.
그래서 모듈들 사이의 의존성 그래프 상에서 가장 깊이 있는 모듈부터 실행된다.
**이때, 이미 실행된 모듈은 건너뛰기 때문에 사이클이 발생하지 않는다.**

## default export

위 표준은 cjs, amd 모듈과 함께 사용되도록 설계되어있다.
만약 Node 프로젝트가 있다면 ES6에서 lodash의 개별 함수를 import 할 수 있다.

```js
// 개별함수만 필요하다면..
// import {each, map} from "lodash";

import _ from 'lodash';
// import {default as _} from 'lodash' 와 같은말.

each([3, 2, 1], x => console.log(x));
```

`import {defaulas as _} from 'lodash'` 이 문구는 CJS모듈도 가져올 수 있도록 설계되어있다.

## 모듈 객체

```js
import * as cows from 'cows';
```

import \* 을 실행하면, 모듈 네임스페이스 객체가 import 된다.
모듈 네임스페이스 객체의 속성은 해당 모듈이 export 하는 항목들이다.

## 모듈 모으기
