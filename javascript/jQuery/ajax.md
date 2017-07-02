# ajax

## how to use

```javascript
$.ajax({
	// URL 필수 요소
	url : 'url',
	// []는 반복해서 사용할 수 있다는 의미.
	[, options]
})
```

## getJSON

```javascript
// $.getJSON(URL, DATA, CALLBACK);

$(document).ready(function(){
	$.getJSON('sample.json', function(data){

	})
})
```

 
