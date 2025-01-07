import functools


def min_coins(amount, denominations):
    @functools.cache
    def coins(amount):
        if amount == 0:
            return 0
        options = [coins(amount - d) for d in denominations if d <= amount]
        valid_options = [x for x in options if x != -1]
        if len(valid_options) == 0:
            return -1
        return 1 + min(valid_options)
    return coins(amount) 


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        return min_coins(amount, coins)

