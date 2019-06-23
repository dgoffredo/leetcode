# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# leetcode.com boilerplate
class Solution:
    def minDepth(self, root: TreeNode) -> int:
        return min_depth(root)


def min_depth(tree):
    lefty, righty = 0, 0
    if tree.left is not None:
        lefty = min_depth(tree.left) + 1
    if tree.right is not None:
        righty = min_depth(tree.right) + 1

    return min(lefty, righty)
