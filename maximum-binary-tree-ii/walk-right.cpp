struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *insert(TreeNode* node, int value) {
  if (node == nullptr) {
    return new TreeNode(value);
  }
  if (node->val < value) {
    return new TreeNode(value, node, nullptr);
  }
  node->right = insert(node->right, value);
  return node;
}

class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
      return insert(root, val);
    }
};
