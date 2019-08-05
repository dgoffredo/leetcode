
from math import inf
from typing import List


# leetcode.com boilerplate
class Solution:
    def mergeStones(self, stones: List[int], K: int) -> int:
        assert stones
        return min_score(stones, K)


def min_score(stones, k):
    if (len(stones) - 1) % (k - 1):
        return -1 # impossible to end up with one pile

    cache = {} # (i, j, p) -> min score, where i and j are inclusive indices
               # into `stones`, and `p` is a number of piles.

    prefix_sums = [0]
    for i in range(len(stones)):
        prefix_sums.append(prefix_sums[i] + stones[i])

    return min_score_cached(cache,
                            prefix_sums,
                            stones, 
                            k, 
                            i=0, 
                            j=(len(stones) - 1),
                            p=1)


def min_score_cached(cache, prefix_sums, stones, k, i, j, p):
    key = i, j, p
    value = cache.get(key)
    if value is not None:
        return value

    value = min_score_impl(cache, prefix_sums, stones, k, i, j, p)
    cache[key] = value
    return value


def min_score_impl(cache, prefix_sums, stones, k, i, j, p):
    assert i <= j

    def recur(i, j, p):
        return min_score_cached(cache, prefix_sums, stones, k, i, j, p)

    if j - i + 1 < p:
        return inf # can't make more piles than you have to start with

    if i == j:
        if p == 1:
            return 0 # making one pile out of itself costs just itself
        else:
            return inf # one pile can only make one pile

    stones_sum = prefix_sums[j + 1] - prefix_sums[i]

    if p == 1:
        # To make one pile (starting with more than one), we have to first get
        # k piles.
        return stones_sum + recur(i, j, k)

    # In the most general case, in order to get `p` piles out of `j - i + 1`
    # piles, we need to get `p - 1` piles out of one side and 1 pile out of the
    # other side.  We calculate this for every possible cut, and take the
    # minimum.  `m` is the "middle" index.
    return min(recur(i, m, p - 1) + recur(m + 1, j, 1) for m in range(i, j))
