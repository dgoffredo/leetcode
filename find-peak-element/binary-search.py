from typing import List


# leetcode.com boilerplate
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        return peak_index(nums)


def peak_index(heights):
    return peak_search(heights, 0, len(heights) - 1)


def peak_search(heights, low, high):
    if low == high:
        return low

    middle = low + (high - low) // 2
    height = heights[middle]
    left = height - 1 if middle == 0 else heights[middle - 1]
    right = height - 1 if middle == len(heights) -1 else heights[middle + 1]

    if height > left and height > right:
        return middle
    elif left > height:
        return peak_search(heights, low, middle)
    else:
        assert right > height
        return peak_search(heights, middle + 1, high)
