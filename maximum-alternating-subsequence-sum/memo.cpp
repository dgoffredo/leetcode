#include <algorithm>
#include <unordered_map>
#include <vector>

template <typename Key, typename Value>
using M = std::unordered_map<Key, Value>;

// sum -> i -> sign -> answer
using Cache = M<long long, M<int, M<int, int>>>;

long long max_alternating_sum(Cache& cache, int sum, int i, int sign, const std::vector<int>& nums) {
  if (i == int(nums.size())) {
    return sum;
  }

  auto& per_sign = cache[sum][i];
  const auto& entry = per_sign.find(sign);
  if (entry != per_sign.end()) {
    return entry->second;
  }
  return per_sign[sign] = std::max(
    // with `nums[i]`
    max_alternating_sum(cache, sum + sign * nums[i], i + 1, -sign, nums),
    // without `nums[i]`
    max_alternating_sum(cache, sum, i + 1, sign, nums)
  );
}

class Solution {
public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
      Cache cache;
      return max_alternating_sum(cache, 0, 0, +1, nums);
    }
};
