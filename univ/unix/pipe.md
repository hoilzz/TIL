# pipe

파이프는 수도 파이프와 같은 원리다.
- 파이프는 **2개의 프로세스를 연결**
  - 한쪽 프로세스는 **only write**
  - 다른 한쪽은 **only read**
- 위와 같은 특징 때문에 `Half-Duplex 통신(반이중 통신)`
- 송수신 모두 하려면 2개의 pipe 생성

## pipe 사용

```C
int pipe(int fd[2])
```

함수의 인자로 `int형 배열`이 들어가는 점에 유의하자.
- 배열이 넘어가는 이유는 이 함수가 `읽기전용`의 파이프와 `쓰기전용`의 파이프 2개를 리턴해 주기 때문이다.
- `[0] : read`, `[1] : write`

```C

int main() {
  int n, fd[2];
  char buf[255];
  int pid;


  if (pipe(fd) < 0) {
    perror("pipe err : ");
    exit(0);
  }

  // 자식프로세스라면 파이프에 자신의 PID 정보를 준다.
  else if(pid == 0) {
    close(fd[0]);
    while(1) {
      strcpy(buf, "hello mother process")
      write(fd[1], buf, strlen(buf));
      sleep(1);
    }
  }
  // 부모프로세스라면 파이프에서 데이터를 읽어들인다.
  else {
    close(fd[1]);
    while(1) {
      n = read(fd[0], buf, 255);
      printf("%s", buf);
    }
  }
}

```

- `pipe(fd)` : 파이프 생성
- fork를 통해 자식프로세스를 생성. 자식프로세스는 부모로부터 파일을 물려받는다.
  - **pipe**도 파일이다.
  - 자식에서 쓸 파이프는 `write`용 이므로, `read`를 위한 파이프는 `close(fd[0])`를 이용해 닫았다.
  *안 닫으면 어떻게될까? 왜 닫을까*

*sizeof(buf)가 아닌 strlen(buf)로 써야 하는 이유*
- sizeof(buf)면 입력되지 않은 index들의 똥값들이 들어가서 출력시 똥이 나옴
- strlen(buf)로 하면 쓰여진 string의 크기만 pipe로 입력됨



## characteristic

- FIFO 처리
- lseek 작동 ㄴㄴ해 (**읽은 데이터는 사라짐**)
- pipe는 파일이기 때문에 fork()에 의해 상속 가능
- 파이프는 집어넣고 가져가기 방식. 누가 가져갔는지 보장할 수 없다.
  - 만약 데이터가 없는데 파이프를 통해 read하는 경우 값이 들어올 때까지 blk
  - 그래서 파이프 0번쨰를 nonblk 모드로 해주어야한다
  - 이 때 fcntl() 사용

- blocking read & write
  - blocking read : pipe 빈 경우
  - blocking write : pipe 꽉 찬 경우

- 파이프 nonblk 설정하기

```C
fcntl(fd, F_SETFL, O_NONBLOCK)
```

- fd가 write : pipe가 차면 blk 없이 -1 즉시 리턴
- fd가 read  : pipe가 비어있으면 즉시 -1 리턴

## pipe 닫기

1. 쓰기 전용 pipe 닫기
  - read를 위해 기다리던 process들에게 0을 리턴(EOF 효과)

2. 읽기 전용 pipe 닫기
  - 더 이상 reader가 없으면, writer들은 SIGPIPE signal을 받는다.
  - signal handling 되지 않으면 process 종료.
  - 핸들링 되면 signal 처리후 write는 -1 리턴


## Pipe의 장단점
- 장점
  - 한쪽 process는 read, 한쪽 process는 write라는 단순 구조라면 고민없이 pipe 이용가능
- 단점
  - `반이중 통신`, 만약 procee가 `R/W` 모두 해야한다면 pipe 2개 필요
  - read와 write가 기본적으로 block으로 작동하기 때문에 프로세스가 read 중이라면 read 끝나기 전까지 write 불가능
  - 만약 2개의 프로세스가 모두 read 중이라면 영원히 block
  - 이럴 경우 Read 전용 프로세스와 write 전용 프로세스 2개를 만들어야 한다.


## pipe를 이용한 client-server
- client는 하나의 pipe로 request를 write
- Server는 여러 개의 pipe로부터 요청을 Read via **`select`**
  - no request from any client = server는 blocking
  - a request from any child = read the request
  - more than one request = read them in the order

## select(..);
입출력 다중화는 여러 개의 파일에서 발생하는 입출력을 관리하는 기술

- 지정된 fd_set 중 어느것이 R/W 가능한지 표시
- R/W 가능한 fd 없으면 blk
- 영구적 blk 막기 위해 `timeout` 설정 가능

### how to work
1. 입출력을 관리하고자 하는 파일의 그룹을 fd_set이라는 파일 비트 배열에 집어 넣기 (`FD_SET(int fd, fd_set *set)`)
2. 비트 배열의 값이 변했는지 확인하기

```C
int select(int nfds,
           fd_set *readfds,
           fd_set *writefds,
           fd_set *errorfds,
           struct timeval *timeout);
```

- `nfds` : 관심 있는 fd의 최대 번호 (fd +1)
- `readfds` : 읽기 가능한 fd 집합
- `writefds`: 쓰기 가능한 fd 집합

> fd_set *fset
- **먼저 `FD_ZERO`를 통해 fd_set 초기화**
- **`FD_SET` 을 이용하여 관심있는 각 fd값(r/w)을 fd_set에 할당**
- select에 r/w 별로 인자값 할당
- 만약 변경된 데이터가 있다면 해당 비트값이 1로 설정이 됨
  - `FD_ISSET`으로 일일히 확인해야함
- select 함수는 `데이터가 변경된 파일의 개수 즉 fd_set에서 비트 값이 1인 필드의 개수`를 반환
  - 이 때 변경된 파일의 목록을 반환하지 않는다는 것에 주의해야 한다
  - 그러므로 만약 최대 파일 지정번호가 1000이고 select이 1을 반환 했다면, 0번 부터 루프를 순환하면서 어떤 파일이 변경되었는지 검사해야함

### fd_set 관련 매크로

- `FD_ZERO`, `FD_SET`, `FD_ISSET`, `FD_CLR`


*fd_set 처음 선언시 fd bit의 값은?*

```C
// 2개의 파일을 실행하여 끝까지 출력할껀데, 끝까지 읽어도 바로 종료하지 않고
// select를 이용하여 파일에 새로운 내용이 입력되는지를 조사하여 새로운 내용 입력되면 화면에 출력.
FD_ZERO(&readfds);
FD_SET(fd[0], &readfds);
FD_SET(fd[1], &readfds);

state = select(fd[1]+1, &readfds, NULL, NULL, NULL);
```

- `fd[0]`과 `fd[1]`의 2개의 파일에 대해서 읽을 수 있는 데이터가 있는지 관심을 가지고 있으므로,
- **FD_SET을 이용하여 readfds의 비트배열에 fd값을 할당**
  - 값 할당 보다는 **비트 배열의 인덱스 값이 fd를 가리킨다**라는게 적당한 표현
- 그 다음 select를 이용하여 `readfds`의 비트값을 가져오고
- `FD_ISSET`을 이용하여 각 비트값을 검사.
