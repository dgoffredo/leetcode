from typing import List, Optional


class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def next_larger_nodes(head: Optional[ListNode]) -> List[int]:

    class Entry:

        def __init__(self, value: int):
            self.value = value
            self.answer_index = -1

    entries = []
    node = head
    while node is not None:
        entries.append(Entry(node.val))
        node = node.next

    if len(entries) == 0:
      return []

    answers = [0] * len(entries)
    answers[-1] = 0

    for i in range(len(entries) - 2, -1, -1):
        entry = entries[i]
        j = i + 1
        while True:
            other = entries[j]
            if entry.value < other.value:
                entry.answer_index = j
                break
            elif entry.value == other.value:
                entry.answer_index = other.answer_index
                break
            else:
                assert entry.value > other.value
                j = other.answer_index
                if j == -1:
                    break
        answers[i] = 0 if entry.answer_index == -1 else entries[
            entry.answer_index].value

    return answers


class Solution:

    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        return next_larger_nodes(head)
