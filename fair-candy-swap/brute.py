from typing import List


class Solution:
    def fairCandySwap(self, A: List[int], B: List[int]) -> List[int]:
        return fair_candy_swap(A, B)


# Let's try 100 million possibilities, but avoiding duplicates.
def fair_candy_swap(alice_bars, bob_bars):
    alice_total = sum(alice_bars)
    bob_total = sum(bob_bars)

    bobs = set(bob_bars)
    alices = set(alice_bars)

    for a in alices:
        for b in bobs:
            if alice_total - a + b == bob_total - b + a:
                return [a, b]
