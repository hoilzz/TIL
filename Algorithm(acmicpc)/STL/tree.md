# std::map

map의 자료구조는 트리다. (정확하게 말하면 레드-블랙 트리다.)

## 트리 자료구조의 특징

노드를 **균형있게** 가지는 것이 성능에 유리하기 때문에, 기본 트리에서 변형된 트리 자료구조가 있다.

균형을 이룬 트리는 자료를 정해진 방식에 따라 분류하여 저장한다.

그러므로 일렬로 자료를 저장하는 LL에 비해 **검색이 빠르다.**

그렇지만 정해진 규칙에 따라 자료를 `삽입`, `삭제` 해야하기 때문에 구현이 복잡하다.

## map을 언제 사용할까

- 많은 자료를 `정렬`하여 저장하고 있고, `빠른 검색`을 필요로 할 때 자주 사용한다.

즉, 다음 조건일 때 사용하면 좋다.
	- 정렬해야 한다
	- 많은 자료를 저장하고, 검색이 빨라야 한다
	- 빈번하게 삽입, 삭제하지 않는다.

## map 사용 방법

```C
map <key 자료형, value 자료형> 변수 이름
```

정렬의 대상은 `key`를 대상으로 **오름 차순** 정렬한다.

내림 차순으로 하고 싶다면

```C
map <int, int, 비교 함수>
map <int, int greater<int>>
```

greater는 STL에 이미 정의되어 있는 템플릿이다.

## map의 주요 멤버들

- begin()
- empty()
- end() : 마지막 원소 다음의 반복자를 리턴
- erase
- find
- insert
- operator[] : 지정한 key 값으로 원소 `추가` 및 `접근`
- size

## 추가

추가시 insert 사용

```C
// pair <iterator, bool> insert(const value_type& _Val);
// iterator insert(iterator _Where, const value_type& _Val);

map <int, int> map1;

map1.insert(map<int, int>::value_type(1, 35));

map1.insert(make_pair(1,35));

// 두 번째 방식으로는 특정 위치에 추가할 수 있다.
// 첫 번째 위치에 key 1, value 35를 추가
map1.insert( map1.begin(), map< int, int >::value_type(1, 35) );
```

이미 추가된 key값을 또 추가할 수 없다.

```C
pair<map<int, int>::iterator, bool> Result;
Result = map1.insert(make_pair(1,35));
```

만약 그렇게 한다면 Result.second는 false이고, 성공 했다면 true다.

`operator[]`로 추가하기

```C
map1[10] = 90;
```

## 반복자 사용

begin(), end()와  역방향 반복자 rbegin(), rend()를 지원한다.

```C
map <int, int>::iterator IterPos;
for(IterPos = map1.begin(); Iter_Pos != map1.end(); ++Iter_Pos){
	cout<<Iter_Pos.second<<endl;
}
```

만약 map에서 비교함수 사용시, iterator도 같은 비교함수 사용해야 한다.


## 검색

map 에서는 key로 검색한다.

검색 성공시 반복자 리턴한다.

```C
// Iterator find(const Key& _Key);

map <int, int>::Iterator FindIter = map1.find(10);

if(FindIter != map1.end()){
	FindIter->second = 1000;
}
```

## 삭제

- `erase` : 특정 요소 삭제
- `clear` : 모든 요소 삭제

```C
// 1. Iterator erase(iterator _Where);
// 2. iterator erase(iterator _First, ieterator _Last);
// 3. size_type erase(const key_type& _Key);

// 1번 방법 : 2번째 요소 삭제
map1.erase(++map1.begin());

// 2번 방법 : 지정 구역 모두 삭제
map1.erase(map1.begin(), map1.end();)

// 3번 : key값 기준 삭제
map1.erase(10);
```

---

예제 코드

```C
#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Item{
    char Name[32];
    char Kind;
    int BuyMoney;
    int SkillCd;
};

int main() {

    map< char*, Item> Items;
    map<char*, Item>::iterator IterPos;

    Item Item1;

    strncpy(Item1.Name, "긴칼", 32);
    Item1.Kind = 1; Item1.BuyMoney = 200; Item1.SkillCd = 0;

    Item Item2;
    strncpy( Item2.Name, "성스러운 방패", 32 );
    Item2.Kind = 2; Item2.BuyMoney = 1000; Item2.SkillCd = 4;
    Item Item3;
    strncpy( Item3.Name, "해머", 32 );
    Item3.Kind = 1; Item3.BuyMoney = 500; Item3.SkillCd = 0;


    // Items에 아이템 추가
    Items.insert(map<char*, Item>::value_type(Item2.Name, Item2));
    Items.insert(make_pair(Item1.Name, Item1));

    // item 개수와 리스트를 불러오자

    if( Items.empty() == false){
        cout<<"item length : "<<Items.size()<<endl;
    }

    for(IterPos = Items.begin(); IterPos != Items.end(); ++IterPos){
        cout<<"이름 : "<<IterPos->first<<", 가격 : "<<IterPos->second.BuyMoney<<endl;
    }

    IterPos = Items.find("긴칼");
    if(IterPos == Items.end()){
        cout<<"긴칼 없수다"<<endl;
    }

    Item Item4;
    strncpy(Item4.Name, "로드호그의검", 32);
    Item4.Kind = 3; Item4.BuyMoney= 3000; Item4.SkillCd = 0;

    Items["호일검"] = Item4;

    cout<<Items["호일검"].Name<<endl;

    cout<<"올림차순으로 정렬된 map(key 자료형으로 string 사용)"<<endl;

    map<string, Item, less<string>> Items2;
    map<string, Item, less<string>>::iterator IterPos2;

    Items2.insert(map<string, Item>::value_type(Item2.Name, Item2));
    Items2.insert(make_pair(Item1.Name, Item1));

    Items2[Item3.Name] = Item3;

    for(IterPos2 = Items2.begin(); IterPos2 != Items2.end(); ++IterPos2){
        cout<<"이름 : "<<IterPos2->first<<", 가격 : "<<IterPos2->second.BuyMoney<<endl;
    }

    // 이번엔 내림차순으로 정렬해보자

    map <string, Item, greater<string>> Items3;
    map <string, Item, greater<string>>::iterator IterPos3;

    Items3.insert(map<string, Item>::value_type(Item1.Name, Item1));
    Items3[Item2.Name] = Item2;
    Items3["호일검"] = Item4;
    Items3.insert(make_pair(Item3.Name, Item3));

    for(IterPos3 = Items3.begin(); IterPos3 != Items3.end(); IterPos3++){
        cout<<"이번 검은 "<<IterPos3->first<<" 이고, 가격은 "<<IterPos3->second.BuyMoney<<endl;
    }
    return 0;
}
```
