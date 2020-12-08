import bisect
import math
import random

class Solution:
    def __init__(self, N, blacklist):
        self.n = N
        blacklist.sort()
        self.lookup = [(b - i, b + 1) for i, b in enumerate(blacklist)]

    def pick(self) -> int:
        r = random.randint(0, self.n - len(self.lookup) - 1)
        i = bisect.bisect_right(self.lookup, (r, math.inf))
        if i == 0:
            return r
        
        before, after = self.lookup[i - 1]
        return after + (r - before)

# Your Solution object will be instantiated and called as such:
# obj = Solution(N, blacklist)
# param_1 = obj.pick()
