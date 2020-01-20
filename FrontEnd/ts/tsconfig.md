# tsconfig

## esModuleInterop

[understanding esModuleInterop](https://stackoverflow.com/questions/56238356/understanding-esmoduleinterop-in-tsconfig-file)

CJS module을 ES6 모듈로 import 할 때 문제 발생한다.
CJS는 (\* as something)으로 import 해야한다.

```js
// node_modules/moment/index.js
exports = moment;
```

```js
// index.ts file in our app
import * as moment from 'moment';
moment(); // not compliant with es6 module spec

// transpiled js (simplified):
const moment = require('moment');
moment();
```

`*`은 `exports` 변수와 어느정도 동일하다. 하지만 es6 module spec을 준수하지 않는다.
스펙에서, star import의 namespace record는 `moment()`와 같이 호출되는 것이 아닌 plain object만 될 수 있다.

**Solution**

`esModuleInterop` 플래그로 CJS 모듈을 `es6` 모듈로 import할 수 있다.

```js
// index.ts file in our app
import moment from 'moment';
moment(); // compliant with es6 module spec

// transpiled js with esModuleInterop (simplified):
const moment = __importDefault(require('moment'));
moment.default();
```

유효한 es6 module spec이 되고 잘 동작한다. moment는 star import의 namespace가 아니기 때문이다. 걍 default import다.

하지만 어케 동작할까?
default import를 했기 때문에, moment 객체의 `default` property를 호출한다.
하지만 exports object에서 default property를 선언한 적이 없다.
`__importDefault` 함수에서 CJS module에게 default property에 exports를 할당한다.

```js
var __importDefault =
  (this && this.__importDefault) ||
  function(mod) {
    return mod && mod.__esModule ? mod : { default: mod };
  };
```

As You can see, we import es6 modules as it is, but CommonJS modules are wrapped into object with default key. This makes possible to import defaults on CommonJS modules.

\_\_importStar does the similar job - it returns untouched esModules, but translate CommonJS modules into modules with default property:
