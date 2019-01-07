# Caching

This guide focuses on the configuration needed to ensure files produced by webpack compilation can remain cached unless their contents has changed.

## Output Filenames

`output.filename`의 기능을 이용하여 변경된 파일만 브라우저가 가져오도록 하는 방식이다. `[hash]`는 filename 내부의 build-specific hash를 포함하기 위해 사용된다. 그러나 `[contenthash]` 사용하는게 더 낫다. 이것은 각 asset마다 다른 file의 content에 대한 해시를 사용하기 때문이다.

...

## module Identifier

`main` bundle의 해시만 바뀌는걸 예상할 수 있다. 하지만, 3개 다 바뀜.

기본적으로 resolving 순서에 기반하여 `module.id`는 증가하기 때문에