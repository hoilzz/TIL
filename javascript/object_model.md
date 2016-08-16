# Object Model

객체화 되어있는 웹브라우저 구성요소
자바스크립트로 이 객체를 제어해서 웹브라우저 제어 가능
이 객체들은 서로 계층적 관계로 구조화 되어있다.
BOM과 DOM은 이 구조를 구성하고 있는 가장 큰 틀

![javascript Object][object]
[object]: https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/904/2229.png "object"

### BOM
Browser Object Model
웹페이지의 내용을 제외한 브라우저의 각종 요소들을 객체화시킨것.
전역객체 Window 프로퍼티에 속한 객체들이 여기에 속한다

> <body>
>   <input type ="button" onclick="alert(window.location)" value="alert(window.location)">
>   <input type="button" onclick="window.open('bom.html')" value="window.open('bom.html')"
> </body>
>

### DOM
Document Object Model
웹페이지의 내용을 제어.
window의 프로퍼티인 document 프로퍼티에 할당된
Document 객체가 이러한 작업

> console.log(document.body)
> console.log(document.getElementsByTagName('body')[0]);
