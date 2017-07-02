# data-*

`data-*` global attribute는 custom data attributes라 불리는 atrribute의 클래스를 형성한다.
이것은 소유자 정보가 HTML과 DOM 사이에서 교환되도록 허용한다. 모든 custom data는 element의 `HTMLElement` interface를 통해 이용가능하다. `HTMLElement.dataset` 프로퍼티는 custom data에 대한 접근하도록 한다.

`*`는 다음 제한사항만 지키면 어떠한 이름으로도 대체될 수 있다.

	- 이름은 xml로 시작하지 않는다.
	- 이름은 세미콜론 포함하지 않는다.
	- 이름은 대문자 A to Z 포함하지 않는다.

HTMLElement.dataset 프로퍼티는 DOMStringMap이다. 커스텀 데이터 attribute인 `data-test-value`는 `HTMLElement.dataset.testValue`(or `HTMLElement.dataset["testValue"]`)를 통해 접근 가능하다. (dash는 다음 문자 대문자로 대체된다. 걍 카멜케이스로 생각하자.)

## Usage

`data-*` attribute를 추가하여, 평범한 HTML element가 복잡해지고 강력한 program-object가 될 수 있다. 예를 들어, 게임에서 space-ship `sprite`는 몇몇 data-* attribute 등 을 가진 간단한 img element가 될 수 있다.

```html
<img class="spaceship cruiserX3" src="shipX3.png"
  data-ship-id="324"   data-weapons="laserI laserII"   data-shields="72%"
  data-x="414354" data-y="85160" data-z="31940"
  onclick="spaceships[this.dataset.shipId].blasted()"
</img>
```

## summary

- HTML에 `data-*` 로 시작하는 custom class를 통해 많은 데이터 입력 가능
- 접근 할 때 `HTMLElement.dataset.` + `카멜케이스 이름`
