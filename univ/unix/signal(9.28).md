# signal
: software interrupt
- OS가 프로세스에게 특별한 상황을 알리기 위함
- CTRL+C로 종료 가능

## 기본 처리
1 종료            (정상 종료)
2 코어덤프 후 종료   (비정상 종료)
  - core file
3 중지            (일시 중지, 추후 프로그램 재실행 가능)
4 무시

## child process의 종료 상태 확인
  pid = wait(&status); // OS로부터 이 프로세스 상태를 확인할 수 있음

## 사용법

  int kill (pid_t pid, int sig)
  // 배열에 pid다들 잘 저장해놨다가 사용하면 개이득

  int raise()

### signal을 받을 process group 지정

int sigaction(int signo, const struct sigaction * act, struct sigaction * oact);
signal 수신시 원하는 행동 지정
SIGINT는 ctrl+c


## signal Handling :
1 default action (프로세스 종료)
2 무시 (받았는데 무시)
3 정의된 action (내가 원하는 action 정의 가능 ex. 시그널 받으면 이 함수 실행해)
  - sigaction 지정
  - sigaction 구조체에 먼저 action 지정.. 그래야 OS에 등록됨

### sigaction 구조체





struct sigaction {
  void (* sa_handler) (int); // 1 signo를 수신하면 수행할 함수 포인터, 즉 함수 이름
                             //
  sigset_t sa_mask;          // 2 여기 정의된 시그널들은, sa_handler에 의해 지정된 함수가 수행되는 동안 blokcing된다.
                             //   = 지정된 함수 실행할 때까지 시그널 안받겠다
  int sa_flags;              // handler

  void (* sa_sigaction) (int, siginfo_t * , void * )
}

2 부가 설명
  void A (int..) {...} // 만약 A 함수 수행시간 10분 걸림.. 이 떄 수행 중에 다른 시그널이 도착하면 그 다른 시그널을 수행하러감..
                       // 수행 후, 다시 돌아옴.. 시그널이 올 때마다 이걸 계속 반복
                       // 위 2줄의 과정이 싫다면, 즉 blocking 하길 원하면 2번 인자값에서 설정


## signal 집합 지정


지금 blocking 된 얘부터 하는게 아닌 번호가 빠른 얘부터


sigaction 의 3번째 인수 다 NULL로 하지만 쓸 때가 있음

3번째 인자 : 2번째 인자가 NULL이고, 세번째 위치에


## alarm signal

OS에게

실행 후, 10초후에 종료시키기 가능

child process는 알람 상속 안됨
(알람을 제외한 나머지는 상속이 된다.)


## sigprocmask

지금부터 signal blocking을 풀겠다.
1 signal 지금부터 blocking
2 지금부터 blocking 해제

3번째 인자는 보통 NULL, A 블락킹했다가 풀고 B 블락킹 하기이런거 반복할 때 사용

**NOTE**
sigaction mask
signal을 처리하는 도중에 다른 signal block


## pause

시그널 처리 action이 default면 정상종료







































# NOTE
## wait()함수

자식 프로세스가 종료된 다음에 자식 프로세스의 종료 상태를 가져올 때까지 부모 프로세스는 기다린다.

  pid_t wait (int * status)

- status : 자식프로세스가 종료될 때의 상태 정보 저장
  - 정상 종료 : status의 하위 8비트에는 0이 저장되며, 상위 8비트에는 프로세스가 종료되게한 exit() 함수의 인수가 저장됨.
  - 비정상 종료 : status의 하위 89비트에는 프로세스를 종료시킨 시그널의 번호가 저장되며, 상위 8비트에는 0이 저장됨

- return
  - 성공 : 자식 프로세스가 종료되면서 반환되는 값
  - 실패 : -1


## func testFunc (char * file_name, struct stat * buf)
char file_name [101];
struct stat * buf;

testFunc(file_name, &buf)
char * pointer를 인자로 받을 때, char형 배열을 인자로 넣을 때 *배열 이름 자체가 주소* 이기 때문에 &file_name할필요 없다.
