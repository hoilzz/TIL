# promise

> new Promise(function(resolve, reject){...})

**executor**
resolve 및 reject 인수와 함께 전달되는 함수. executor는 비동기 작업 시작한 다음 완료 후, resolve 함수를 호출하여 promise를 해결(resolve)하거나 오류가 발생하면 reject한다. executor 함수에서 오류 발생시 promise는 reject되고, 반환값은 무시된다.