# msync()

```C
msync(void *addr, size_t len, int flags)
```

## def
`mysnc()` 없이, `munmap` 호출 전에 changes가 write된다는 보장이 없다. 더 정확하게 하기 위해, addr에서 시작하는 메모리 area부터 length만큼 상응하는 파일의 부분이 업데이트 된다.
