
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

from collections import defaultdict


class Solution:
    def verticalTraversal(self, root):
        if root is None:
            return None

        return vertical_traversal(root)


def vertical_traversal(root):
    # Each node gets a coordinate (depth, rightness), where the root has
    # (0, 0).  Each time you go to a child, depth += 1.  If you go left, then
    # rightness -= 1.  If you go right, then rightness += 1.

    by_rightness = defaultdict(list)  # rightness => [(depth, value) ...]

    def visit(node, depth, rightness):
        by_rightness[rightness].append((depth, node.val))
        
        if node.left is not None:
            visit(node.left, depth + 1, rightness - 1)

        if node.right is not None:
            visit(node.right, depth + 1, rightness + 1)

    visit(root, depth=0, rightness=0)

    result = []
    for rightness in sorted(by_rightness):
        depths_and_values = by_rightness[rightness]
        depths_and_values.sort()
        result.append([value for depth, value in depths_and_values])

    return result
