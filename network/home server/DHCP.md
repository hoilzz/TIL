# DHCP (Dynamic Host Configuration Protocol)

[!img](/img/nat.png)

IP를 수동으로 지정하는건 어떻게 하면 되는지 보자. 실제로 컴퓨터에 인터넷 연결 쓰기 위해서는 컴터의 IP를 직접 지정해줘야한다. 192.168.0.3으로 하면 될까? 위 그림에서 보다시피 이미 사용중이다.

IP addr은 같은 범위 내에서는 절대 중복되면 안된다.

[!img](/img/수동지정.png)

일단 수동으로 지정하는 방법을 살펴보자. 원래는 IP addr을 자동으로 얻기로 설정되어있다. IP addr을 지정하고..(192.168.0.4) 서브넷 마스크, 디폴트 게이트웨이를 지정하자. DNS도 지정하자.

DHCP server는 위 정보를 자동으로 지정해준다. 공유기는 DHCP server를 내장하고 있다. 동시에, 인터넷을 사용하는 디바이스들은 DHCP client가 기본 내장되어있다. 

공장에서 디바이스 제작시 기기를 인식할 수 있는 식별자를 가지고 있다. 이것은 **Mac Address** 혹은 물리적 주소라는 의미로 **Physical address**라는 용어를 사용한다. 

만약에 컴터를 공유기에 꽂거나 혹은 무선 접속하면 어떤일이 일어날까?

[!img](/img/dhcp-client.png)
[!img](/img/dhcp-server.png)
[!img](/img/dhcp-client2.png)
[!img](/img/dhcp-server2.png)

그래서 결국엔 192.168.0.4라는 IP를 클라이언트는 가질 수 있다. 

라우터는 작은 통신사. 통신사들도 똑같이 임대시간 등을 정해서 라우터에게 회선을 통해 IP를 할당해준다.