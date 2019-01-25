# 2. use jest-dom for improved assertion

jest-dom library는 test assertion을 작성하기 쉽게 도와주는 jest 내장 assertion 라이브러리에 유용한 extension을 제공.

```
...
expect(div.querySelector('nput').type).toBe('number')
```

i빼먹을 경우, _TypeError, cannot read property 'type' of null_ 이라고 말함.

얘는 뭐가 잘못됐는지 찾아 볼 때  별로 도움안됨. 뭐가 잘못됐는지 알려주면 도움될거 같음.

이런 도움을 줄 수 있는 얘가 `jest-dom`

- expect.extend를 모든 테스트에 추가하는 거는 되게 짜증남.
- `import 'jest-dom/extend-expect'`
  - 모든 assertion에 extend-expect를 자동으로 추가함.