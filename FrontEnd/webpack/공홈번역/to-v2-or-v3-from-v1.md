# to v2 or v3 from v1

## module.loaders is now module.rules

기존 loader 설정은 강력한 규칙 시스템으로 대체되어 로더 등을 구성해왔다. 호환성을 이유로, 기존 `module.loaders` 문법은 여전히 유효하고 기존 이름은 파싱된다. new naming convention은 이해하기 쉽고 `module.rules`를 이용하도록 업그레이드해야하는 좋은이유다.

## module.rules

### Condition

- `{include: Condition}`: 조건이 일치해야한다.