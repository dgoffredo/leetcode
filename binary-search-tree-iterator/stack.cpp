#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator {
    std::vector<const TreeNode*> ancestors;
public:
    BSTIterator(const TreeNode* root) {
        for (const TreeNode *node = root; node; node = node->left) {
            ancestors.push_back(node);
        }
    }
    
    int next() {
       const int result = ancestors.back()->val;
        advance();
        return result;
    }
    
    bool hasNext() {
       return !ancestors.empty(); 
    }

private:
    void advance() {
        const TreeNode *node = ancestors.back();
        if (node->right) {
            node = node->right;
            do {
                ancestors.push_back(node);
                node = node->left;
            } while (node);
            return;
        }

        ancestors.pop_back();
        while (!ancestors.empty() && node == ancestors.back()->right) {
            node = ancestors.back();
            ancestors.pop_back();
        }
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
