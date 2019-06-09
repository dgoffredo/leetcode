
import heapq
from typing import List


# leetcode.com boilerplate
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        return merge(lists)


def merge(lists):
    result = None
    last = None

    heap = [(node.val, i) for i, node in enumerate(lists) if node]
    heapq.heapify(heap)

    while heap:
        value, i = heapq.heappop(heap)

        # Create a new node and add it to the end of our answer.
        new_last = ListNode(value)
        if last is not None:
            last.next = new_last
        last = new_last
        if result is None:
            result = last

        # "Increment" the corresponding list, and add the next value to the
        # heap.
        lists[i] = lists[i].next
        if lists[i] is not None:
            heapq.heappush(heap, (lists[i].val, i))

    return result
        