# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        else:
            return zigzag_level_order([root])


def zigzag_level_order(nodes):
    result = []
    level = 0
    while nodes:
        if level % 2:
            source = reversed(nodes)
        else:
            source = nodes

        result.append([node.val for node in source])
        
        kids = []
        for node in nodes:
            for kid in (node.left, node.right):
                if kid is not None:
                    kids.append(kid)

        nodes = kids
        level += 1
    
    return result
