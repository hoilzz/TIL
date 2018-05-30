# TDD VS BDD

## TDD

1. 개발자가 테스트 작성
2. 테스트 돌리면 무조건 실패. (왜냐하면 피처 구현된적 없으니까)
3. 개발자는 실제로 코드상에서 테스트를 구현한다.
4. 만약 개발자가 코드를 잘 작성한다면, 다음 단계에서 테스트가 통과하는 걸 볼 수 있다.
5. 개발자는 코드 리팩토링, 주석 추가 하고 정리할 수 있다. 왜냐면 개발자는 새로운 코드가 뭔가를 break하고, 테스트는 실패해서 얼럿으로 될 것이다.

```javascript
var assert = require('assert'),
    factorial = require('../index');

suite('Test', function (){
    setup(function (){
        // Create any objects that we might need
    });

    suite('#factorial()', function (){
        test('equals 1 for sets of zero length', function (){
            assert.equal(1, factorial(0));
        });

        test('equals 1 for sets of length one', function (){
            assert.equal(1, factorial(1));
        });

        test('equals 2 for sets of length two', function (){
            assert.equal(2, factorial(2));
        });

        test('equals 6 for sets of length three', function (){
            assert.equal(6, factorial(3));
        });
    });
});
```

## BDD

BDD는 TDD와 비슷하다고들 한다. 걍 BDD의 메인은 TDD가 유발한 이슈들을 제거하는 것이다.

TDD와 반대로, BDD는 sw 개발을 이끄는 **행위와 명세**를 작성한다. 행위와 명세는 테스트와 비슷해보이지만 차이점은 미묘하고 중요하다.

```javascript
var assert = require('assert'),
    factorial = require('../index');

describe('Test', function (){
    before(function(){
        // Stuff to do before the tests, like imports, what not
    });

    describe('#factorial()', function (){
        it('should return 1 when given 0', function (){
            factorial(0).should.equal(1);
        });

        it('should return 1 when given 1', function (){
            factorial(1).should.equal(1);
        });

        it('should return 2 when given 2', function (){
            factorial(2).should.equal(2);
        });

        it('should return 6 when given 3', function (){
            factorial(3).should.equal(6);
        });
    });

    after(function () {
        // Anything after the tests have finished
    });
});
```

주요차이점은 **wording**이다. BDD는 좀 더 장황한 스타일이다. 그래서 문장 읽는거와 비슷하다. 이것이 내가 앞에서 말한 "BDD는 TDD가 유발한 이슈를 제거하는 것"이라고 한거다. 문장 같은 너의 테스트를 읽는 능력은 테스트에 대한 생각을 변화시키는 것이다. 만약 너의 테스트가 유연하게 읽힌다면 너는 자연스럽게 더 나은 테스트를 작성할 수 있다.

**BDD 테스트는 feature에 더 집중되어있다. (not the actual result)**. BDD는 소프트웨어 **design** 하는데 도움을 준다고 들을 것이다. (not test it like what TDD is meant to do).

### TDD vs BDD

TDD와 BDD 중 선택하는 건 복잡하다. 언어에 대한 testing framework, 동료와 맞출 수 있는 것 등등에 따라 달라진다.

몇몇 논쟁은 BDD는 TDD보다 항상 낫다고 한다. 왜냐하면 BDD는 TDD 사용할 때 일어난 이슈들을 제거할 가능성을 가지고 있기 때문이다.

BDD의 핵심은 it **might** prevent issue.(보장이 되어있지 않다.) 좋지 않은 코드 구조와 같은 이슈, bad design practices etc..는 여전히 지속될 거시다.
