# DOMContentLoaded, load, unload

[DOMContentLoaded, load, unload](http://javascript.info/onload-ondomcontentloaded)
[DOMContentLoaded 전에 첫번쨰 페인팅 어케 일어남?](https://stackoverflow.com/questions/34289535/why-first-paint-is-happening-before-domcontentloaded)

- DOMContentLoaded : HTML이 모두 로드 되고 DOM트리가 완성되었지만, <img/>, stylesheet와 같은 외부 리소스가 아직 로드되지 않음.
- load : 브라우저에 img, style, script 등이 모두 로드 되었을 때

위 두가지만 봐도

DOMContentLoaded -> load 순임을 알 수 있다.

그럼 각각 언제 주로 사용될까?

- DOMContentLoaded : DOM이 준비 상태라 DOM 제어 가능
- load : 모든 리소스가 로드되었기 때문에 image 사이즈를 얻을 수 있다.

> 왜 </body> 전에 <script/> 태그가 있는가?
> HTML 문서 파싱 중에 <script/> 태그 만나면 파싱을 멈춘다.
> 중단 후 스크립트 전부 실행후에 재실행
> 즉 DOMContentLoaded 이벤트 발생시점도 늦어진다.
> 또한, DOM이 구축되지 않았는데 DOM selector 코드가 <script/> 문에 있다면 정상 동작이 안된다.

---

## DOM tree가 완성됐을 떄 이벤트 발생이라는 말은 layout, paint가 일어나지 않았다는 뜻?

일단 아래 글에 의하면 정답은 "NO"다. 왜냐면

[why first paint is happening before DOMCONtentLoaded](https://stackoverflow.com/questions/34289535/why-first-paint-is-happening-before-domcontentloaded)
