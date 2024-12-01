#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

bool equal_sum_partition_exists(const std::vector<int>& numbers, int partition_size) {
  const int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  const std::div_t div = std::div(sum, partition_size);
  if (div.rem) {
    return false;
  }
  const int target_sum = div.quot;
  // Each bin contains the amount remaining to reach `target_sum`.
  std::vector<int> bins(partition_size, target_sum);

  for (const int number : numbers) {
    auto found = std::find_if(bins.begin(), bins.end(), [=](int remaining) {
        return remaining >= number;
    });
    if (found == bins.end()) {
      return false;
    }
    *found -= number;
  }

  return std::find_if(bins.begin(), bins.end(), [](int number) { return number != 0; }) == bins.end();
}

class Solution {
public:
    bool canPartitionKSubsets(const std::vector<int>& nums, int k) {
       return equal_sum_partition_exists(nums, k);
    }
};
