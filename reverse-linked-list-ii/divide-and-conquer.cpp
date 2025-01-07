#include <algorithm>
#include <cstddef>
#include <iterator>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class ListIter : public std::forward_iterator_tag {
    ListNode *node;

 public:
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using reference_type = int&;
    using const_reference_type = const int&;

    ListIter()
    : node(nullptr) {}

    explicit ListIter(ListNode *node)
    : node(node) {}

    ListIter& operator++() {
        if (node) {
            node = node->next;
        }
        return *this;
    }

    ListIter operator++(int) {
        ListIter result = *this;
        ++(*this);
        return result;
    }

    int& operator*() const {
        return node->val;
    }

    friend bool operator==(ListIter left, ListIter right) {
        return left.node == right.node;
    }

    friend bool operator!=(ListIter left, ListIter right) {
        return left.node != right.node;
    }
};

template <std::forward_iterator Iter>
void reverse(Iter begin, Iter end) {
    const auto size = std::distance(begin, end);
    if (size < 2) {
        return;
    }
    const auto middle = std::next(begin, size / 2);
    reverse(begin, middle);
    reverse(middle, end);
    std::rotate(begin, middle, end);
}

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        const ListIter begin(head);
        reverse(std::next(begin, left - 1), std::next(begin, right));
        return head;
    }
};

void free(ListNode *node) {
    if (node) {
        free(node->next);
        delete node;
    }
}

#include <iostream>

int main() {
    auto list = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    Solution().reverseBetween(list, 2, 4);
    for (auto node = list; node; node = node->next) {
        std::cout << node->val << '\n';
    }
    free(list);
}
