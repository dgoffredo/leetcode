
# leetcode.com boilerplate
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        return num_taxi_paths(m, n)


def num_taxi_paths(m, n):
    distances = [1 for _ in range(m * n)]

    def get(i, j):
        return distances[i * n + j]

    def assign(i, j, value):
        distances[i * n + j] = value

    for j in range(n - 2, -1, -1):
        for i in range(m - 2, -1, -1):
            assign(i, j, get(i + 1, j) + get(i, j + 1))

    return get(0, 0)
