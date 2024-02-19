from typing import List


class Solution:
    def countDistinct(self, nums: List[int], k: int, p: int) -> int:
      return count_distinct(nums, k, p)


def count_distinct(nums, k, p):
  result = 0
  seen = set()
  for i in range(len(nums)):
    count = 0
    for j in range(i + 1, len(nums) + 1):
      # print('i:', i, ' j:', j, ' count:', count, ' result: ', result)
      subarray = nums[i:j]
      if subarray[-1] % p == 0:
        count += 1
      if count > k:
        break

      key = tuple(subarray)
      if key in seen:
        continue
      else:
        result += 1
        seen.add(key)
              
  return result
