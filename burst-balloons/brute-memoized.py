
import functools
from typing import List


# leetcode.com boilerplate
class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        if nums:
            return max_score(tuple(nums))
        else:
            return 0


def without(values, index):
    return values[:index] + values[index + 1:]


def get(values, index):
    if index < 0 or index >= len(values):
        return 1
    else:
        return values[index]


def product(values, index):
    return get(values, index - 1) * get(values, index) * get(values, index + 1)


@functools.lru_cache(maxsize=None)
def max_score(balloons):
    if len(balloons) == 1:
        return balloons[0]

    return max(product(balloons, i) + max_score(without(balloons, i))
               for i in range(len(balloons)))
