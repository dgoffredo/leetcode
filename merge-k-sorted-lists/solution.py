
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

    while True:
        selection = smallest(lists)
        if selection is None:
            break

        value, i = selection

        # Create a new node and add it to the end of our answer.
        new_last = ListNode(value)
        if last is not None:
            last.next = new_last
        last = new_last
        if result is None:
            result = last

        # "Increment" the corresponding list.
        lists[i] = lists[i].next

    return result
        

    
def smallest(lists):
    options = [(item.val, i) for i, item in enumerate(lists) if item]
    if len(options) == 0:
        return None
    else:
        return min(options)
