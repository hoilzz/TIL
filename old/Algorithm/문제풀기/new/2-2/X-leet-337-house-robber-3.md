# X-337-house-robber-3

재밌는 문제임. 틀림.

이진트리로 된 집들이 있다.
각 노드는 훔칠 수 있는 양을 값으로 가진다.
근데 훔칠 수 있는 조건은 다음과 같다.
- 인접한(directory-linked) 집을 털면 경찰에게 걸린다.

이 조건을 지키면서 최대로 털 수 있는 양을 구하자.

일단 단순하게 짝수 row(root 선택) VS 홀수 row(root 미선택) 두가지를 탐색하며 최대값 구하기로 했다. (하다보니 이건 모든 경우의 수를 구할 수 없다는 걸 알았다.)

```C
int dfs(TreeNode* currentNode, bool isPassRow) {
        int result = 0;
        if(currentNode == NULL) {
            return 0;
        }
        if(isPassRow) {
            // cout<<"currentNode->val: "<<currentNode->val<<endl;
            result += currentNode->val;
            // cout<<"result: "<<result<<endl;
        }
        //left
        result += dfs(currentNode->left, !isPassRow);
        //right
        result += dfs(currentNode->right, !isPassRow);
        
        // cout<<"result: "<<result<<endl;
        return result;
    }
    
    int rob(TreeNode* root) {
        // root 선택 : 홀수 row
        // int result = 0;
        // cout<<result<<endl;
        int r = dfs(root, true);
        int l = dfs(root, false);
        if(r > l) {
            return r;
        }
        return l;
        // cout<<"r : "<<r<<endl;
        // root 미선택 : 짝수 row
        // return r;
    }
```

--- 

모든 경우의 수를 탐색할 방법도 떠오르지 않아서 답 찾아봄.

```C
public class Solution {
    public int rob(TreeNode root) {
        if (root == null) {
            return 0;
        }
         
        if (root.left == null && root.right == null) {
            return root.val;
        }
         
        // case1: rob the root
        int leftMax = 0;
        int rightMax = 0;
         
        if (root.left != null) {
            leftMax = rob(root.left.left) + rob(root.left.right);
        }
         
        if (root.right != null) {
            rightMax = rob(root.right.left) + rob(root.right.right);
        }
        
        int maxRoot = root.val + leftMax + rightMax;
         
        // case 2: not rob the root
        leftMax = rob(root.left);
        rightMax = rob(root.right);
         
        int maxNoRoot = leftMax + rightMax;
         
        return Math.max(maxRoot, maxNoRoot);
    }
}
```

- 전체 케이스를 구하기 위해 재귀함수 잘 쪼갠듯...
- 개좋은문제인거같다..

```C
public class Solution {
    public int rob(TreeNode root) {
        if (root == null) {
            return 0;
        }
         
        int[] result = robHelper(root);
        return Math.max(result[0], result[1]);
    }
     
    private int[] robHelper(TreeNode root) {
        if (root == null) {
            return new int[2];
        }
         
        int[] left = robHelper(root.left);
        int[] right = robHelper(root.right);
         
        int[] curr = new int[2];
        curr[0] = root.val + left[1] + right[1];
        curr[1] = Math.max(left[0], left[1]) + Math.max(right[0], right[1]);
         
        return curr;
    }
}
```