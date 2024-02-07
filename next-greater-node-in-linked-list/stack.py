from typing import List, Optional


class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def next_larger(values: List[int]) -> List[int]:
    stack = [0]
    answers = [0] * len(values)
    for i in range(len(values) - 1, -1, -1):
        value = values[i]
        while stack[-1] != 0 and value >= stack[-1]:
            stack.pop()
        answers[i] = stack[-1]
        stack.append(value)

    return answers


def next_larger_nodes(head: Optional[ListNode]) -> List[int]:
    values = []
    node = head
    while node is not None:
        values.append(node.val)
        node = node.next

    return next_larger(values)


class Solution:

    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        return next_larger_nodes(head)
