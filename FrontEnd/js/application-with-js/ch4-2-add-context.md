# 4.2 컨텍스트 추가하기

모듈을 만들면 특히 콜백을 이벤트에 등록할 때 지역 컨텍스트를 유용하게 활용할 수 있다.

기본적으로 모듈 내부의 컨텍스트는 `전역`이다.

즉 모듈에서 사용하는 `this`는 `window`다.

```javascript
(function(){
	assertEqual(this, window);
})();
```

오브젝트에 아래왁 ㅏㅌ은 함수를 추가하여 `컨텍스트의 범위`를 조절할 수 있다.

```javascript
(function(){
	var mod = {};

	mod.contextFunction = function(){
		assetEqual(this, mod);
	};

	mod.contextFunction();
})();
```


이제 mod 오브젝트의 지역 컨텍스트에서 contextFunction()을 실행한다.

그러면 `contextFunction()` 함수 내에서는 전역 변수를 남발할 걱정 없이 this를 사용할 수 있다.

아래 코드는 위ㅏ 예제를 얼마나 유용하게 활용할 수 있는지 보여준다.

```javascript
(function($){
	var mod = {};

	mod.load = function(func){
		// func함수의 this를4ㅓㅕㅑㅅ 2번째 인자로 바인딩된 새로운 func 반환.
		$($.proxy(func, this));
	}

	mod.load(function(){
		// this를 window가 아닌 mod 오브젝트로 범위가 조절 됐다.
		this.view = $("#view");
	});

	mod.assetsClick = function(e){
		// 프로세스 클릭
	}

	mod.load(function(){
		this.view.find(".assets").click(
			$.proxy(this.assetsClick, this);
		)
	})

})(jQuery);
```

위 예제에서 콜백을 인자로 받는 `load()` 함수를 만들었다.

페이지 로드시 load() 함수가 호출된다.

콜백 호출할 때마다 **올바른 컨텍스트에서 실행되도록** `jQuery.proxy()`를 이용했다는 사실을 기억하자.

페이지 로드시, 콜백 함수 `assetClock()`을 포함하는 클릭 핸들러를 엘리먼트에 추가한다.

이정도면 컨트롤러의 역할을 완벽히 처리할 수 있다. (페이지 로드시 컨트롤러는 이벤트 핸들러를 뷰에 부착하기)

중요한 점은

*얼마나 컨트롤러의 상태를 로컬로 저장할 수 있으며 완벽하게 모듈로 캡슐화할 수 있는가*

이것이다.


## 4.2.1 라이브러리로 추상화하기

다른 모듈과 컨트롤러에서 재사용할 수 있도록 위 구현을 라이브러리로 추상화하자.

기존의 load() 함수는 그대로 포함하면서 `proxy()`, `include()` 같은 함수를 새로 추가한다.

...

페이지가 로드되면 view 변수를 만들고 이벤트 리스너 두 개를 추가한다.

이벤트 리스너는 마우스가 엘리먼트 위를 움직일 때마다 `toggleClass()`



### 4.2.2 문서를 로딩한 다음에 컨트롤러 로딩하기

지금은 DOM을 로드하기 전에 컨트롤러 일부를 로드하고

다른 부분은 페이지의 문서를 로드한 다음 콜백에서 호출한다.
