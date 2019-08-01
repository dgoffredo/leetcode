from typing import List

# leetcode.com boilerplate
class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        return num_taxi_paths(obstacleGrid)
        

def num_taxi_paths(obstacles):
    m = len(obstacles)
    n = len(obstacles[0])

    # If there's an obstacle at the end, then there's no way there.  If there
    # is no obstacle there, then we begin with "num_paths = 1" at that point.
    if obstacles[m - 1][n - 1]:
        return 0

    num_paths = [0 for _ in range((m + 1) * (n + 1))]

    def get(i, j):
        return num_paths[i * (n + 1) + j]

    def assign(i, j, value):
        num_paths[i * (n + 1) + j] = value

    for j in range(n - 1, -1, -1):
        for i in range(m - 1, -1, -1):
            if (i, j) == (m - 1, n - 1):
                assign(i, j, 1)
            elif obstacles[i][j]:
                assign(i, j, 0)
            else:
                assign(i, j, get(i + 1, j) + get(i, j + 1))

    return get(0, 0)
