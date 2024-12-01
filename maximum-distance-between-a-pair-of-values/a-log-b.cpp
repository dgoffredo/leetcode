#include <algorithm>
#include <iterator>
#include <vector>

int answer_to_contrived_problem(const std::vector<int>& left, const std::vector<int>& right) {
  int max_distance = 0;

  struct Backwards {
    bool operator()(int x, int y) const {
      return x > y;
    }
  };

  for (auto left_it = left.begin();
      std::distance(left.begin(), left_it) < int(right.size()) - max_distance && left_it != left.end();
      ++left_it) {
    const auto right_it = right.begin() + std::distance(left.begin(), left_it);
    auto righty = std::upper_bound(
      right_it,
      right.end(),
      *left_it,
      Backwards{});
    if (righty == right.begin()) {
      continue;
    }
    --righty;
    const int distance = std::distance(right_it, righty);
    if (*righty >= *left_it && distance > max_distance) {
      max_distance = distance;
    }
  }

  return max_distance;
}

class Solution {
public:
    int maxDistance(std::vector<int>& nums1, std::vector<int>& nums2) {
      return answer_to_contrived_problem(nums1, nums2);
    }
};
