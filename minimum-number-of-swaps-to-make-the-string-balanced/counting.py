class Solution:
    def minSwaps(self, s: str) -> int:
      opens, closes, swaps = 0, 0, 0
      for ch in s:
        if ch == '[':
          opens += 1
        elif ch == ']':
          closes += 1
        if closes > opens:
          swaps += 1
          closes -= 1
          opens += 1
      return swaps
