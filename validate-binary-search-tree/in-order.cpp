#include <optional>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool is_binary_search_tree(TreeNode *root) {
    if (!root) {
        return true;
    }
    std::vector<TreeNode*> stack{root};
    std::optional<int> previous;
    do {
        TreeNode *node = stack.back();
        if (node->left) {
            stack.push_back(node->left);
            node->left = nullptr;
            continue;
        }
        if (previous && *previous >= node->val) {
            return false;
        }
        previous = node->val;
        stack.pop_back();
        if (node->right) {
            stack.push_back(node->right);
        }
    } while (!stack.empty());

    return true;
}

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return is_binary_search_tree(root);
    }
};
