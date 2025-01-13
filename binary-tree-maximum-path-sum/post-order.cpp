#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Maxes {
    int leg;
    int path;
};

Maxes visit(TreeNode *node) {
    // `leg_options` are the possibilities for the largest "leg" sum rooted at
    // `node`, i.e. a direct ancestor chain rooted at `node`.
    int leg_options[3];
    int *leg_options_end = leg_options;
    *leg_options_end = node->val;
    ++leg_options_end;

    // `path_options` are the possibilities for the largest "path" sum in the
    // subtree rooted at `node`. It need not necessarily include `node`.
    int path_options[5];
    int *path_options_end = path_options;
    *path_options_end = node->val;
    ++path_options_end;

    // As we visit subtrees, we'll append possible values to `leg_options` and
    // `path_options`.

    int left_leg;
    int right_leg;

    if (node->left) {
        const Maxes left = visit(node->left);
        left_leg = left.leg;
        *leg_options_end = left_leg + node->val;
        ++leg_options_end;
        *path_options_end = left.path;
        ++path_options_end;
    }
    if (node->right) {
        const Maxes right = visit(node->right);
        right_leg = right.leg;
        *leg_options_end = right_leg + node->val;
        ++leg_options_end;
        *path_options_end = right.path;
        ++path_options_end;
    }
    if (node->right && node->left) {
        *path_options_end = left_leg + right_leg + node->val;
        ++path_options_end;
    }

    const int largest_leg_sum = *std::max_element(leg_options, leg_options_end);
    // The largest leg is a possibility for the largest path, so append it to
    // the array of possibilities. 
    *path_options_end = largest_leg_sum;
    ++path_options_end;

    return Maxes{
        .leg = largest_leg_sum,
        .path = *std::max_element(path_options, path_options_end)
    };
}

class Solution {
public:
    int maxPathSum(TreeNode* node) {
        const Maxes max = visit(node);
        return max.path;
    }
};
