#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
    unordered_map<int, unordered_map<int, bool>> table;
public:
    bool canPartition(vector<int>& nums) {
      const int sum = accumulate(nums.begin(), nums.end(), 0);
      if (sum % 2) {
        return false;
      }
      return can_partition(nums, nums.size(), sum / 2);
    }
    
    bool can_partition(const vector<int>& nums, int j, int sum) {
      auto [found, ptr] = lookup(j, sum);
      if (found) {
        return *ptr;
      }
      return *ptr = can_partition_impl(nums, j, sum);
    }

    bool can_partition_impl(const vector<int>& nums, int j, int sum) {
      switch (j) {
      case 0:
        return sum == 0;
      case 1:
        return nums[0] == sum;
      }
      return nums[j - 1] == sum || can_partition(nums, j - 1, sum - nums[j - 1]) || can_partition(nums, j - 1, sum);
    }

    pair<bool, bool*> lookup(int j, int sum) {
      auto sums = table.find(j);
      if (sums == table.end()) {
        bool *slot = &table[j][sum];
        return {false, slot};
      }
      auto found = sums->second.find(sum);
      if (found == sums->second.end()) {
        bool *slot = &sums->second[sum];
        return {false, slot};
      }
      return {true, &found->second};
    }
};
