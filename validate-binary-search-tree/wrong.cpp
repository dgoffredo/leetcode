#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool is_binary_search_tree(const TreeNode *root) {
    if (!root) {
        return true;
    }
    std::vector<const TreeNode*> stack{root};
    do {
        const TreeNode *const node = stack.back();
        stack.pop_back();
        if (node->left) {
            if (!(node->left->val < node->val)) {
                return false;
            }
            stack.push_back(node->left);
        }
        if (node->right) {
            if (!(node->val < node->right->val)) {
                return false;
            }
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
