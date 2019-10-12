# What is a Pure function?

[pure fn이란?](https://medium.com/javascript-scene/master-the-javascript-interview-what-is-a-pure-function-d1c076bec976)

순수함수는 FP, 안전한 동시성, react + reddux app을 포함한 다양한 목적에 필수적이다.
하지만 "pure function"이란 무엇일까?

## What is a function?

function은 **argument** 라는 input을 받고 **return value** 라 불리는 output을 만든다. 함수는 다음 목적을 제공한다.

- **Mapping** : 주어진 input을 기반으로 output을 만든다. 함수는 input 값과 output 값을 **매핑** 한다.

- **Procedures** : 함수는 일련의 스템을 수행하기 위해 호출된다. 이 시퀀스는 절차로 알려져있고, 절차형 프밍 스타일이다.

- I/O : 몇몇 함수는 스크린, 스토리지, 시스템 로그, 네트워크와 같은 시스템의 다른 부분과 소통하기 위해 존재한다.

## Mapping

순수 함수는 매핑에 관한것이다. 함
