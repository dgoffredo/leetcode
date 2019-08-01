

from typing import List


# leetcode.com boilerplate
class Solution:
    def partitionDisjoint(self, A: List[int]) -> int:
        return partition_point(A)


def partition_point(values):
    assert len(values) >= 2

    end_index = 0
    max_seen_since = [values[0] for _ in values]

    for i, value in enumerate(values[1:], 1):
        if value < max_seen_since[end_index]:
            # We have to update our end index
            end_index = i

        max_seen_since[i] = max(max_seen_since[i - 1], value)

    return end_index + 1
