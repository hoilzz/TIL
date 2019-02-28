# 103-Binary Tree Zigzag Level Order Traversal

지그재그로 방문한 노드가 가진 값을 출력

문제에서의 지그재그란

1. 왼->오
2. 오->왼
3. 다시 1번으로

```
   3
   / \
  9  20
    /  \
   15   7
```

각 레벨 별로 1~3으로 방문하면 된다고 생각.

근데 제출하고나니 출력순서는 왼쪽에서 오른쪽이 되어야하는데,
오->왼 방향으로 방문시 오른쪽 얘부터 큐에 담기니까
그 다음, 왼->오 방향으로 방문시에 오른쪽 얘부터 출력하게됨.
그래서 아예 왼->오에서는 오른쪽부터(끝부터 시작) 시작하여 방문 값을 담은 다음 reverse로 해결.



```C
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector< vector<int>> result;

        if(!root) {
            return result;
        }
        
        queue <TreeNode *> q;
        int idx = 0;
        q.push(root);
        
        int direction = 1; // -1 : 왼쪽시작, 1 : 오른쪽 시작
        
        vector<int>temp;
        temp.push_back(root->val);
        result.push_back(temp);

        while(!q.empty()) {
            vector<int> subResult;
            int size = q.size();
            for(int i = 0; i < size; i++) {
                root = q.front();
                q.pop();
                
                // 오른시작
                if(direction == 1) {
                    if(root->right != NULL) {
                        q.push(root->right);
                        subResult.push_back(root->right->val);
                    }
                    if(root->left != NULL) {
                        q.push(root->left);
                        subResult.push_back(root->left->val);
                    }

                // 왼 시작
                } else {
                    if(root->right != NULL) {
                        q.push(root->right);
                        subResult.push_back(root->right->val);
                    }
                    if(root->left != NULL) {
                        q.push(root->left);
                        subResult.push_back(root->left->val);
                    }
                }
            }
            
            // 무조건 왼->오로 노출
            if(direction == -1) {
                reverse(subResult.begin(), subResult.end());
            }

            if(subResult.size() >= 1) {
                result.push_back(subResult);
            }

            direction *= -1;
        }

        return result;
    }
};
```




