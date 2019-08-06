# TS에서 extends

## Conditional Types

2.8에서 non-uniform type mapping을 표현할 수 있는 기능이 추가됐다.
조건부 타입은 2개의 가능한 타입 중 1개를 선택할 수 있다.

```
T extends U ? X : Y
```

T가 U에 할당가능하면 X, 그렇지 않으면 Y