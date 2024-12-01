#include <algorithm>
#include <cctype>
// #include <iostream>
#include <string>
#include <vector>

std::vector<std::string> case_combinations(const std::string& text) {
  std::vector<std::string> combos;

  const auto is_digit = [](char ch) {
    return ch >= '0' && ch <= '9';
  };
  const int digits = std::count_if(text.begin(), text.end(), is_digit);
  const int letters = text.size() - digits;
  const int num_combos = 1 << letters;
  // std::cout << '\"' << text << "\" contains " << digits << " digits and " << letters << " letters.\n";
  std::string copy;
  for (int i = 0; i < num_combos; ++i) {
    copy = text;
    int mask = i;
    auto iter = copy.begin();
    for (;;) {
      iter = std::find_if_not(iter, copy.end(), is_digit);
      if (iter == copy.end()) {
        combos.push_back(copy);
        break;
      }
      if (mask & 1) {
        *iter = std::toupper(*iter);
      } else {
        *iter = std::tolower(*iter);
      }
      mask >>= 1;
      ++iter;
    }
  }

  return combos;
}

class Solution {
public:
    std::vector<std::string> letterCasePermutation(const std::string& text) {
        return case_combinations(text);
    }
};

// int main() {
//   std::string text;
//   std::vector<std::string> combos;
//   while (std::cin >> text) {
//     combos = Solution().letterCasePermutation(text);
//     for (const std::string& combo : combos) {
//       std::cout << " -> " << combo << '\n';
//     }
//   }
// }
