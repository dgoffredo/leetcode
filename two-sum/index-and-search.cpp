#include <unordered_map>
#include <vector>

std::vector<int> indices_of_elements_having_target_sum(std::vector<int>& nums, int target) {
  std::unordered_map<int, int> by_value; // value -> index in nums
  for (int i = 0; i < int(nums.size()); ++i) {
    by_value.emplace(nums[i], i);
  }
  for (int i = 0; /* we may assume there is a solution */ ; ++i) {
    const auto found = by_value.find(target - nums[i]);
    if (found != by_value.end() && found->second != i) {
      // Reuse `nums` for storing the answer.
      nums.clear();
      nums.push_back(i);
      nums.push_back(found->second);
      return std::move(nums);
    }
  }
}

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
      return indices_of_elements_having_target_sum(nums, target);
    }
};
