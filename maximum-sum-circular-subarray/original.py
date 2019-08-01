
from collections import deque
from typing import List


# leetcode.com boilerplate
class Solution:
    def maxSubarraySumCircular(self, A: List[int]) -> int:
        return max_subarray_sum(A + A, len(A))


def print(*args, **kwargs):
    pass


def max_subarray_sum(numbers, max_length):
    assert len(numbers) > 0
    assert max_length <= len(numbers)

    print(list(enumerate(numbers)))

    prefix_sum = list(numbers)
    for i in range(1, len(numbers)):
        prefix_sum[i] += prefix_sum[i - 1]

    print(list(enumerate(prefix_sum)))

    max_so_far = -30000 # minimum value according to problem description
    candidate_indices = deque()
    for i in range(len(numbers)):
        # TODO: first `while` loop could just be an `if`, right?
        while candidate_indices and i - candidate_indices[0] > max_length:
            print('(a) pop', candidate_indices[0])
            candidate_indices.popleft()

        while candidate_indices and prefix_sum[candidate_indices[-1]] > prefix_sum[i]:
            print('(b) pop', candidate_indices[-1])
            candidate_indices.pop()

        print('(c) push', i)
        candidate_indices.append(i)

        if i == candidate_indices[0]:
            # TODO: explain
            subarray_sum = numbers[i]
        else:
            subarray_sum = prefix_sum[i] - prefix_sum[candidate_indices[0]] 

        print(f'subarray_sum({candidate_indices[0]}, {i}) -> {subarray_sum}')

        if subarray_sum > max_so_far:
            max_so_far = subarray_sum

    return max_so_far
