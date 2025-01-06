#include <cstdint>
#include <optional>
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

std::uintptr_t to_int(const TreeNode *ptr, bool visited) {
    auto result = reinterpret_cast<std::uintptr_t>(ptr);
    result |= visited;
    return result;
}

std::pair<const TreeNode*, bool> from_int(std::uintptr_t combined) {
    const bool visited = combined & 1;
    const auto ptr = reinterpret_cast<const TreeNode*>((combined >> 1) << 1);
    return {ptr, visited};
}

bool is_binary_search_tree(const TreeNode *root) {
    if (!root) {
        return true;
    }
    std::vector<std::uintptr_t> stack{to_int(root, false)};
    std::optional<int> previous;
    do {
        const auto [node, seen] = from_int(stack.back());
        if (!seen && node->left) {
            stack.back() = to_int(node, true);
            stack.push_back(to_int(node->left, false));
            continue;
        }
        if (previous && *previous >= node->val) {
            return false;
        }
        previous = node->val;
        stack.pop_back();
        if (node->right) {
            stack.push_back(to_int(node->right, false));
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
