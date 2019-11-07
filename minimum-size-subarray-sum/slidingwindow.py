from typing import List


class Solution:
    def minSubArrayLen(self, s: int, nums: List[int]) -> int:
        return do_the_thing(s, nums)


def do_the_thing(sum_threshold, numbers):
    length = len(numbers)

    if length == 0:
        return 0

    # Each subarray is numbers[i:j]
    i = 0  # index of first element in subarray
    j = 1  # index of one-past-the-last element in the subarray

    current_sum = numbers[0]
    shortest_so_far = None

    while True:
        if current_sum < sum_threshold:
            if j == length:
                # Can't expand any more; we're done.
                break

            # Expand
            current_sum += numbers[j]
            j += 1
        else:
            # The current subarray sums up to greater than or equal to
            # `sum_threshold`.  Possibly we have a new shortest candidate.
            if shortest_so_far is None or j - i < shortest_so_far:
                shortest_so_far = j - i

            # Try shrinking.  Maybe there's a subarray that still hits the sum
            # threshold but that is shorter.
            if i == j - 1:
                if j == length:
                    # Can't shrink because we're at the end.
                    break
                
                # Can't shrink, but can slide over.
                i += 1
                j += 1
                current_sum = numbers[i]
            else:
                # We can shrink.
                current_sum -= numbers[i]
                i += 1

    return shortest_so_far or 0
