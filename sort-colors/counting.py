from typing import List


class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        sort_colors(nums)


def sort_colors(nums):
    # Each num is one of 0, 1, or 2.  We can do one pass to count the amount
    # of each, and then write all the 0's, then all the 1's, and then all the
    # 2's.
    counts = [0, 0, 0]
    
    for n in nums:
        counts[n] += 1

    i = 0
    for color, color_count in enumerate(counts):
        for _ in range(color_count):
            nums[i] = color
            i += 1

    return nums # for easier repl testing
