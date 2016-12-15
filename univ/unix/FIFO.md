# FIFO
`First In First Out`, `먼저 입력된 데이터가 먼저 전달되는 `통신, `PIPE`도 이 전달 메커니즘을 따른다.
: FIFO는 named Pipe다.

## pipe와 named pipe

- 공통점 : 먼저 입력된 데이터가 먼저 전달되는 흐름
- 차이점
  - named pipe는 사용할 pipe를 `명명` 할 수 있다.
  - pipe는 사용할 pipe를 명명할 수 없다. 그래서 `익명 pipe`


### 익명 파이프
- 데이터 통신을 할 프로세스가 명확하게 알 수 있을 때 사용
- 송신할 프로세스는 수신할 프로세스를 알고, 수신 프로세스도 반대로 알고 있을 때 (반대로, 부모 프로세스와 자식 프로세스는 서로 알 필요가 없다.)

### named pipe
- 자식과 부모 관계가 아닌 프로세스는 `이름`을 알아야 한다.
- 리눅스에서 파일은 시스템 전역적으로 관리하는 객체이니 이름만 아면 어떤 프로세스라도 접근 가능. 서로 관련 없는 프로세스도 named pipe로 통신 가능


## named pipe 생성

```C
int mkfifo (cont char *pathname, mode_t mode)
```

```C
mkfifo("/tmp/myfifo", O_WRONLY);
mkfifo("/tmp/myfifo", O_WRONLY|O_NONBLOCK);
```

- 일반 open 호출은 다른 프로세스가 읽기 또는 쓰기를 위해 open될 때까지 blk
- non-blk open의 경우 상대 프로세스가 준비되지 않으면 -1 return
- fifo를 이용한 통신 예제
  - reader가 O_RDWR로 fifo를 open한 이유?
  - writer 종료 시 blk 된채로 기다리기 위해,
  - 아니면, 무한 0 return



























































# FIFO

- pipe는 동일 ancestor를 갖는 프로세스들만 연결 가능(child-process)
- FIFO는 모든 프로세스들 연결 가능
- UNIX의 file 이름 부여 받음
- 소유자, 크기, 연관된 접근 허가를 가진다
- 일반 file처럼 open, close, read, write, remove 가능

## HOW TO USE
- FIFO 만들기

  ```C
    int mkfifo(const *pathname, mode_t mode)
    open(O_RDONLY 또는 O_WRONLY)
  ```

  ```C
    mkfifo("/tmp/fifo", 0666);
    fd = open("/tmp/fifo", O_WRONLY)
  ```
  - **`O_RDWR`**
    - file에 R 또는 W 하는 경우
    - writer 종료시 blocking 된 채로 기다리기 위해(`O_RDWR`이 아니면 무한 0 return)

### open
- 일반 open 호출은 다른 프로세스가 R 또는 W를 위해 open될 때까지 block
- non-blokcing open의 경우(상대 프로세스가 준비되지 않으면) -1 return

## Ex

```C
int main(void){
        int fd, n;
        char buf[512];

        mkfifo("fifo", 0600);

        fd=open("fifo", O_RDWR);

        for (;;){
               n=read(fd, buf, 512);
               write(1, buf, n);
        }
}
```

```C
int main(void){
        int fd, j, nread;
        char buf[512];

        if ((fd=open("fifo", O_WRONLY|O_NONBLOCK)) < 0){
               printf("fifo open failed");
               exit(1);
        }

        for (j=0; j<3; j++){
               nread=read(0, buf, 512);
               write(fd, buf, nread);
        }

        exit(0);
}
```
