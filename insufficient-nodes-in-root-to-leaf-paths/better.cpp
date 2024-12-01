
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *walk(TreeNode *node, int limit, int parent_sum) {
  const int current_sum = parent_sum + node->val;

  if (!node->left && !node->right) {
    // We are a leaf.
    if (current_sum < limit) {
      return nullptr;
    }
    return node;
  }

  // We are not a leaf.
  if (node->left) {
    node->left = walk(node->left, limit, current_sum);
  }
  if (node->right) {
    node->right = walk(node->right, limit, current_sum);
  }

  if (!node->left && !node->right) {
    // We were pruned away.
    return nullptr;
  }
  return node;
}

TreeNode *prune(TreeNode *root, int limit) {
  if (root) {
    return walk(root, limit, 0);
  }
  return nullptr;
}

class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
      return prune(root, limit);
    }
};
