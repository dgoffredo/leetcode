#include <unordered_map>
#include <vector>

class Node {
public:
    int val = 0;
    std::vector<Node*> neighbors;
};

Node *clone(Node *start) {
  if (start == nullptr) {
    return start;
  }

  std::unordered_map<int, Node*> cache;
  const auto visit = [&cache](Node *node, auto&& recur) {
    const auto found = cache.find(node->val);
    if (found != cache.end()) {
      return found->second;
    }
    Node *copy = new Node;
    copy->val = node->val;
    cache.emplace(copy->val, copy);
    for (Node *neighbor : node->neighbors) {
      copy->neighbors.push_back(recur(neighbor, recur));
    }
    return copy;
  };
  return visit(start, visit);
}

class Solution {
public:
    Node* cloneGraph(Node* node) {
      return clone(node);
    }
};
