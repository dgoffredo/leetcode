#include <algorithm>
#include <string>

int min_steps(const std::string& left, const std::string& right) {
  int left_counts[26] = {};
  int right_counts[26] = {};

  for (const char letter : left) {
    ++left_counts[letter - 'a'];
  }
  for (const char letter : right) {
    ++right_counts[letter - 'a'];
  }

  int steps = 0;
  for (int i = 0; i < 26; ++i) {
    const int lesser = std::min(left_counts[i], right_counts[i]);
    steps += left_counts[i] - lesser;
    steps += right_counts[i] - lesser;
  }

  return steps;
}

class Solution {
public:
    int minSteps(std::string left, std::string right) {
       return min_steps(left, right);
    }
};
