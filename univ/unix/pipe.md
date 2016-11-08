
## pipe

> pipe(filedes[2])
filedes[0]:읽기용
filedes[1]:쓰기용
process당 open file 수, 시스템 내의 file수 제한

### 특성
- FIFO처리
- lseek 작동 ㄴㄴ
- fork()에 의해 상속 가능
- pipe를 이용한 단방향 통신 (부모 -> 자식)
  - pipe 생성
  - fork()에 의해 자식 생성 & pipe 복사
  - 부모 읽기용, 자식 쓰기용 pipe를 close

#### pipe를 이용한 양방향 통신
- pipe 2개 생성
- fork()에 의해 자식 생성 & pipe 2개 복사
  - pipe1 : 부모 읽기용, 자식은 쓰기용 pipe를 close
  - pipe2 : 부모 쓰기용, 자식은 읽기용 pipe를 close
- block read : pipe가 비어있는 경우
- blocking write : pipe가 꽉찬 경우

#### pipe 닫기
- 쓰기 전용 pipe 닫기
  - 다른 writer가 없는 경우, read를 위해 기다리던 process들에게 0을 return(EOF와 같은 효과)
- 읽기 전용 pipe 닫기
  - 더 이상 reader가 없으면, writer들은 SIGPIPE signal 받음
  - 핸들링 되지 않으면 process 종료
  - 핸들링 되면 처리 후, -1을 리턴

#### non blocking
여러 pipe를 차례로 polling 하는 경우

```C
fcntl(fd, F_SETFL, O_NONBLOCK);
```
- fd가 쓰기 전용이고, pipe가 차면 blocking 없이 즉시 -1을 return
- 읽기 전용인 경우, pipe 비어있으면 즉시 -1 return
