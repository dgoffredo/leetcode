#include <optional>
#include <vector>

bool exists_increasing_3_sequence(const std::vector<int>& numbers) {
  if (numbers.size() < 3) {
    return false;
  }

  int largest_1_seq = numbers.back();
  std::optional<int> largest_2_seq;
  for (int i = numbers.size() - 2; i >= 0; --i) {
    const int n = numbers[i];
    if (largest_2_seq && *largest_2_seq > n) {
      return true;
    }
    if (largest_2_seq && *largest_2_seq < n && largest_1_seq > n) {
      largest_2_seq = n;
    }
    if (!largest_2_seq && largest_1_seq > n) {
      largest_2_seq = n;
    }
    if (n > largest_1_seq) {
      largest_1_seq = n;
    }
  }

  return false;
}

class Solution {
public:
    bool increasingTriplet(const std::vector<int>& nums) {
      return exists_increasing_3_sequence(nums);
    }
};
