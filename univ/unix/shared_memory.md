# shared memory
- 둘 이상의 프로세스가 물리적 메모리의 일부를 공유

## shmget()

```C
int shmget(key_t key, size_t size, int permflag)
```

- key : 공유 메모리 영역의 id
  - IPC_PRIVATE 또는 ftok 함수로 생성한 키
- size : 공유 메모리 영역 최소 크기
- permflag : access permission (IPC_CREAT, IPC_EXCL)

### 공유 메모리 생성 예시
