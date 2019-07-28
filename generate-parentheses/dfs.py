from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        return list(generate_trees(n))


def generate_trees(num_nodes):
    n = num_nodes

    def visit(opened, closed, so_far):
        if closed == n:
            yield so_far
            return

        if opened + closed < n:
            yield from visit(opened + 1, closed, so_far + '(')

        if opened > 0:
            yield from visit(opened - 1, closed + 1, so_far + ')')

    yield from visit(1, 0, '(')
