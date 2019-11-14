import math
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        return max_profit(prices)


def max_profit(prices):
    """The plan is to compare the maximum of three options:
    
    1. Maximum difference between a price and any previous.
    2. Maximum sum of two non-overlapping differences.
    3. Zero

    (1) corresponds to doing one buy->sell, (2) corresponds to doing two
    buy->sells, and (3) corresponds to not being able to make any profit.  If
    you think about it (1) and (2) can be combined by doing a sliding separator
    of "where the second buy happens."
    """
    # A trick to getting the "maximum diff with something before this price"
    # is to note that the maximum difference `x - k` for some set of values for
    # `k` is just `x - min(k)`.  So, by keeping track of the smallest element
    # so far, just keep track of the smallest price seen so far, and at each
    # price `p`, take the max of the previously calculated maximum and of
    # `p - smallest_price_so_far`.

    # corner case
    if len(prices) < 2:
        return 0

    largest_diff = largest_diffs(prices)
    # TODO
    # The largest profit for a k-suffix is the _smallest_ profit going in
    # reverse up to k...


def largest_diffs(prices):
    # These initial values might introduce a spurious zeros, but it's fine.
    largest_diff = []
    smallest = prices[0]
    for price in prices:
        previous = largest_diff[-1] if len(largest_diff) > 0 else 0
        largest_diff.append(max([previous, price - smallest]))

        if price < smallest:
            smallest = price

    return largest_diff


def smallest_diffs(prices):
    smallest_diff = []
    largest = prices[0]
    # TODO: I don't like the edge case here, but since I'm just going to be
    #       negating these later, I don't think that zero does any harm, since
    #       negative zero is zero.
    for price in prices:
        previous = smallest_diff[-1] if len(smallest_diff) > 0 else math.inf
        smallest_diff.append(min([previous, price - largest]))

        if price > largest:
            largest = price

    return smallest_diff
