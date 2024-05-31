#include <algorithm>
#include <vector>

std::vector<int> max_score_indices(std::vector<int>& nums) {
  const int N = nums.size();
  // `sums[i]` is the prefix some up to but not including `nums[i]`.
  std::vector<int> sums(N + 1);
  int total = 0;
  for (int i = 0; i < N; ++i) {
    total += nums[i];
    sums[i + 1] = total;
  }

  // Reuse the storage of `nums`, since we don't need it anymore.
  auto& division_score = nums;
  division_score.resize(N + 1);
  for (int i = 0; i <= N; ++i) {
    // (zeros before i) + (ones at or after i)
    division_score[i] = (i - sums[i]) + (total - sums[i]);
  }

  const int largest = *std::max_element(division_score.begin(), division_score.end());
  // Reuse the storage of `sums`, since we don't need it anymore.
  auto& indices = sums;
  indices.clear();
  for (int i = 0; i <= N; ++i) {
    if (division_score[i] == largest) {
      indices.push_back(i);
    }
  }

  return indices;
}

class Solution {
public:
    std::vector<int> maxScoreIndices(std::vector<int>& nums) {
      return max_score_indices(nums);
    }
};
