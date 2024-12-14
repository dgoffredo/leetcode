#include <algorithm>
#include <cassert>
#include <vector>

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *merge_lists(std::vector<ListNode*>& nodes);

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        return merge_lists(lists);
    }
};

struct ReverseByValue {
    bool operator()(const ListNode *left, const ListNode *right) const {
        assert(left);
        assert(right);
        return left->val > right->val;
    }
};

ListNode *merge_lists(std::vector<ListNode*>& nodes) {
    std::erase(nodes, nullptr);
    std::make_heap(nodes.begin(), nodes.end(), ReverseByValue{});

    ListNode *first = nullptr;
    ListNode *last = nullptr;
    while (!nodes.empty()) {
        std::pop_heap(nodes.begin(), nodes.end(), ReverseByValue{});
        ListNode *node = nodes.back();
        nodes.pop_back();
        if (node->next) {
            nodes.push_back(node->next);
            std::push_heap(nodes.begin(), nodes.end(), ReverseByValue{});
            node->next = nullptr;
        }
        if (!first) {
            first = last = node;
        } else {
            last = last->next = node;
        }
    }

    return first;
}
