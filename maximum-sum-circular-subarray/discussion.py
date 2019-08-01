
from typing import List


# leetcode.com boilerplate
class Solution:
    def maxSubarraySumCircular(self, A: List[int]) -> int:
        max_sum = max_subarray_sum(A)
        if max_sum > 0:
            return max(max_sum, sum(A) - min_subarray_sum(A))
        else:
            return max_sum


def max_subarray_sum(numbers):
    assert len(numbers) > 0

    max_so_far = numbers[0]
    max_to_me = max(numbers[0], 0)

    for value in numbers[1:]:
        max_to_me += value
        if max_to_me > max_so_far:
            max_so_far = max_to_me

        if max_to_me < 0:
            max_to_me = 0

    return max_so_far


def min_subarray_sum(numbers):
    assert len(numbers) > 0

    min_so_far = numbers[0]
    min_to_me = min(numbers[0], 0)

    for value in numbers[1:]:
        min_to_me += value
        if min_to_me < min_so_far:
            min_so_far = min_to_me

        if min_to_me > 0:
            min_to_me = 0

    return min_so_far
