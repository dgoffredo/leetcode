
from typing import List


# Definition for a binary tree node.
class TreeNode:
   def __init__(self, x):
       self.val = x
       self.left = None
       self.right = None


class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> TreeNode:
        return build_tree(inorder, postorder)


def build_tree(in_order, post_order):
    def build_node(post_i, in_beg, in_end):
        print(f'build_node({post_i}, {in_beg}, {in_end}):')
        if in_beg == in_end:
            print(f'    empty, returning (None, {post_i + 1})')
            return None, post_i + 1

        value = post_order[post_i]
        in_root = in_order.index(value, in_beg, in_end)
        print(f'    value={value}, in_root={in_root}')
        right, right_i = build_node(post_i - 1, in_root + 1, in_end)
        left, left_i = build_node(right_i - 1, in_beg, in_root)

        result = TreeNode(value)
        result.left = left
        result.right = right

        print(f'    returning (TreeNode(...), {right_i})')

        return result, left_i

    assert len(post_order) == len(in_order)
    
    if len(post_order) == 0:
        return None
    else:
        root, _ = build_node(post_i=len(post_order) - 1,
                             in_beg=0,
                             in_end=len(in_order))
        return root
