# leetcode.com boilerplate
class Solution:
    def minDepth(self, root: TreeNode) -> int:
        if root is None:
            return 0
        else:
            return min_depth(root)


def min_depth(tree):
    if tree.left is None and tree.right is None:
        return 1

    possibilities = []
    if tree.left is not None:
        possibilities.append(1 + min_depth(tree.left))
    if tree.right is not None:
        possibilities.append(1 + min_depth(tree.right))

    return min(possibilities)
