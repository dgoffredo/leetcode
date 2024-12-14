#include <cassert>
#include <queue>
#include <vector>

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template <typename ListIter>
ListNode *merge_lists(ListIter begin, ListIter end);

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        return merge_lists(lists.begin(), lists.end());
    }
};

struct ReverseByValue {
    bool operator()(const ListNode *left, const ListNode *right) const {
        assert(left);
        assert(right);
        return left->val > right->val;
    }
};

template <typename ListIter>
ListNode *merge_lists(ListIter begin, ListIter end) {
    std::priority_queue<ListNode*, std::vector<ListNode*>, ReverseByValue> heap;
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter) {
            heap.push(*iter);
        }
    }

    ListNode *first = nullptr;
    ListNode *last = nullptr;
    while (!heap.empty()) {
        ListNode *node = heap.top();
        heap.pop();
        if (node->next) {
            heap.push(node->next);
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
