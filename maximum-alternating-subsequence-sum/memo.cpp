#include <algorithm>
#include <iterator>
#include <vector>

// i -> {answer for sign=1, answer for sign=-1}
using Cache = long long[100'000 * 2];

long long max_alternating_sum(Cache& cache, int i, int sign, const std::vector<int>& nums) {
  if (i == int(nums.size())) {
    return 0;
  }

  long long& answer = *(cache + 2*i + (sign == 1));
  if (answer != -1) {
    return answer;
  }

  return answer = std::max(
    // with `nums[i]`
    sign * nums[i] + max_alternating_sum(cache, i + 1, -sign, nums),
    // without `nums[i]`
    max_alternating_sum(cache, i + 1, sign, nums)
  );
}

class Solution {
public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
      Cache cache;
      std::fill(std::begin(cache), std::end(cache), -1);
      return max_alternating_sum(cache, 0, +1, nums);
    }
};
