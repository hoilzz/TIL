# asset management

> file-loader는 파일에서 `import / require()`를 url로 리졸브하고 ouput 디렉토리에 파일로 emit 한다.

```js
// service.js
import MyImage from "./my-image.png";
```

위 코드의 이미지는 `output` 디렉토리에 추가되고 MyImage 변수는 처리된 후에 finalurl을 포함한다.

```css
my_image {
  background: url("./myImage.png");
}
```

css-loader를 사용할 때, 비슷한 프로세스가 일어난다.
CSS 내부에서 loader는 위 코드의 파일이 local파일 인 것을 인지한다.
그리고 `./my-image.png` path를 `output` directory 내부의 이미지에 대한 final path로 변경한다.
