# Manifest

index.html이 브라우저에서 로드되면, application에 필요한 bundle과 다른 assets들이 로드되고 연결된다. `/src` 디렉토리는 번들링 되고, 미니파이되고, webpack의 `optimization`이 lazy-loading 하기 위해 작은 chunks로 쪼개진다. 웹팩은 필요한 모듈 간에 인터랙션을 어떻게 관리할까? 이거 때문에 manifest data가 있다.

compiler가 어플리케이션을 resolve하고 매핑하기 때문에, 너의 모듈에 대한 자세한 기록을 유지한다. 이 데이터들은 `Manifest`라고 부르고, resolve 하고 번들된 모듈을 로드하여 브라우저에 갖다 주기위해 실행 중에 사용된다. `import` or `require` 뭐든 간에, 모듈 식별자를 가리키는 `__webpack_require__` 메서드를 가진다.

