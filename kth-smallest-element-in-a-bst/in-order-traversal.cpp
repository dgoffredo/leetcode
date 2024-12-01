
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <cassert>

// Let's do it recursively. In-order with a stack is a slight pain.
TreeNode *kth_node_in_order(TreeNode *node, int &k) {
  if (node == nullptr) {
    return nullptr;
  }
  if (TreeNode *left_result = kth_node_in_order(node->left, k)) {
    return left_result;
  }
  if (--k == 0) {
    return node;
  }
  return kth_node_in_order(node->right, k);
}

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
      TreeNode *node = kth_node_in_order(root, k);
      assert(node);
      return node->val;
    }
};
