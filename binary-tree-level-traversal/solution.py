# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        else:
            return level_order([root])


def level_order(nodes):
    result = []
    while nodes:
        result.append([node.val for node in nodes])
        kids = []
        for node in nodes:
            for kid in (node.left, node.right):
                if kid is not None:
                    kids.append(kid)
        nodes = kids
    
    return result
