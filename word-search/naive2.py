
"""naive solution

Try all relevant paths, each keeping track of where it came from so that it
doesn't retrace itself.
"""


from contextlib import contextmanager
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

    return any(path_exists(grid, set(), (i, j), word)
               for i in range(M) for j in range(N))


def path_exists(grid, history, point, suffix):
    i, j = point
    # print(f'Looking at {point} ({grid[i][j]}) for suffix {repr(suffix)}. History is {history}.')

    char = suffix[0]
    M = len(grid)
    N = len(grid[0])

    with add_point(history, point):
        if grid[i][j] != char:
            return False

        if len(suffix) == 1:
            return True

        return any(path_exists(grid, history, neighbor, suffix[1:])
                   for neighbor in candidate_points(history, point, M, N))


@contextmanager
def add_point(history, point):
    history.add(point)
    yield history
    history.remove(point)


def candidate_points(history, point, M, N):
    i, j = point
    points = set()

    # left
    if j > 0:
        points.add((i, j - 1))
    # above
    if i > 0:
        points.add((i - 1, j))
    # right
    if j < N - 1:
        points.add((i, j + 1))
    # below
    if i < M - 1:
        points.add((i + 1, j))

    result = points - history
    # print(f'Found candidate neighbor points: {result}.')
    return result