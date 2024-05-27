#include <utility>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int deepest_leaves_sum(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  int sum = 0;
  int max_depth = 0;
  std::vector<std::pair<TreeNode*, int>> stack; // (node, depth)
  stack.emplace_back(root, 0);
  do {
    const auto [node, depth] = stack.back();
    stack.pop_back();

    if (node->left == nullptr && node->right == nullptr) {
      if (depth > max_depth) {
        max_depth = depth;
        sum = 0;
      }
      if (depth == max_depth) {
        sum += node->val;
      }
      continue;
    }
    
    if (node->left) {
      stack.emplace_back(node->left, depth + 1);
    }
    if (node->right) {
      stack.emplace_back(node->right, depth + 1);
    }
  } while (!stack.empty());

  return sum;
}
