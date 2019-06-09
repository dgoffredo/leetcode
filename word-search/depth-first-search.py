
"""naive solution

Try all relevant paths, each keeping track of where it came from so that it
doesn't retrace itself.
"""


from typing import List


# leetcode.com boilerplate
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        return grid_contains(board, word)


def grid_contains(grid, word):
    if len(grid) == 0 or len(grid[0]) == 0:
        return False

    M = len(grid)
    N = len(grid[0])

    return any(path_exists(grid, (i, j), word)
               for i in range(M) for j in range(N))


def path_exists(grid, point, suffix):
    i, j = point
    # print(f'Looking at {point} ({grid[i][j]}) for suffix {repr(suffix)}. History is {history}.')

    char = suffix[0]
    M = len(grid)
    N = len(grid[0])
    value = grid[i][j]

    if value != char:
        return False

    if len(suffix) == 1:
        return True

    grid[i][j] = chr(0) # mark it as visited

    for neighbor in candidate_points(point, M, N):
        if path_exists(grid, neighbor, suffix[1:]):
            grid[i][j] = value # put it back
            return True

    grid[i][j] = value # put it back
    return False


def candidate_points(point, M, N):
    i, j = point
    points = []

    # left
    if j > 0:
        points.append((i, j - 1))
    # above
    if i > 0:
        points.append((i - 1, j))
    # right
    if j < N - 1:
        points.append((i, j + 1))
    # below
    if i < M - 1:
        points.append((i + 1, j))

    return points
