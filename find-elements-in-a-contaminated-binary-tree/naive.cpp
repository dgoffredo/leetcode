#include <unordered_set>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class FindElements {
  std::unordered_set<int> values;
public:
    FindElements(TreeNode* root) {
      root->val = 0;
      visit(root);
    }
    
    bool find(int target) {
       return values.find(target) != values.end(); 
    }

    void visit(TreeNode* node) {
      const int val = node->val;
      values.insert(val);
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
