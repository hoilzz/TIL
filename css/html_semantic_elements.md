## HTML5 Semantic Elements

Semantics는 언어에서 어구와 단어의 의미다.

Semantic elements는 의미를 가진 element다.


What are Semantic Elements?

semantic element는 브라우저와 개발사 둘 다에게 명백하게 의미를 설명한다

non-semantic element  :  <div> and <span> - 컨텐츠에 대해 아무것도 말하지 못한다.
semantic element      :  <form>, <table>, and <img> - 컨텐츠에 대해 명백히 정의

HTML5 semantic elements는 모든 모던 브라우저에서 지원한다.

게다가, 오래된 브라우저에게 unknown elements를 처리하는 방법을 알려줄 수 있다.

Read about it in HTML5 [Browser Support](http://www.w3schools.com/html/html5_browsers.asp)

> You can even teach IE6 how to handle unknown HTML elements.


## Define HTML5 Elements as Block Elements

HTML5는 8개의 새로운 semantic HTML element를 정의한다.

All these are *block-level* element.


*오래된 브라우저에서 올바른 행동을 보호하기 위해,*
CSS display property를 block으로 세팅해야 한다.


> header, section, footer, aside, nav, main, article, figure {
 display : block;
}
