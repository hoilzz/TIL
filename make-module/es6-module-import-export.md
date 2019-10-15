# es6 module에서 import export는 정확히 어떻게 동작하는걸까?

[시간없으면 이것만](https://2ality.com/2015/07/es6-module-exports.html)
[참고1](https://ponyfoo.com/articles/es6-modules-in-depth)
[참고2](https://esdiscuss.org/topic/ambiguity-with-default-exports-and-live-bindings)
[참고3](https://stackoverflow.com/questions/39259729/javascript-reference-vs-binding-whats-the-difference)

[참고4](https://rollupjs.org/repl/?version=1.24.0&shareable=JTdCJTIybW9kdWxlcyUyMiUzQSU1QiU3QiUyMm5hbWUlMjIlM0ElMjJtYWluLmpzJTIyJTJDJTIyY29kZSUyMiUzQSUyMmltcG9ydCUyMCU3QiUyMGNvdW50JTJDJTIwaW5jcmVtZW50JTIwJTdEJTIwZnJvbSUyMCcuJTJGaW5jcmVtZW50ZXIuanMnJTNCJTVDbiU1Q25jb25zb2xlLmxvZyhjb3VudCklM0IlNUNuaW5jcmVtZW50KCklM0IlNUNuY29uc29sZS5sb2coY291bnQpJTNCJTVDbmNvbnNvbGUubG9nKGNvdW50KSUzQiU1Q25jb3VudCUyMCUyQiUzRCUyMDElM0IlMjIlN0QlMkMlN0IlMjJuYW1lJTIyJTNBJTIyaW5jcmVtZW50ZXIuanMlMjIlMkMlMjJjb2RlJTIyJTNBJTIyZXhwb3J0JTIwbGV0JTIwY291bnQlMjAlM0QlMjAwJTNCJTVDbiU1Q25leHBvcnQlMjBmdW5jdGlvbiUyMGluY3JlbWVudCgpJTIwJTdCJTVDbiU1Q3Rjb3VudCUyMCUyQiUzRCUyMDElM0IlNUNuJTdEJTVDbiUyMiU3RCU1RCUyQyUyMm9wdGlvbnMlMjIlM0ElN0IlMjJmb3JtYXQlMjIlM0ElMjJjanMlMjIlMkMlMjJnbG9iYWxzJTIyJTNBJTdCJTdEJTJDJTIybW9kdWxlSWQlMjIlM0ElMjIlMjIlMkMlMjJuYW1lJTIyJTNBJTIybXlCdW5kbGUlMjIlN0QlMkMlMjJleGFtcGxlJTIyJTNBbnVsbCU3RA==)

[벨로그](https://velog.io/@doondoony/JavaScript-Module-System)

## es6 module은 immutable binding을 내보낸다.(export)

CJS와 달리 ES6은 value와 **binding** 을 내보낸다.

## How bindings work

ES module은 값이 아닌, live binding을 내보낸다. 그래서 초기에 import 된 후에, 값은 변경될 수 있다.
