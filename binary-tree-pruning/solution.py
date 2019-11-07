
# Definition for a binary tree node.
# TODO: comment out when submitting to leetcode.com
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


from typing import Optional


class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if root is None:
            return None

        return prune_tree(root)


def prune_tree(root):
    def visit(node):
        # Base case: leaf.
        if node.left is None and node.right is None:
            return node if node.val else None

        # Left and right subtrees might be None to begin with, or if not might
        # become None after visitation.
        if node.left is not None:
            node.left = visit(node.left)
        
        if node.right is not None:
            node.right = visit(node.right)

        if node.left is None and node.right is None and not node.val:
            return None

        return node

    return visit(root)
