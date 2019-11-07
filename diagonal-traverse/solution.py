from typing import List


class Solution:
    def findDiagonalOrder(self, matrix: List[List[int]]) -> List[int]:
        return diagonal_zig_zags(matrix)


# This is the least efficient way to do this, but MEHHHHHHH
def diagonal_zig_zags(matrix):
    if len(matrix) == 0:
        return []
    
    assert matrix
    assert matrix[0]

    M = len(matrix)
    N = len(matrix[0])

    assert all(len(row) == N for row in matrix)

    result = []

    for diag_index in range(M + N):
        diag = get_diag(diag_index, matrix)
        if diag_index % 2 == 1:
            diag.reverse()
        result.extend(diag)

    return result


def get_diag(index, matrix):
    M = len(matrix)
    N = len(matrix[0])

    if index < M:
        i, j = index, 0
    else:
        i, j = M - 1, index - M + 1

    result = []
    while i >= 0 and j < N:
        result.append(matrix[i][j])
        i -= 1
        j += 1

    return result
