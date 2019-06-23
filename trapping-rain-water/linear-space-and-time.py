from typing import List

# leetcode.com boilerplate
class Solution:
    def trap(self, height: List[int]) -> int:
        return water_capacity(height)


def water_capacity(heights):
    # to be filled out in subsequent loops
    max_to_left = [None for _ in heights]
    max_to_right = [None for _ in heights]

    current_max = 0
    for i, height in enumerate(heights):
        max_to_left[i] = current_max
        current_max = max(current_max, height)

    current_max = 0
    for i, height in enumerate(reversed(heights)):
        i = len(heights) - i - 1
        max_to_right[i] = current_max
        current_max = max(current_max, height)

    capacity = 0
    for height, left, right in zip(heights, max_to_left, max_to_right):
        volume = min(left, right) - height
        if volume > 0:
            capacity += volume

    return capacity
