# lerna

큰 코드 베이스를 독립적으로 버전화된 패키지들로 쪼개는 것은 _코드 공유할 때_ 극도로 유용하다.
그러나, 많은 저장소에서 변경하는 것은 지저분하고 추적하기 어렵다. 그리고 저장소 전반적인 테스트는 매우 복잡해진다.

이 문제를 해결하기 위해, 몇개 프로젝트는 코드베이스를 multi-package 저장소로 구성한다.(얘는 [monorepo](https://github.com/babel/babel/blob/master/doc/design/monorepo.md)라고 부름)

> monorepo
> 여러 개의 repos에서 여러개의 모듈 프로젝트를 저글링하는 것은 신생아에게 자전거 타는 법 가르치는 것과 같다.
> 바벨은 monorepo 접근법을 따르고, 공식적으로 유지 관리되는 모듈은 동일 저장소에 있도록 하는 것이다.
> 이거슨 taboo지만 장단점을 살펴보자.

장점:

- __Single__ lint, build, test and release process
- 모듈 간의 변경을 쉽게 조정 가능
- __Single__ place to report issues.
- dev 환경 설정하기 쉬움
- Tests across modules are run together which finds bugs that touch multiple modules easier.

단점:

- codebase가 위협적으로 보임
- repo 사이즈가 넘나 큼
- [github에서 직접 npm install을 할 수 없음](https://github.com/npm/npm/issues/2974)

다시 이어서, Babel, react 등과 같은 프로젝트는 _단일 레포_ 다.

lerna는 multi-package repositories with git and npm 을 관리하는 작업 과정을 최적화하는 도구다.
__Lerna는 개발 및 빌드 환경에서 패키지의 수많은 복사본에 필요한 시간과 공간을 감소시킬 수 있다.__
(일반적으로 프로젝트를 많은 별도의 npm 패키지로 나누는 단점이다.)

## Lerna repo 생김새

```
my-lerna-repo/
  package.json
  packages/
    package-1/
      package.json
    package-2/
      package.json
```

## Lerna가 할 수 있는것

Lerna에서 2개의 주요 명령어는 `lerna bootstrap` and `lerna publish`다.
`bootstrap`은 저장소간에 의존성을 연결할 것이다. `publish`는 업데이트된 패키지의 publish를 도울 것이다.


## How It Works

2가지 모드

1. Fixed
2. Independent

### Fixed/Locked mode(default)

Fixed 모드는 single version line에서 동작한다. `version` key 아래에서 프로젝트 루트에 있는 `lerna.json`에서 버전이 유지된다. `lerna publish`를 실행할 때, 만약 모듈이 release가 만들어진 이후에 업데이트 됐다면, 너가 릴리즈한 new version으로 업데이트 될 것이다. 이거슨 너가 필요할 때 새로운 패키지 버전만 퍼블리시할 수 있다는 것을 의미한다.

---


### lerna.json

lerna.json에서 packages config는

## Common devDependencies

대부분 devDependencies는 Lerna repo의 루트로 올려질 수 있다.

이것의 few benefits:

- 모든 패키지가 주어진 디펜던시의 동일한 버전 사용
- 루트에 있는 dependencies를 최신으로 유지
- 의존성 설치 시간 감소
- 스토리지가 덜 필요함

npm 스크립트로 실행가능한 binary로 제공된 `devDependencies`는 사용되는 곳에 직접 설치되어야함

예를 들어 `nsp` 의존성은 `lerna run nsp`가 필수다. (and packages 디렉토리 내에서 `npm run nsp`도 실행되야함)

```json
{
  "scripts": {
    "nsp": "nsp"
  },
  "devDependencies": {
    "nsp": "^2.3.3"
  }
}
```