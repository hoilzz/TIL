# arrow function in class

클래스에서 arrow function은 오버라이딩 될 수 없다.

기존에 클래스는 method 정의만 가능했다.
즉, 클래스 내부의 constructor와 method 정의로만 해당 클래스의 메서드를 정의할 수 있다.

[https://babeljs.io/docs/en/babel-plugin-proposal-class-properties](https://babeljs.io/docs/en/babel-plugin-proposal-class-properties)

하지만 class-properties-proposal 을 사용하면 4가지 방식의 클래스 프로퍼티를 생성할 수 있다.

```js
class Book {
  instanceProperty = 'bork';
  boundFunction = () => {
    return this.instanceProperty;
  };

  static staticProperty = 'babeliscool';
  static staticFn = function() {
    return Bork.staticProperty;
  };
}
```

이제 내가 헷갈린 오버라이딩 예제를 보자.

```js
class Animal {
  constructor(sound = '??') {
    this.sound = sound;
  }

  setNickname(nickname) {
    this.nickname = nickname;
  }

  arrowNotHerited = () => {
    console.log('in Animal');
  };
}

class Dog extends Animal {
  constructor() {
    super('wal wal');
    this.species = 'mixed';
  }

  setNickName(nickname) {
    this.nickname = 'doggy_' + nickname;
    console.log('overriding fn called');
  }

  arrowNotHerited() {
    console.log('in Dog');
  }
}

const baduk = new Dog('urururur');
baduk.setNickname('baduk'); // overriding fn called
baduk.arrowNotHerited(); // in dog
```

arrowNotHerited 메서드는 오버라이딩 되지 않는다.

transpile을 통해 무슨일이 일어났는지 알아보자.

```js
// after transpile

function _defineProperty(obj, key, value) {
  if (key in obj) {
    Object.defineProperty(obj, key, {
      value: value,
      enumerable: true,
      configurable: true,
      writable: true,
    });
  } else {
    obj[key] = value;
  }
  return obj;
}

var Animal =
  /*#__PURE__*/
  (function() {
    function Animal() {
      var sound =
        arguments.length > 0 && arguments[0] !== undefined
          ? arguments[0]
          : '??';

      _defineProperty(this, 'arrowNotHerited', function() {
        console.log('can not called in child');
      });

      this.sound = sound;
    }

    _createClass(Animal, [
      {
        key: 'setNickname',
        value: function setNickname(nickname) {
          this.nickname = nickname;
        },
      },
    ]);

    return Animal;
  })();
```

> Object.defineProperty
> 객체에 직접 새로운 속성을 정의하거나, 이미 존재하는 속성을 수정한 후 그 객체를 반환.

```js
_defineProperty(this, 'arrowNotHerited', function() {
  console.log('can not called in child');
});
```

- Animal 생성자 함수에서 arrowNotHerited를 직접할당
- this는 생성자 함수 실행시 생성되는 인스턴스
- 즉, prototype 객체에 할당되지 않는다.

```js
function _createClass(Constructor, protoProps, staticProps) {
  if (protoProps) _defineProperties(Constructor.prototype, protoProps);
  if (staticProps) _defineProperties(Constructor, staticProps);
  return Constructor;
}

_createClass(Animal, [
  {
    key: 'setNickname',
    value: function setNickname(nickname) {
      this.nickname = nickname;
    },
  },
]);
```

- setNickname은 contructor.prototype에 할당
- 그러므로, setNickname은 오버라이딩이 잘 동작한다

[위 코드를 바벨에서 트랜스파일한 결과](https://babeljs.io/repl#?babili=false&browsers=&build=&builtIns=false&spec=false&loose=false&code_lz=MYGwhgzhAECCB2BLAtmE0DeAoAkMA9vBAC4BOArsMfqQBQT7nwAm0AvNAOQD83nAlJlw5iAC0QQAdAyasOMlgG4s0VdAC-K6FpwQApsQByiYAGt4YZHtpIzFq4Oxq1I8VNvnLe9tA_29ys6aqjpgpKT4AO6G-MQAEnqkiMR6ctC0gmwAfEI4eIQMIHqSIPgA5rScwGDwvrHQ1SBFrIi1wOIgzAKBapqaWKCQMAAi5dB6AB4pLDAIKGhCqgREZJTUdI64EOQADomVkQuHIN1aqmIS0nvAiHowHJzIiBOpnD3B2qr6Riamhl42X7-TauS5-Lw-TjMcplACeAH1ONAANS-IFeHpLAr4IolcqVfAAN0SSWYrTK0AAZm00M0BFoPlowhForEEkkUswMrlloViqUKpxWtBRmUADTQZlRGLxRLJVLQKxifBdfjvLD9LADArEaAAIzAzHIph88D0kRF-M45AotptpwNRtM0gMxjsAM4juNDsNxskUtZso5qQyiiAA&debug=false&forceAllTransforms=false&shippedProposals=false&circleciRepo=&evaluate=false&fileSize=false&timeTravel=false&sourceType=module&lineWrap=true&presets=es2015%2Cstage-2&prettier=false&targets=&version=7.5.5&externalPlugins=)

class 내부의 화살표 함수 선언시 standard 문법이 없다. 그러므로, class-properties 플러그인을 통해 선언할 수 있다.
이를 이용하여 클래스 내부 화살표 함수 선언시, prototype 객체가 아닌 new 생성자로 생성된 인스턴스에 할당된다.

Animal, Dog 클래스의 예제에서,
new Dog.arrowNotHerited() 호출시, 프로토타입체이닝을 확인하기 전에 instance내의 메서드(arrowNotHerited)를 호출한다.
