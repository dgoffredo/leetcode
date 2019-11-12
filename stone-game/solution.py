from typing import List


class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        num_stones = sum(piles)
        return max_stones(piles) > num_stones // 2


def max_stones(piles):
    cache = {}  # (i, j) -> max stones in subgame with piles[i:j]

    def recur(i, j, num_stones):
        cached = cache.get((i, j))
        if cached is not None:
            return cached

        if j == i + 1:
            cache[(i, j)] = piles[i]
            return piles[i]

        assert j > i + 1  # there are at least two piles

        take_left = num_stones - recur(i + 1, j, num_stones - piles[i])
        take_right = num_stones - recur(i, j - 1, num_stones - piles[j - 1])

        best = max([take_left, take_right])
        cache[(i, j)] = best
        return best       
        
    return recur(0, len(piles), sum(piles))
