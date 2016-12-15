# 메시지 큐

메시지를 queue 데이터 구조 형태로 관리한다.
- 메시지 큐는 커널에서 전역 관리
- 모든 프로세스에서 접근 가능
- 메시지큐의 접근자(Id)를 아는 모든 프로세서는 동일한 메시지큐에 접근하여 데이터 공유 가능
- 메시지 type에 의해 여러 종류의 메시지를 다룰 수 있다
- 여러개의 프로세스가 하나의 메시지큐를 access할 때, 각 메시지에 type을 줌으로써 각 프로세스에게 필요로 하는 메시지만을 가져가게 할 수 있는 편리한 기능 제공
  - 구조체를 몽땅 넘길 수 도 있음

## 메시지 큐 생성, 사용 제어

```C
int msgget(key_t key, int msgflg)
int msgsnd(int msqid, struct msgbuf *msgp, size_t msgsz, int msgflg)
ssize_t msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long msgtyp, int msgflg)
```

- 최초 msgget을 이용하여 커널에 메시지큐를 요청하면, 커널은 해당 메시지큐를 위해 메모리를 할당하고, 메모리 관리와 그밖의 정보 관리를 위해 위의 구조체를 세팅

## 메시지 큐 생성

> int msgget(key_t key, int msgflg)

- **메시지 큐 생성** or **기존에 있던 메시지 큐의 참조**
- `msgflg`
  - `IPC_EXCL`이 지정될 경우, 이미 key로 존재하는 메시지큐 있다면 -1 리턴
- 성공할 경우 int형 메시지 큐 식별자 돌려준다

## 메시지큐에 데이터 쓰기

`int msgsnd(int msqid, struct msgbuf *msgp, size_t msgsz, int msgflg)`

1. `int msqid`
  - 메시지큐 식별자
2. `struct msgbuf *msgp`
  - 메시지큐에 넘기고자하는 구조체

  ```C
  struct msgbuf {
    long mtype;
    char mtext[255];
  }
  ```

  - 메시지 구조체의 매우 전형적인 모습
  - `long mtype` 은 필수요소
    - 메시지 타입으로 반드시 0보다 더 큰 정수여야 한다.
    - mtype을 다르게 줘서, 특정 프로세스에서 특정 메시지 참조할 수 있도록 한다.
    - 예를 들어 A라는 프로세스가 A' 메시지 타입을 참조해야 하고,
    - B는 B'로 참조하도록 만들어야 한다면,
    - msgBuf를 만들 때, mtype에 A'은 1, B'는 2 이런식으로 메시지 타입을 정의하고 A는 mtype이 1인 것을 B는 mtype이 2인 것을 가지고 가도록 만들면 된다.

3. `msgsz`
  - 구조체 사이즈
4. `msgflg`
  - 메세지 전달 옵션
  - `IPC_NOWAIT` : 메시지가 성공적으로 보내질 때까지 block
  - 설정 X : 바로 return

## 메시지큐의 데이터 가져오기

`ssize_t msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long msgtyp, int msgflg)`

4. `long msgtyp`
  - 메시지를 보낼 구조체를 만들때 `mtype`을 정의하여, 메시지를 분류해서 접근할 수 있도록 할 수 있다.
  - 메시지를 가져올 때는 `msgtyp`를 통해서 자기가 원하는 `msgtyp`의 메시지 구조체에 접근할 수 있다.
  - `msgtyp == 0` : GET 메시지 큐의 첫번쨰 데이터
  - `msgtyp > 0`  : mtype이 같은 msgtyp과 같은 첫번째 데이터 돌려줌
  - `msgtyp < 0`  : mtype이 msgtyp의 절대값보다 작거나 같은 첫번째 데이터 돌려줌
  *여기서 첫번째 데이터는 업로드 순서인가.. 아니면 그 값에 가까운 mtyp 번호 인가*
  *첫번째 데이터라는 뜻은, 동일 메시지 타입으로 메시지 전송시 큐 처럼 쌓이는거 같다. 그래서 쌓인 것 중 가장 첫번째 데이터를 OUT*

## 예제를 통해 알아본 메시지 큐

총 2개의 예제프로그램 만든다.
- 하나는 메시지큐 생산자로써, 메시지큐 생성하고 메시지 보내는(msgsnd) 일
- 소비자로써 메시지큐에 있는 데이터 받아오기

<br>

메시지 큐 생산자

```C
struct msgbuf{
  long msgtype;
  char mtext[256];
  char myname[16];
  int seq;
}

void main() {
  key_t key_id;
  int i;
  struct msgbuf mybuf, rcvbuf
  char tempBuf[256];

  key_id = msgget((key_t)1234, IPC_CREAT|0666);
  if (key_id == -1)
  {
    perror("msgget error : ");
    exit(0);
  }

  printf("Key is %d\n", key_id);

  printf("your name : ");
  scanf("%s", tempBuf);
  strcpy(mybuf.myname, tempBuf);

  tempBuf[0] = '\0';

  printf("inser msg : ");
  scanf("%s", tempBuf);
  strcpy(mybuf.mtext, tempBuf);

  mybuf.seq = 0;
  i = 0;

  while(1)
  {
    // 짝수일 경우 msg type = 4
    // 홀수일 경우 msg type = 3
    if (i % 2 == 0)
      mybuf.msgtype = 4;
    else
      mybuf.msgtype = 3;

    mybuf.seq = i;

    // 메시지 전송
    if( msgsnd (key_id, (void *)&mybuf, sizeof(struct msgbuf), IPC_NOWAIT) == -1)
    {
      perror("msgsnd err : ");
    }
    printf("send %d\n", i);
    i++;
    sleep(1);

  }

}
```

- mybuf로 메시지 전송, 이 때 `msgtype`을 `i % 2` 가 0일 경우 4로, 그렇지 않을 경우 3으로 전송

```C

struct msgbuf  //구조체도 헤더파일에서 선언된 것과 겹치는 현상이 일어나서 컴파일이 되질 않습니다. 구조체 이름도 바꾸어야합니다.
{
    long msgtype;
    char mtext[256];
    char myname[16];
    int  seq;
};

int main(int argc, char **argv) {
  key_t key_id;
  struct msgbuf mybuf;
  int msgtype;//전역변수로 빼야 됩니다.

  // 아규먼트가 있을경우 msgtype 가 3인 메시지를 받아오고(홀수)
  // 아규먼트가 없을경우 msgtype 가 4인 메시지를 받아온다(짝수)
    if (argc == 2)
        msgtype = 3;
    else
        msgtype = 4;

    key_id = msgget(1234, IPC_CREAT|0666);

    if (key_id < 0) {
      perror("msgget err : ");
    }

    while(1) {
      if (msgrcv(key_id, (void *)&mybuf, sizeof(struct msgbuf), msgtype, 0) == -1){
        perror("msgrcv err : ");
        exit(0);
      }
      printf("%d\n", mybuf.seq)";
    }
    exit(0);
}

```
