# lerna-faq

# lerna faq

## 명령어

## lerna bootstrap

모든 디펜던시를 설치하고 상호 종속성을 link

얘를 실행하면, 명령어는

1. 각 패키지의 모든 외부 디펜던시에 대해 `npm install`
2. 서로 종속성인 모든 Lerna `packages`를 Symlink하기
3. 모든 부투스트랩된 패키지에서 `npm run prepublish`
4. 모든 부투스트랩된 패키지에서 `npm run prepare`

**–hoist[glob]**

레포 루트에서 `glob`과 일치하는 external 설치. 그래서 모든 패키지에서 이용 가능하다. 이 디펜던시의 바이너리들은 dependent 만약 glob 옵션이 제공 되지 않는다면 기본적으로 `**`(전부)다.

## lerna hoisting

> 이 기능 활성화 할 때 조심해서 써야됨. 설정 잘못 건드리면 문제 일으킴

    Lerna bootstrap --hoist

- 공통 디펜던시들은 top-level `node_modules`에서 설치됨.
- 대부분의 공통 디펜던시들은 호이스팅되지만, 다른 버전을 가진 패키지는 local `node_modules`에 필수 디펜던시 설치를 하게됨
- 예를 들어 `lerna bootstrap`은 항상 `npm install`을 사용한다.
- 공통 패키지의 Binary는 symlink된다. 그래서 package.json scripts 수정할 필요 없음

> 참고 Node의 module resolution 알고리즘은 리커시브함 package A 를 찾을 때, local node_modules에서 찾고, 없으면 ../node_modules/A, ../../node_modules/A, … 에서 찾음

## lerna publish

    lerna publish # 최근 릴리즈에서 변경된 패키지 배포
    lerna publish from-git # 현재 커밋에서 태스된 패키지를 명시적으로 퍼블리시
    lerna publish from-package # 레지스트리에 제공되지 않은 최신 버전인 패키지를 명시적으로 퍼블리시

## lerna run

    lerna run <script> -- [..args] # run npm run my-script in all packages that have it
    lerna run test
    lerna run build
