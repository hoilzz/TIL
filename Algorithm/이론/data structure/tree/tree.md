# Tree

트리는 스택이나 큐와 같은 선형 구조가 아닌 비선형 자료구조다.

- 사이클이 없는 그래프
- 정점의 개수가 V라면, 간선의 개수는 V-1


## 트리의 표현

- 트리는 그래프이기 때문에, 그래프와 같은 방식으로 표현 가능하다.
- 트리의 모든 노드는 부모를 0개 혹은 1개만 가지기 때문에, 부모만 저장하는 방식으로 표현 가능하다.


- 이진 트리의 경우에는 배열로 표현 가능
  - 부모 노드가 x인 경우 자식의 노드는 `2 * x`, `2 * x + 1`로 나타내면 된다.
  - 또는 이차원 배열을 활용하여 `A[i][0]`에 i의 왼쪽 자식, `A[i][1]`에 오른쪽 자식 저장할 수 있다.

## 트리의 순회

그래프의 경우에는 DFS와 BFS가 있었다. 트리에서도 이 방법을 이용할 수 있다. 하지만, 트리에서만 사용할 수 있는 프리오더, 인오더, 포스트오더라는 트리에서만 사용할 수 있는 방법도 있다.

- 프리오더 : DFS와 비슷

[트리 순회](https://www.acmicpc.net/problem/1991) 문제를 풀어보자.

```C
typedef struct node {
    char left;
    char right;
}Vertex;

Vertex vertex[100];

void preOrder(char current){
  if(current == '.'){
    return;
  }
  printf("%c", current);

  preOrder(vertex[current].left);
  preOrder(vertex[current].right);
}

void inOrder(char current){
  if(current == '.'){
    return;
  }
  inOrder(vertex[current].left);
  printf("%c", current);
  inOrder(vertex[current].right);
}

void postOrder(char current){
  if(current=='.'){
    return;
  }
  postOrder(vertex[current].left);
  postOrder(vertex[current].right);
  printf("%c", current);
}

int main() {

  int n;
  char temp1, temp2, temp3;

  cin>>n;

  for (int i = 0; i<n; i++){
    cin>>temp1>>temp2>>temp3;

    vertex[temp1].left = temp2;
    vertex[temp1].right= temp3;
  }

  preOrder('A');
  printf("\n");
  inOrder('A');
  printf("\n");
  postOrder('A');
  
  return 0;
}
```

처음에 A,B,C,D 알파벳 순으로 입력되는 줄 알았다. 그래서 0:A, 1:B 이런식으로 생각하고 2차원 배열을 이용하여 `[0][1]`은 A의 왼쪽 자식, `[0][2]`는 오른쪽 자식으로 했다. 하지만 입력 값이 A,B,C,E,F,D와 같이 D보다 E,F가 먼저 나올 수 있다. 그래서 포인터처럼 연결되어있는 것처럼 구조체 배열['A'].left 에 연결된 단어 'B'를 할당한다. 그럼 구조체 배열['B'].left, .right를 통해 접근할 수 있다. 
마지막으로, 문제의 트리는 이진트리이고 자식 노드가 없을 경우 `.`으로 표현하므로 . 값이 나올 때마다 return하여 함수를 종료시켜주면 문제를 풀 수 있다. 

## 트리의 탐색

- DFS/BFS 알고리즘을 통해 트리를 탐색할 수 있다.
- 트리는 사이클이 존재하지 않는다. 임의의 두 정점 사이의 경로는 1개다. 따라서, BFS를 통해 최단거리를 구할 수 있다.
  - 이유: 경로가 1개라 찾은 경로가 최단 경로다.

## Summary

트리는 

- 그래프의 하위 집합이다.
- 사이클이 없다.
- 2차원 배열 혹은 리스트 등으로 표현 가능하다.
- 주로 계층 구조를 표현할 때 사용한다.