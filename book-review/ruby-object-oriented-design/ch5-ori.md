### 5장 오리타입으로 비용 줄이기

-------

객체지향 디자인의 목표는 코드의 수정 비용을 줄이는 것이다. 오리타입은 특정 클래스에 종속되지 않은 퍼블릭 인터페이스이다.

여러 클래스를 가로지르는 인터페이스는 클래스에 대한 값비싼 의존을 메시지에 대한 부드러운 의존으로 대치한다. 그리고 애플리케이션을 유연하게 만들어준다.

#### 5.1 오리타입 이해하기

프로그래밍 언어들은 '타입'이라는 개념을 통해 변수의 내용물이 어떤 카테고리에 속하는 지 설명한다.  변수의 내용물이 어떤 카테고리에 속하는지 알기 때문에, 어떻게 행동하는지 예측할 수 있다. 루비에서 객체들의 타입을 예측할 수 있는 이유는 객체들의 퍼블릭 인터페이스를 믿기 때문이다.

하지만 어떤 객체가 하나의 인터페이스에만 반응 할 수 있다고 생각할 필요는 없다. 서로 다른 여러개의 인터페이스를 구현할 수 있다. 클래스는 객체가  퍼블릭 인터페이스를 갖추기 위한 하나의 수단일 뿐이다. 애플리케이션은 특정 클래스에 종속되지 않은 퍼블릭 인터페이스를 정의할 수 있다. 이런 인터페이스는 여러 클래스들 사이를 관통해서 존재한다. 객체를 사용하는 사람은 모든 객체가 자신이 구현하고 있는 어떤 인터페이스 또는 모든 인터페이스에 맞춰 행동하리라 믿어도 된다. 

모든 상황에서 모든 객체가 예상한 바대로 움직인다고 믿을 수 있다면, 디자인은 무한한 가능성이 열리지만, 끔직한 디자인을 만들어 낼 수도 있다. 이런 유연성을 현명하게 사용하기 위해서는 클래스를 가로지르는 타입(across-class types) 즉, 오리 타입을 알아볼 수 있어야 한다. 오리타입은 명시적이고 잘 정리된 계약서 같은 퍼블릭 인터페이스를 가지고 있어야한다. 

##### 5.1.1 오리타입 무시하기

Trip의 prepare 메서드는 자신이 인자로 받은 mechanic 객체에게 prepare_bicycles메시지를 전송한다. 비록 인자의 이름이 mechanic이지만 이 인자가 품고 있는 객체는 어떤 클래스의 인스턴스라도 상관없다.

~~~ruby
class Trip
  attr_reader :bicycles, :customers, :vehicle

  # 무엇이든 이 'mechanic' 인자의 클래스가 될 수 있다.
  def prepare(mechanic)
    mechanic.prepare_bicycles(bicycles)
  end
  #...
end

# 우연히 아래 클래스의 인스턴스를 넘겨준다면, 제대로 동작할 것이다.
class Mechanic
  def prepare_bicycles(bicycles)
    bicycles.each {|bicycle| prepare_bicycle(bicycle)}
  end

  def prepare_bicycle(bicycle)
    #...
  end
end
~~~

Prepare 메서드 자체는 Mechanic 클래스에 의존하고 있지 않지만, prepare_bicycles이라는 메서드에 반응할 수 있는 객체를 수신해야 한다는 사실에 의존하고 있다. 

##### 5.1.2 문제가 더 복잡해지면

요구사항이 변경되었다고 생각해보자. 여행 준비에 mechanic뿐 아니라 trip coordinator와 driver도 필요하다면, 새로운 코드를 보자.

~~~ruby
class Trip
  attr_reader :bicycles, :customers, :vehicle

  def prepare(preparers)
    preparers.each do |preparer|
      case preparer
      when Mechanic
        preparer.prepare_bicycles(bicycles)
      when TripCoordinator
        preparer.buy_food(customers)
      when Driver
        preparer.gas_up(vehicle)
        preparer.fill_water_tank(vehicle)
      end
    end
  end
  #...
end

class TripCoordinator
  def buy_food(customers)
    #..
  end
end

class Driver
  def gas_up(vehicle)
    #..
  end

  def fill_water_tank(vehicle)
    #..
  end
end
~~~

 Trip의 prepare 메서드는 세 개의 서로 다른 클래스를 참조하고 있고, 각 클래스가 구현하고 있는 메서드의 이름을 정확히 알고 있으므로 위험도가 상승했다. 

변경사항이 생기고 prepare의 인자로 새로운 클래스의 인스턴스를 넘기면서 문제가 발생한다. 갑자기 prepare가 prepare_bicycle 메서드를 이해하지 못하는 객체를 처리해야만 한다. 인자들은 모두 다른 클래스의 인스턴스이고 서로다른 메서드들을 구현하고 있다. 클래스에 따라 다르게 작동 하는 case 구분을 가지고 객체들에게 메시지를 전송할 수 있지만, 이럴 경우 여기서 의존성의 분출을 목격하게 될 것이다. 먼 곳의 변경사항이 이 코드에 어떤 작용을 할 지 모른다.

