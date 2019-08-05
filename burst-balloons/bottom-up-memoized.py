
import functools
from typing import List


# leetcode.com boilerplate
class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        if nums:
            return max_score(nums)
        else:
            return 0


def max_score(values):
    def get(i):
        if i < 0 or i >= len(values):
            return 1
        else:
            return values[i]

    @functools.lru_cache(maxsize=None)
    def max_score_impl(first, last):
        max_so_far = 0
        for i in range(first, last + 1):
            score = get(first - 1) * get(i) * get(last + 1)

            if i > first:
                score += max_score_impl(first, i - 1)
            if i < last:
                score += max_score_impl(i + 1, last)

            if score > max_so_far:
                max_so_far = score

        return max_so_far

    return max_score_impl(0, len(values) - 1)
