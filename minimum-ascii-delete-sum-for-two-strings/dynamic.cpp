#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int minimum_deletion_sum(const std::string& left, const std::string& right) {
  // Tabulate the minimum deletion sum `table[i][j]`, where `table[i][j]` is
  // the minimum deletion sum of `left[i:]` and `right[j:]`.
  // `previous` and `current` are columns.
  std::vector<int> previous(left.size() + 1);
  std::vector<int> current(left.size() + 1);
  for (int right_i = right.size(); right_i >= 0; --right_i) {
    for (int left_i = left.size(); left_i >= 0; --left_i) {
      // std::cout << "@(" << right_i << ", " << left_i << ") ("
      //     << (left_i == left.size() ? '_' : left[left_i])
      //     << ", " << (right_i == right.size() ? '_' : right[right_i]) << ")\n";
      if (left_i == left.size() && right_i == right.size()) {
        // std::cout << "    bottom left, so zero\n";
        current[left_i] = 0;
      } else if (right_i == right.size()) {
        // std::cout << "    rightmost column\n";
        current[left_i] = current[left_i + 1] + int(left[left_i]);
      } else if (left_i == left.size()) {
        // std::cout << "    bottommost row\n";
        current[left_i] = previous[left_i] + int(right[right_i]);
      } else {
        // std::cout << "    general case\n";
        const int options[] = {
          // remove from `left`
          int(left[left_i]) + current[left_i + 1],
          // remove from `right`
          int(right[right_i]) + previous[left_i],
          // remove from both
          ((left[left_i] == right[right_i]) ? 0 : int(left[left_i]) + int(right[right_i])) + previous[left_i + 1]
        };
        current[left_i] = *std::min_element(std::begin(options), std::end(options));
      }
      // std::cout << "    chose " << current[left_i] << '\n';
    }
    std::swap(current, previous);
  }
  return previous[0];
}

class Solution {
public:
    int minimumDeleteSum(const std::string& s1, const std::string& s2) {
       return minimum_deletion_sum(s1, s2);
    }
};

int main() {
  std::string left, right;
  std::cin >> left >> right;
  std::cout << Solution().minimumDeleteSum(left, right) << '\n';
}
