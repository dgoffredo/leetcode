
# leetcode.com boilerplate
from typing import List
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        return length_longest_increasing_subsequence(nums)


import bisect


def length_longest_increasing_subsequence(nums):
    """This uses the same principle as the "patience sort."  See wiki."""

    piles = []  # well, just the current top of each pile
    for num in nums:
        # `i` is the index of the lower bound of `num` in `piles`.
        i = bisect.bisect_left(piles, num)
        if i == len(piles):
            # no lower bound, so append to `piles`, which thus remains sorted.
            piles.append(num)
        else:
            # there's a lower bound.  It's either equal to `num` or greater
            # than it.  Update it so that it's equal to `num`.
            piles[i] = num

    # The length of the longest increasing subsequence is the number of piles
    # after having processed all of the input
    return len(piles)
