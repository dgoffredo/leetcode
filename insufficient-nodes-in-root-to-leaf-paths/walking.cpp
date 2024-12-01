
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <algorithm>

struct AnnotatedNode {
  int value;
  int largest_path;
  AnnotatedNode *left, *right;
};

AnnotatedNode *annotate(TreeNode *node, int sum) {
  if (node == nullptr) {
    return nullptr;
  }
  AnnotatedNode* left = annotate(node->left, sum + node->val);
  AnnotatedNode* right = annotate(node->right, sum + node->val);
  int max = sum + node->val;
  if (left) {
    max = std::max(max, left->largest_path);
  }
  if (right) {
    max = std::max(max, right->largest_path);
  }
  return new AnnotatedNode{.value = node->val, .largest_path = max, .left = left, .right = right};
}

TreeNode *prune(AnnotatedNode *node, int limit) {
  if (node == nullptr || node->largest_path < limit) {
    return nullptr;
  }
  return new TreeNode(node->value, prune(node->left, limit), prune(node->right, limit));
}

TreeNode *prune(TreeNode *root, int limit) {
  AnnotatedNode *annotated_root = annotate(root, 0);
  return prune(annotated_root, limit);
}

class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
      return prune(root, limit);
    }
};