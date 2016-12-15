# IPC 설비

- 서로 다른 process들도 동일 IPC 객체는 같은 key 값으로 접근
- 시스템에서 unique한 key값들을 사용해야 함

## Key 값 생성
```C
key_t ftok(const char *path, int id)
```
- 해당 파일의 st_dev, st_ino와 id로 key값 생성

## IPC 객체 상태 구조

```C
  struct ipc_perm {
    uid_t cuid
    gid_t cgid
    uid_t uid_t
    gid_t gid
    mode_t mode
  }
```

## msg passing
msg queue를 통한 msg 전달
1. msgget : queue 생성
2. msgsnd : msg 보내기
3. msgrcv : msg 받기

## msgget 시스템 호출

```C
int msgget(key_t key, int permflags)
```

  - key : msg queue의 key 값
  - permflags : queue에 대한 access permisson
    - IPC_CREAT
      - 해당 queue가 없으면, 생성한 후  return
      - 이 flag가 설정되지 않은 경우에, queue 가 존재하는 경우에만 return
    - IPC_EXCL
      - 해당 큐가 존재하지 않은 경우만 성공
