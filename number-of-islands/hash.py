
from typing import List


# leetcode.com boilerplate
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        return num_islands(grid)


def num_islands(grid):
    if len(grid) == 0 or len(grid[0]) == 0:
        return 0

    def get(i, j):
        if i < len(grid) and j < len(grid[0]) and i >= 0 and j >= 0:
            return grid[i][j]
        else:
            return '0'

    latest_island = 0
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            # print('examining', i, j)
            if get(i, j) != '1':
                 # print('skipping', i, j)
                continue

            # We have a new island. Increment `latest_island` and flood fill to
            # mark all of the land on the island.
            latest_island += 1
            # print('latest_island incremented to', latest_island)
            def explore_island(i, j):
                # print('setting', i, j, 'to', latest_island)
                grid[i][j] = latest_island
                for a, b in [(i + 1, j), (i, j + 1), (i - 1, j), (i, j - 1)]:
                    if get(a, b) == '1':
                        explore_island(a, b)

            explore_island(i, j)

    return latest_island
