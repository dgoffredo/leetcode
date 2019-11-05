# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lcaDeepestLeaves(self, root: 'TreeNode') -> 'TreeNode':
        return lowest_common_ancestor_of_deepest_leaves(root)


def lowest_common_ancestor_of_deepest_leaves(root):
    # First, find the deepest leaves and record the path to each, where a path
    # is a string of "L"s and "R"s (lefts and rights). Then, find the largest
    # common prefix among these paths while simultaneously walking from the
    # root to find the corresponding node.
    
    greatest_depth = 0
    lowest_paths = []

    def visit(node, path):
        nonlocal greatest_depth

        if node.left is None and node.right is None:
            depth = len(path)

            if greatest_depth is None or depth > greatest_depth:
                greatest_depth = depth
                lowest_paths[::] = []

            if depth == greatest_depth:
                lowest_paths.append(path)

            return

        if node.left is not None:
            visit(node.left, path + 'L')

        if node.right is not None:
            visit(node.right, path + 'R')

    visit(root, '')

    # Now we've found a deepest depth and the paths to those leaves.  Find the
    # common path prefix while following the path.  Return the node we end up
    # at.
    node = root
    assert len(lowest_paths) > 0
    for i in range(greatest_depth):
        directions = set(path[i] for path in lowest_paths)
        if len(directions) > 1:
            break # found the part where we diverge

        direction, = directions
        if direction == 'L':
            node = node.left
        else:
            assert direction == 'R'
            node = node.right

    return node
