from typing import List


class Solution:
    def fairCandySwap(self, A: List[int], B: List[int]) -> List[int]:
        return fair_candy_swap(A, B)


def fair_candy_swap(alice_bars, bob_bars):
    alice_total = sum(alice_bars)
    bob_total = sum(bob_bars)

    bob_lookup = set(bob_bars)

    for a in alice_bars:
        # In order for exchanging this to work, Bob would have to give Alice
        # (in return) a bar of length `b`.  If Bob has such a bar, then we're
        # done.  Here's some algebra:
        #
        # alice_total - a + b == bob_total + a - b
        # alice_total - bob_total - a - a == - b - b
        # alice_total - bob_total - 2 a == - 2 b
        # b == (alice_total - bob_total - 2 a) / -2
        #
        b = (alice_total - bob_total - 2 * a) / -2
        if b in bob_lookup:
            return [a, b]
