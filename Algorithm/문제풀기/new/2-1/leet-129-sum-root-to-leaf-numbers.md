# 129. sum root to leaf numbers

각 노드는 1~9,0으로 되어있고 루트~리프 까지의 숫자들을 모아 1개의 숫자를 만든다. 각 leaf마다 숫자가 만들어지는데, 이 숫자들의 합을 구하라.

걍 DFS로 Leaf까지 도달했을 때 결과값을 누적하면된다.

재귀함수
  - task : 각 노드를 방문하여 전달받은 숫자 끝에 해당 노드 숫자를 뒤에 추가한다.
  - 이 task를 Left, Right로 재귀 방문
  - base case
    - 현재 방문한 노드의 left와 right가 null일 경우 값을 누적한다.

```C
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int result;
    // leaf노드까지 움직이며, 도달할 경우 string 완성
    // string 완성될 경우, str -> int해서 sum에 계속 누적
    void moveNode(TreeNode* node, string num) {
        // basecase
        if(node == NULL) {
            return;
        }
        if(node->left == NULL && node->right == NULL) {
            char chNum = (node->val + '0');
            
            int realNum = stoi(num + chNum);
            // cout<<realNum<<endl;
            this->result += realNum;
            return;
        }
        char chNum = (node->val + '0');
        moveNode(node->left, num + chNum);
        moveNode(node->right, num + chNum);
    }
    
    int sumNumbers(TreeNode* root) {
        moveNode(root, "");
        // cout<<"realNum: "<<this->result<<endl;
        return this->result;
    }
};
```

## 배운거

- 숫자를 뒤에 계속 붙여주는건 string을 이용하여, "" + (char)가 편하다.
- __string to int는 `stoi`를 사용.__
- __int to char는 (char) + '0' 을 사용하는게 맘편함__