더 심각한 것은 코딩 스타일 자체가 재생산 된다는 점이다. 또 다른 prepare가 필요해지면, case 구분에 맞는 새로운 when절을 추가하는 데 이러한 결과는 뻣뻣하고 유연하지 못한 애플리케이션이다. 

시퀀스 다이어그램은 코드보다 간단해야 한다. 

##### 5.1.3 오리타입 찾기

Trip의 prepare 메서드가 무엇을 원하는 지에 집중하자.prepare 메서드는 여행을 준비하고 싶어한다. 인자가 주어진 작업을 제대로 할 줄 안다고 prepare가 믿기만 하면 디자인은 훨씬 간단해질 것이다.

Prepare 메서드는 인자가 '여행을 준비하는 객체(Preparer)'이기만을 바랄 뿐이다. 기존의 클래스로부터 자유로워지고 오리타입을 만들어 냈다. 다음 문제는 prepare 메서드가 Preparer에게 어떤 메시지를 전송할지 생각하는 것이다. 

Trip의 prepare 메서드는 자신의 모든 인자가 Preparer이고 prepare_trip을 이해할 수 있기를 바란다.

여기서 Preparer는 구체적으로 존재하지 않고 추상적인 생각일 뿐이다. 

prepare_trip을 구현하고 있는 객체가 곧 Preparer이다. 반대로 얘기해서 Preparer와 협업하는 객체는 이 객체들이 Preparer의 퍼블릭 인터페이스를 구현하고 있다고 믿어야 한다. Mechanic, TripCoordeinator, Driver 모두 Preparer처럼 행동해야 한다. 

아래는 새로운 디자인을 적용한 결과이다.

~~~ruby
class Trip
  attr_reader :bicycles, :customers, :vehicle

  def prepare(preparers)
    preparers.each do |preparer|
      preparer.prepare_trip(self)
    end
  end
  #...
end

class TripCoordinator

  def prepare_trip(trip)
    buy_food(trip.customers)
  end

  def buy_food(customers)
    #..
  end
end

class Driver
  def prepare_trip(trip)
  vehicle = trip.vehicle
  gas_up(vehicle)
  fill_water_tank(vehicle)
  end

  def gas_up(vehicle)
    #..
  end

  def fill_water_tank(vehicle)
    #..
  end
end

class Mechanic
  def prepare_trip(trip)
    trip.bikes.each {|bike| prepare_bike(bike)}
  end

  def prepare_bike(bike)
    #...
  end
end

~~~

이제 prepare 메서드를 수정하지 않고도 새로운 Preparer를 추가할 수 있다.

##### 5.1.4 오리타입을 사용해서 얻을 수 있는 이점

첫번째 코드는 구체적이기 때문에 이해하기 쉽지만 확장하기에는 위험하다. 마지막 오리타입 코드는 보다 추상적이다. 코드를 이해하기에는 좀 더 노력을 요하지만, 대신 쉬운 확장성을 제공한다.

구체적인 코드는 이해하기 쉽지만 확장비용이 높다. 추상적인 코드는 처음에는 불명확해 보이지만 한번 이해하고 나면 수정하기가 훨씬 쉽다. 오리 타입을 사용하면 코드는 구체적인 것에서 추상적인 것으로 바뀐다. 확장하기는 쉬워지지만 그 아래 숨겨진 클래스를 파악하는데 더 많은 노력을 기울여야 한다.

객체를 클래스에 의해 정의된 것이 아니라 그 행동을 통해 정의된 것으로 이해하기 시작할 때, 우리는 표현력 있고 유연한 디자인의 새로운 세계에 발을 딛을 수 있다.

##### 폴리모피즘

객체지향 프로그래밍에서는 같은 메시지에 반응할 수 있는 여러 객체의 능력을 의미한다. 메시지의 송신자는 수신자의 클래스를 신경 쓸 필요가 없다. 수신자는 주어진 행동에 걸맞는 자신만의 행동을 제공한다.

폴리포피즘을 구현하기 위한 방법은 여러가지가 있는데 오리 타입도 그중 하나다. 폴리모픽 메서드는 암묵적인 합의를 중시한다. 송신자의 관점에서 보자면 이들은 상호 대체적이다. 폴리포픽 메서드를 구현하고 있는 모든 객체는 서로가 서로를 대체할 수 있다.

#### 5.2 오리 타입을 사용하는 코드 작성하기

오리 타입을 사용하려면 클래스를 가로지르는 인터페이스(across-class interface)를 사용하면 좋은 지점을 찾아내는 안목부터 갖춰야 한다. 

##### 5.2.1 숨겨진 오리 타입 알아보기

몇가지 일반적인 코딩 패턴은 오리 타입이 숨겨져 있다는 사실을 알려준다.

- 클래스에 따라 변경되는 case 구분
- Kind_of?와 is_a?
- responds_to?

##### 클래스에 따라 변경되는 case 구분

~~~ruby
class Trip
  attr_reader :bikes, :customers, :vehicle

  def prepare(preparers)
    preparers.each do |preparer|
      case preparer
      when Mechanic
        preparer.prepare_bikes(bikes)
      when TripCoordinator
        preparer.buy_food(customers)
      when Driver
        preparer.gas_up(vehicle)
        preparer.fill_water_tank(vehicle)
      end
    end
  end
