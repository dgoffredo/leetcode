#include <set>
#include <vector>

int max_greatness(const std::vector<int>& v) {
  std::multiset<int> sorted{v.begin(), v.end()};

  int greatness = 0;
  for (const int n : v) {
    const auto it = sorted.upper_bound(n);
    if (it == sorted.end()) {
      continue;
    }
    sorted.erase(it);
    ++greatness;
  }

  return greatness;
}

class Solution {
public:
    int maximizeGreatness(const vector<int>& nums) {
      return max_greatness(nums);
    }
};
