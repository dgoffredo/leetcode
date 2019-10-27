
from typing import List

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        return num_connected_components(M)


def num_connected_components(adjacency_matrix):
    N = len(adjacency_matrix) # the number of kids (matrix is square)
    seen = set()

    def visit(kid):
        # Note how me look at _all_ classmates, not only those in the right
        # half triangle of the matrix.  This is subltly key to this algo.
        for classmate in range(N):
            if adjacency_matrix[kid][classmate] and classmate not in seen:
                # found a new friend
                seen.add(classmate)
                visit(classmate)

    num_cliques = 0
    for kid in range(N):
        if kid not in seen:
            visit(kid)
            num_cliques += 1

    return num_cliques
