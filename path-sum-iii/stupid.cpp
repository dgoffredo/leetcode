
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


#include <cstdint>
#include <vector>

int count_of_paths_having_sum(TreeNode *root, std::int64_t target_sum) {
  std::vector<std::int64_t> ancestor_sums;
  std::vector<TreeNode*> stack;
  int num_paths = 0;
  if (root == nullptr) {
    return num_paths;
  }

  stack.push_back(root);
  while (!stack.empty()) {
    TreeNode *const node = stack.back();
    if (!node) {
      // We were already visited. Pop the stacks.
      stack.pop_back();
      ancestor_sums.pop_back();
      continue;
    }

    if (ancestor_sums.empty()) {
      ancestor_sums.push_back(node->val);
    } else {
      ancestor_sums.push_back(ancestor_sums.back() + node->val);
    }

    // Check if there's a path ending at us whose sum is `target_sum`.
    if (ancestor_sums.back() == target_sum) {
      ++num_paths;
    }
    for (int i = 0; i < ancestor_sums.size() - 1; ++i) {
      if (ancestor_sums.back() - ancestor_sums[i] == target_sum) {
        ++num_paths;
      }
    }

    stack.back() = nullptr; // mark us as visited
    if (node->left) {
      stack.push_back(node->left);
    }
    if (node->right) {
      stack.push_back(node->right);
    }
  }

  return num_paths;
}

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
      return count_of_paths_having_sum(root, targetSum);
    }
};
