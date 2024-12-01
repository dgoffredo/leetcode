#include <algorithm>
#include <forward_list>
#include <iterator>

// leetcode.com boilerplate
#ifdef WITH_LISTNODE
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
#endif

std::forward_list<int> node2list(const ListNode* head);

ListNode* list2node(const std::forward_list<int>& values);

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) {
            return head;
        }

        std::forward_list<int> values = node2list(head);

        // A rotation `k` to the right is the same as a rotation `n - k` to the
        // left, where `n` is the length of the list.
        const int n = values.size();

        const auto newFirst = std::next(values.begin(), n - k % n);
        std::rotate(values.begin(), newFirst, values.end());

        return list2node(values);
    }
};

std::forward_list<int> node2list(const ListNode* head) {
    std::forward_list<int> values;

    while (head) {
        values.push_back(head->val);
        head = head->next;
    }

    return values;
}

ListNode* list2node(const std::forward_list<int>& values) {
    if (values.empty()) {
        return nullptr;
    }

    auto iter = values.begin();
    const auto head = new ListNode(*iter);
    ++iter;

    for (auto current = head; iter != values.end(); ++iter) {
        current = current->next = new ListNode(*iter);
    }

    return head;
}
