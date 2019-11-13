import bisect
from typing import List


class Solution:
    def maxProfitAssignment(self,
                            difficulty: List[int],
                            profit: List[int],
                            worker: List[int]) -> int:
        return max_profit(difficulty, profit, worker)


def max_profit(job_difficulties, job_profits, worker_abilities):
    """The plan is to sort by difficulty and then have a new list that
    has (difficulty, max profit at or below this difficulty).  Then you do a
    binary search into this to get the profit for a particular worker.  Loop
    over the workers and add up the profits to get the answer.
    """
    assert len(job_difficulties) == len(job_profits)
    assert len(job_difficulties) > 0

    by_difficulty = sorted(zip(job_difficulties, job_profits),
                           key=lambda x: x[0])

    best_seen = 0
    current_difficulty = by_difficulty[0][0]
    max_profits = []
    for difficulty, profit in by_difficulty:
        if difficulty != current_difficulty:
            max_profits.append((current_difficulty, best_seen))
            current_difficulty = difficulty

        if best_seen < profit:
            best_seen = profit

    # The largest difficulty will not have been added to `max_profits` yet.
    max_profits.append((current_difficulty, best_seen))

    # print('by_difficulty:', by_difficulty)
    # print('max_profits:', max_profits)

    # Now a binary search (lower bound, i.e. bisect_right, i.e. bisect) for
    # the largest difficulty less than or equal to a worker's ability will
    # allow us to find the corresponding largest profit that the worker could
    # get with his ability.
    total_profit = 0
    infinity = 10**6  # per the limits described in the problem statement
    for ability in worker_abilities:
        i = bisect.bisect(max_profits, (ability, infinity))
        # print('worker with ability', ability, 'yields index', i)
        
        # Special case: if i == 0, then the worker can't do any job
        # (sorry, buddy), so he contributes nothing to the total_profit.
        if i != 0:
            # Otherwise, index i - 1 is the greatest difficulty not greater
            # than the worker's ability.
            _, profit = max_profits[i - 1]
            total_profit += profit

    return total_profit
