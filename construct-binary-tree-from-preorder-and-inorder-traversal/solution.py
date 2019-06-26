
from typing import List


# Definition for a binary tree node.
class TreeNode:
   def __init__(self, x):
       self.val = x
       self.left = None
       self.right = None


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        return build_tree(preorder, inorder)


def build_tree(pre_order, in_order):
    def build_node(pre_i, in_beg, in_end):
        print(f'build_node({pre_i}, {in_beg}, {in_end}):')
        if in_beg == in_end:
            print(f'    empty, returning (None, {pre_i - 1})')
            return None, pre_i - 1

        value = pre_order[pre_i]
        in_root = in_order.index(value, in_beg, in_end)
        print(f'    value={value}, in_root={in_root}')
        left, left_i = build_node(pre_i + 1, in_beg, in_root)
        right, right_i = build_node(left_i + 1, in_root + 1, in_end)

        result = TreeNode(value)
        result.left = left
        result.right = right

        print(f'    returning (TreeNode(...), {right_i})')

        return result, right_i

    assert len(pre_order) == len(in_order)
    
    if len(pre_order) == 0:
        return None
    else:
        root, _ = build_node(pre_i=0, in_beg=0, in_end=len(in_order))
        return root
