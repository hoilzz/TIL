# promise

promise는 자바스크립트 비동기 처리에 사용되는 객체다. 특정 코드의 실행이 완료될 때까지 기다리지 않고 다음 코드를 먼저 수행하는 비동기를 처리한다.

promise를 사용하지 않고 api 호출시.. 데이터를 받아오기 전에 데이터를 받은 것 마냥 데이터를 표시하게 된다. 이 때, 오류가 발생하거나 빈화면이 노출된다. 이 문제를 promise로 해결할 수 있다.

## promise의 에러 처리는 catch()로 하자

then의 두번쨰 인자(function(err){})로 처리할 수 있지만, catch로 처리하는게 효율적이다.

then 콜백 함수에서 오류 발생시 오류를 제대로 잡지 못한다.

```
Uncaught (in promise) Error:
```

하지만 동일 오류를 catch로 잡으면

```
then error: error..
```
