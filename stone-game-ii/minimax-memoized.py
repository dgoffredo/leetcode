
from typing import List


# leetcode.com boilerplate
class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        cache = {}
        return most_stones(cache, piles, sum(piles), 0, 1)


def most_stones(cache, piles, total, i, m):
    key = (i, m)
    cached = cache.get(key)
    if cached is not None:
        return cached

    value = most_stones_impl(cache, piles, total, i, m)
    cache[key] = value
    return value


def most_stones_impl(cache, piles, total, i, m):
    if i >= len(piles):
        return 0

    if 2*m >= len(piles) - i:
        # we can just take all of the remaining stones
        return total

    max_found = 0
    mine = 0

    max_piles = min(2*m, len(piles) - i)
    for x in range(1, max_piles + 1):
        j = i + x
        mine += piles[j - 1]
        new_total = total - mine
        new_m = max(m, x)

        their_next_move = most_stones(cache, piles, new_total, j, new_m)
        stones = mine + new_total - their_next_move
        if stones > max_found:
            max_found = stones

    return max_found
