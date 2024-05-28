
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class FindElements {
    const TreeNode *tree;
public:
    FindElements(TreeNode* root)
    : tree(root) {
      root->val = 0;
      visit(root);
    }
    
    bool find(int target) {
       return lookup(tree, target);
    }

    bool lookup(const TreeNode *node, int target) const {
      if (!node || node->val > target) {
        return false;
      }
      return node->val == target || lookup(node->left, target) || lookup(node->right, target);
    }

    void visit(TreeNode* node) {
      const int val = node->val;
      if (node->left) {
        node->left->val = 2*val + 1;
        visit(node->left);
      }
      if (node->right) {
        node->right->val = 2*val + 2;
        visit(node->right);
      }
    }
};

