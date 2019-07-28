
from typing import List

# leetcode.com boilerplate
class Solution:
    def findMin(self, nums: List[int]) -> int:
        return special_min(nums)


def special_min(numbers):
    if len(numbers) == 1:
        return numbers[0]

    low = 0
    high = len(numbers) - 1
    while True:
        TODO