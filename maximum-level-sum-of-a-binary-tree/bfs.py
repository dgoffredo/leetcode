
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

# leetcode.com boilerplate
class Solution:
    def maxLevelSum(self, root) -> int:
        return level_with_max_sum(root)


from collections import deque


def level_with_max_sum(root):
    best = None
    todo = deque()
    current_level = 1
    current_sum = 0
    todo.appendleft((root, current_level))

    while todo:
        node, level = todo.pop()  # pops from the right

        if level != current_level:
            assert level == current_level + 1
            entry = (current_sum, -current_level)
            if best is None or entry > best:
                best = entry
            current_level += 1
            current_sum = 0

        current_sum += node.val

        if node.left is not None:
            todo.appendleft((node.left, level + 1))
        if node.right is not None:
            todo.appendleft((node.right, level + 1))

    return -max([best, (current_sum, -current_level)])[1]
