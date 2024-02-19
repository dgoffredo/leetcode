#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

bool can_partition(vector<int>& nums);

class Solution {
public:
    bool canPartition(vector<int>& nums) {
      return can_partition(nums);       
    }
};

using Iter = vector<int>::const_iterator;

bool can_add_to(Iter begin, Iter end, int remaining) {
  auto found = std::upper_bound(begin, end, remaining);
  if (found == begin) {
    return false;
  }
  auto candidate = found - 1;
  if (*candidate == remaining) {
    return true;
  }
  return can_add_to(begin, candidate, remaining - *candidate) || can_add_to(begin, candidate, remaining);
}

bool can_partition(vector<int>& nums) {
  const int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 2) {
    return false;
  }

  std::sort(nums.begin(), nums.end());

  return can_add_to(nums.begin(), nums.end(), sum / 2);
}