~~~

이 패턴은 모든 Preparer가 무언가를 공유하고 있다는 사실을 바로 알려준다. 'prepare가 인자로부터 얻고자 하는 것은 무엇인가?' 이질문에 대한 답변이 우리가 전송해야하는 메시지를 알려준다. 

여기서 prepare 메서드는 자신의 인자가 여행을 준비하기를 바라고 있다. 따라서 prepare_trip 메서드를 가져야 한다.

##### kind_of?와 is_a?

Kind_of?와 is_a? 메시지는 클래스를 확인해준다. 

~~~ruby
if preparer.kind_of?(Mechanic)
	preparer.prepare_bicycles(bicycle)
elsif preparer.kind_of?(TripCoordinator)
	preparer.buy_food(customers)
elsif preparer.kind_of?(Driver)
	preparer.gas_up(vehicle)
    preparer.fill_water_tank(vehicle)
end
~~~

Kind_of?를 사용해도 클래스에 따라 변경되는 case 구분을 사용하는 것과 아무런 차이가 없다.

##### responds_to?

~~~ruby
if preparer.responds_to?(:prepare_bicycles)
	preparer.prepare_bicycles(bicycle)
elsif preparer.responds_to?(:buy_food)
	preparer.buy_food(customers)
elsif preparer.responds_to?(:gas_up)
	preparer.gas_up(vehicle)
    preparer.fill_water_tank(vehicle)
end
~~~

클래스 이름은 없어졌지만, 여전히 클래스에 얽혀있다. 이 메서드는 다른 객체를 믿기 보다는 명령하려 든다.



##### 5.2.2 오리타입을 믿기

위의 모든 코드는 '나는 네가 누구인지 알고 있고, 그렇기 때문에 네가 무엇을 하는지도 알고 있다'라고 말하고 있다.

이러한 지식은 객체에 대한 믿음이 부족하다는 사실을 말해줄 뿐이고, 협업 객체가 운신할 수 있는 폭을 줄인다. 코드를 수정하기 힘들고 의존성을 불러온다.

유연한 애플리케이션이란 믿을 수 있는 객체로 이루어져 있다.  코드를 보고 코드가 원하는 바를 이용해서 오리타입을 찾은 후, 인터페이스를 정의하자. 인터페이스를 필요로 하는 곳에 인터페이스를 구현하고 객체들이 제대로 행동하리라 믿어야한다.



##### 5.2.3 오리 타입 문서 작성하기

Preparer는 추상적이기에 강력한 디자인 도구가 될 수 있지만, 추상성 자체가 코드 속에서 오리 타입을 잘 드러나지 않게 만든다. 오리 타입을 만들었다면 문서도 작성하고 테스트 해야 한다. 



##### 5.2.4 오리 타입끼리 코드 공유하기

Preparer 오리 타입은 모두 자신의 클래스에 필요한 행동만 구현하고 있다. 하지만 오리타입을 사용하다보면 오리 타입 클래스끼리는 종종 같은 행동을 공유할 필요가 있다는 사실을 발견한다.7장에서 자세히 소개한다.



##### 5.2.5 현명하게 오리 타입 선택하기

아래 예시는 입력 값을 어떻게 처리해야 할지 결정하기 위해 클래스를 확인하고 있다. 

~~~ruby
# A convenience wrapper for <tt>find(:first, *args)</tt>. You can pass in all the
    # same arguments to this method as you can to <tt>find(:first)</tt>.
    def first(*args)
      if args.any?
        if args.first.kind_of?(Integer) || (loaded? && !args.first.kind_of?(Hash))
          limit(*args).to_a
        else
          apply_finder_options(args.first).first
        end
      else
        find_first
      end
    end
~~~

위의 예시와 앞의 코드 사이의 가장 큰 차이점은 코드가 확인하고 있는 클래스의 안정성이다. 예시에서는 Integer 와 Hash에 의존하기 있기 때문에 자기 자신보다 훨씬 안정적인 클래스에 의존하고 있는 것이다. 

여기서 알 수 있듯이, 새로운 오리타입을 만들지 말지는 우리의 판단에 달려있다. 오리 타입을 만들어서 불안정한 의존성을 줄일 수 있으면 만들면 된다.

위의 예시에서는 Integer, Hash 같은 기본 클래스(base Classes)를 의존하고 있고 이를 수정하려면 기본 클래스를 수정해야한다. 이러한 방법을 몽키패칭(monkey patching)이라고 하는데 대가가 아주 크므로 잘 생각하고 해야된다.

#### 5.4 요약

객체지향 디자인의 핵심에는 메시지가 있다. 메시지는 퍼블릭 인터페이스를 따라 객체들 사이를 오간다. 객체가 누구인지가 아니라 객체가 무엇을 하는지에 따라 가상의 타입을 만들어 낸다.

오리타입은 오리타입이 없었다면 발견하지 못했을 추상화를 볼 수 있게 해준다. 이 추상화에 의존할 때 애플리케이션의 위험성은 줄어들고 유연성을 증가한다.
