#include <algorithm>
#include <iterator>
#include <vector>

std::vector<int> map_sum_of_absolute_difference(const std::vector<int>& numbers) {
  std::vector<int> result(numbers.size());
  if (numbers.empty()) {
    return result;
  }

  int total_sum = 0;
  for (const int number : numbers) {
    total_sum += number;
  }

  int prefix_sum = 0;
  auto it = numbers.begin();
  do {
    const int value = *it;
    const auto next = std::upper_bound(numbers.begin(), numbers.end(), value);
    int sum = 0;
    if (it != numbers.begin()) {
      sum += std::distance(numbers.begin(), it) * value - prefix_sum;
    }
    if (next != numbers.end()) {
      const int suffix_sum = total_sum - prefix_sum - value * std::distance(it, next);
      sum += suffix_sum - value * std::distance(next, numbers.end());
    }
    while (it != next) {
      result[std::distance(numbers.begin(), it)] = sum;
      prefix_sum += value;
      ++it;
    }
  } while (it != numbers.end());

  return result;
}

class Solution {
public:
    std::vector<int> getSumAbsoluteDifferences(std::vector<int>& nums) {
       return map_sum_of_absolute_difference(nums);
    }
};

