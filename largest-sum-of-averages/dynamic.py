from functools import lru_cache
from typing import List

# leetcode.com boilerplate
class Solution:
    def largestSumOfAverages(self, A: List[int], K: int) -> float:
        return largest_sum_of_averages(A, K)


def largest_sum_of_averages(numbers, num_pieces):
    prefix_sums = [0]
    for i in range(len(numbers)):
        prefix_sums.append(prefix_sums[i] + numbers[i])

    def total(i, j):
        return prefix_sums[j + 1] - prefix_sums[i]

    @lru_cache(maxsize=None)
    def recur(i, j, k):
        assert i <= j
        assert k

        if k == 1:
            # print(f'({i}, {j}, {k}) -> {total(i, j) / (j - i + 1)}')
            return total(i, j) / (j - i + 1)

        # Otherwise, break it it half in every possible way.  Either side will
        # recur into 1 piece, while the other will recur into `k - 1` pieces.
        # Take the max possible out of all of these.  `m` is for "middle,"
        # with the convention that the cut is between index `m - 1` and `m`.
        # Also, keep in mind that `k > 1`.
        max_found = 0

        for m in range(i + 1, j + 1 - (k - 1) + 1):
            # print(f'({i}, {m - 1}, 1) + ({m}, {j}, {k - 1})')
            combo = recur(i, m - 1, 1) + recur(m, j, k - 1)
            if combo > max_found:
                max_found = combo

        for m in range(i + k, j + 1):
            # print(f'({i}, {m - 1}, {k - 1}) + ({m}, {j}, 1)')
            combo = recur(i, m - 1, k - 1) + recur(m, j, 1)
            if combo > max_found:
                max_found = combo

        # print(f'({i}, {j}, {k}) -> {max_found}')
        return max_found

    return recur(i=0, j=(len(numbers) - 1), k=num_pieces)
