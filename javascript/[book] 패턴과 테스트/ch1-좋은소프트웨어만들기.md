# ch1 좋은 소프트웨어 만들기

```javascript
// 다른 전역 변수와 충돌을 피하기 위해 명칭공간을 생성한다.
var rj3 = {};

// svg라는 하위 명칭공간을 만든다.
rj3.svg = {};

// rj3.svg 명칭공간에 line 함수를 넣는다.
rj3.svg.line = function() {
  var getX = function(point) {
    return point[0];
  },
  getY = function(point) {
    return point[1];
  },
  interpolate = function(points) {
    return points.join("L");
  };

  function line(data) {
    var segments = [],
      points = [],
      i = -1,
      n = data.length,
      d;

    function segment() {
      segments.push("M",interpolate(points));
    }

    while (++i < n) {
      d = data[i];
      points.push([+getX.call(this,d,i), +getY.call(this,d,i)]);
    }

    if (points.length) {
      segment();
    }

    return segments.length ? segments.join("") : null;
  }

  line.x = function(funcToGetX) {
    if (!arguments.length) return getX;
    getX = funcToGetX;
    return line;
  };

  line.y = function(funcToGetY) {
    if (!arguments.length) return getY;
    getY = funcToGetY;
    return line;
  };

  return line;
};
```

D3.js에서 SVG 라인 생성기를 만드는 함수를 통해 좋은 소프트웨어에 대해 알아보자.
배열 데이터를 SVG 경로(path)로 변환하는 함수다. SVG 경로는 SVG언어로 표현하면 단순 문자열이다. 

```html
// x,y 좌표가 (10,130)인 지점으로 이동(M)한 뒤, (100,60)까지 선(L)을 그리고, 또 (190, 160)까지 선을 그리고, 마지막으로 (280,10)까지 선을 그린다.
<path d="M10,130L100,60L190,160L280,10"></path>
```

```javascript
var arrayData = [
    [10,130],
    [100,60],
    [190,160],
    [280,10]
],
lineGenerator = rj3.svg.line(),
path = lineGenerator(arrayData);
```

lineGeneator에는 어떤 값이 할당될까? rj3.svg.line()의 반환값은 line 함수(외부함수 이자  rj3.svg.line의 내부에 중첩된 함수)다. 강력한 자바스크립트 함수를 원한다면 일급 객체인 함수를 인자로 주고 반환값으로 돌려받는 형태에 길들어야 한다. 자바스크립트 함수는 일급 시민으로서 자신만의 프로퍼티와 메서드를 가질 수 있다. 

```javascript
line.x = function(funcToGetX) {
    if (!arguments.length) return getX;
    getX = funcToGetX;
    return line;
}
```

---

lineGenerator(arrayData)는 arrayData를 인자를 주고 호출한다. 이 배열은 line함수의 data인자가 되고 while루프는 원소를 하나씩 꺼내서 points 배열을 채워나간다.

```javascript
var getX = function(point) {
    return point[0];
},
getY = function(point) {
    return point[1];
}

...

while(++i < n) {
    d = data[i];
    points.push([+getX.call(this, d, i), +getY.call(this, d, i)]);
}
```

data 원소는 각각 변수 d로 받아 getX, getY 함수에 전달한다. 이 함수들은 x, y 좌표값을 추출한다. 

하지만 만약, 점 데이터가 `[x, y]` 좌표 값이 담긴 배열이 아닌 `{ x: 10, y: 130}`과 같은 **객체**라면? 이럴 때는 어떻게 rj3.svg.line으로 라인을 그릴 수 있을까? 다음과 같이 해볼 수도 있다.

```javascript
(function() {
    var objectData = [
        {x: 10, y: 130},
        {x: 100, y: 60},
        {x: 190, y: 160},
        {x: 280, y: 10}
    ],
    arrayData = objectData.map(function(d) {
        return [+d.x, +d.y];
    }),
    lineGenerator = rj3.svg.line(),
    path = lineGenerator(arrayData);
}());
```

위와 같이 데이터를 즉석에서 변환하는 코드를 추가하면 된다. 하지만 

- **같은 데이터를 하나 더 복사하는 건 낭비다**.
- 사용자 인터페이스에도 걸림돌이 될 수 있다.

그렇다면, 데이터가 바뀔 경우 라인도 **동적으로** 바뀌게 하고 싶을 때는 어떻게 할까?

---

**line.x 와 line.y는 정말 잘 결정한 설계 요소다.** 사용법을 보자.

```javascript
(function() {
    var objectData = [
        {x: 10, y: 130},
        {x: 100, y: 60},
        {x: 190, y: 160},
        {x: 280, y: 10}
    ],
    lineGenerator = rj3.svg.line()
        .x(function(d) {return d.x;})
        .y(function(d) {return d.y;}),
    path = lineGenerator(arrayData);
})
```

`.x(function(d) {return d.x;})` 호출시 getX 변수의 기본 함수를 교체한다.

```javascript
points.push([+getX.call(this, d, i), +getY.call(this, d, i)])
```

getX.call은 교체한 함수를 호출하여 해당 객체의 x프로퍼티, 즉 사본 아닌 원래 객체 값을 반환한다. **call**을 눈여겨보자. x 좌표값을 얻는 함수가 뭐든(function(d) {return d.x}) 는 1개 인자밖에 없긴하다) 인자 2개를 넘겨 호출하도록 구현되어있다. 두 번쨰 인자 i는 배열 인덱스로, 여기서는 쓰이지 않지만 다른 곳에서 쓰일 수 있다. 바로 이것이 **함수 오버로딩**이라는 OOP 개념을 JS에 녹인 원리다.

```javascript
line.x = function(funcToGetX) {
    if (!arguments.length) return getX;
    getX = funcToGetX;
    return line;
}
```

`if (!arguments.length) return getX;`에서 arguments는 호출한 함수의 인자를 담은 유사배열 객체로 함수 내부에서 사용된다. 만약 인자가 없다면 getX값을 있는 그대로 반환한다. 즉, 인자 없이 line.x 호출시 x 좌표의 현재 접근자를 리턴한다. 인자가 있다면 x 좌표 접근자를 주어진 인자로 바뀐 뒤, **전혀 다른 반환값인 line 함수 객체를 돌려준다.** **그래서 인자 i도 같은 방법으로 `함수 오버로딩`을 할 수 있다.**

> **자바스크립트에서 객체 지향적 함수 오버로딩 개념은 함수의 arguments를 보고 여기에 뭔가 맞추는 행위다.**

**그런데 x 좌표 접근자를 지정하는 함수가 왜 굳이 line을 반환했을까? 호출을 체이닝할 수 있기 때문이다.**

---

rj3.svg.line() 호출시 내부 line 함수를 반환한다고 했다. 