# faq

- import문으로 어떻게 node_modules 의 디펜던시를 가져올까?
  - node_modules 내부에 여러가지 파일이 있는데 어떤게 모듈인지 알고 가져올까?

```
If your package.json file also has a module field, ES6-aware tools like Rollup and webpack 2 will import the ES6 module version directly.
```

여튼 package.json에 모듈 필드가 있다면, 웹팩같은 ES6-aware tools이 ES6 module을 직접 import 함