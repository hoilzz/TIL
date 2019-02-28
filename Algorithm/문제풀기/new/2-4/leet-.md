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

--------->
<--------
--------->

각 레벨 별로 이케 방문 하면 된다고 생각.

근데 제출하고나니 출력순서는 오->왼이 되면 안되는 거 확인. (방문만 지그재그고, 해당 레벨에서 출력은 왼->오)


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




