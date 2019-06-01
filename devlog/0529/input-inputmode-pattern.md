# input

모웹, 웹뷰에서 input focus시 숫자 키보드가 노출되어야 한다.

관련해서 input의 attribute inputmode와 pattern에 대해 araboza

## inputmode(HTML5)

어떤 키보드가 노출되어야 하는지 **브라우저** 에게 힌트를 준다.(웹뷰에게는 안알려주나..?)
**type** attribute가 text, password, email, url의 값일 때 적용될 수 있는 속성이다.

`text`
유저 현재 장소(국가?)에 맞는 표준 텍스트 인풋 키보드

`numeric`
숫자 인풋 키보드. 0~9까지 숫자를 필요로 한다. 디바이스는 - 키를 보여줄 수도 있다. (`input type="number"`와 사용하는 것을 권장한다.)

> 안드로이드에서 숫자 키보드를 노출하기 위해 type=numeric인지 검사.

`tel`
핸드폰 키패드 인풋. 0~9를 포함한다. (\*, #도 포함). 핸드폰 키패드를 필요로 하는 input은 `<input type="tel">`을 사용해야만 한다.
출

## type

`tel`
핸드폰 번호를 입력하기 위한 control.

입력되는 값을 제한하기 위해 **pattern** 과 **maxlength** 와 같은 속성을 사용할 수 있다.

## pattern (HTML5)

input 내부의 값이 정규식으로 검사되는 속성이다.

**type** 의 속성이 `text`, `search`, `tel`, url, email일 때 적용된다. 다른거는 무시된다.

> `pattern=[0-9]*` ios에서 0~9 숫자 키보드를 노출할 때 이 속성을 검사.

---

테스트

https://bit.ly/2XeHF4H

<p class="codepen" data-height="265" data-theme-id="0" data-default-tab="html,result" data-user="cooking" data-slug-hash="RmYyLv" style="height: 265px; box-sizing: border-box; display: flex; align-items: center; justify-content: center; border: 2px solid; margin: 1em 0; padding: 1em;" data-pen-title="RmYyLv">
  <span>See the Pen <a href="https://codepen.io/cooking/pen/RmYyLv/">
  RmYyLv</a> by cooking (<a href="https://codepen.io/cooking">@cooking</a>)
  on <a href="https://codepen.io">CodePen</a>.</span>
</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>

pattern은 `[0-9]*` 동일

위 코드펜 실험 결과

숫자 키보드 노출 되는 조건

pattern은 ios에서
inputmode=numeric는 안드에서

inputmode=tel은 둘 다 노출됨.

ios12부터 pattern 미사용, tel로 대체해야함.

---

| 환경 | type | inputmode | 결과 |
| :--- | :--: | :-------: | :--- |


|ios 11 chrome| text | numeric |숫자와 특수문자 노출되는 일반 키보드|
|ios 11 chrome| text | tel |숫자만 노출 되는 키보드|
|ios 앱|text|numeric| 숫자만 노출되는 키보드|
|ios 앱|text|tel| 숫자만 노출되는 키보드|
