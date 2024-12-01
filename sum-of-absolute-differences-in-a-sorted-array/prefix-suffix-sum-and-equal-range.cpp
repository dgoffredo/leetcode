#include <algorithm>
#include <iterator>
#include <vector>

std::vector<int> map_sum_of_absolute_difference(const std::vector<int>& numbers) {
  std::vector<int> prefix_sum(numbers.size());
  int sum = 0;
  for (int i = 0; i < int(numbers.size()); ++i) {
    sum += numbers[i];
    prefix_sum[i] = sum;
  }
  sum = 0;
  std::vector<int> suffix_sum(numbers.size());
  for (int i = numbers.size() - 1; i >= 0; --i) {
    sum += numbers[i];
    suffix_sum[i] = sum;
  }

  std::vector<int> result(numbers.size());
  auto it = numbers.begin();
  while (it != numbers.end()) {
    const int value = *it;
    auto next = std::upper_bound(it, numbers.end(), value);
    const int i = std::distance(numbers.begin(), it);
    const int j = std::distance(numbers.begin(), next);
    int sum = 0;
    if (i > 0) {
      sum += i * value - prefix_sum[i - 1];
    }
    if (j < int(numbers.size())) {
      sum += suffix_sum[j] - value * (numbers.size() - j);
    }
    for (int k = i; k != j; ++k) {
      result[k] = sum;
    }
    it = next;
  }

  return result;
}

class Solution {
public:
    std::vector<int> getSumAbsoluteDifferences(std::vector<int>& nums) {
       return map_sum_of_absolute_difference(nums);
    }
};
