
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int grandsum(TreeNode *node, int grand_value, int parent_value) {
  if (node == nullptr) {
    return 0;
  }

  int sum = 0;
  if (grand_value % 2 == 0) {
    sum += node->val;
  }
  sum += grandsum(node->left, parent_value, node->val);
  sum += grandsum(node->right, parent_value, node->val);
  return sum;
}

class Solution {
public:
    int sumEvenGrandparent(TreeNode* root) {
      return grandsum(root, -1, -1);
    }
};
