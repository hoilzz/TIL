# Object.assign()
하나 이상의 `source object`로부터 `target object`로 `property`를 복사하는데 사용된다.

## Syntax
> Object.assign(target, ... sources)

## Description
소스 프로퍼티와 동일한 프로퍼티의 키를 가진 타겟 오브젝트의 프로퍼티들은 소스 오브젝트의 프로퍼티로 덮어쓰기 된다.

<br>
Object.assign()은 소스 오브젝트 대상으로 게터를 호출하고, 타겟 오브젝트 대상으로 세터를 호출한다.
그러므로 소스 오브젝트의 프로퍼티를 그냥 복사하거나 새로운 프로퍼티를 생성하면서 타겟 오브젝트의 프로퍼티를 할당해간다.
