#include <cassert>
#include <iterator>
#include <string>
#include <vector>

std::string choose_Mm(std::vector<int> digits) {
  for (int digit = 5; digit >= 0; --digit) {
    for (auto it = digits.begin(); it != digits.end(); ++it) {
      if (*it != digit) {
        continue;
      }
      digits.erase(it);
      assert(digits.size() == 1);
      return std::to_string(digit) + std::to_string(digits[0]);
    }
  }
  return "";
}

std::string choose_hMm(int H, std::vector<int> digits) {
  const int max = H == 2 ? 3 : 9;
  for (int digit = max; digit >= 0; --digit) {
    for (auto it = digits.begin(); it != digits.end(); ++it) {
      if (*it != digit) {
        continue;
      }
      auto remaining = digits;
      remaining.erase(remaining.begin() + std::distance(digits.begin(), it));
      std::string suffix = choose_Mm(std::move(remaining));
      if (!suffix.empty()) {
        return std::to_string(*it) + ":" + suffix;
      }
    }
  }
  return "";
}

std::string choose_HhMm(std::vector<int> digits) {
  for (int digit = 2; digit >= 0; --digit) {
    for (auto it = digits.begin(); it != digits.end(); ++it) {
      if (*it != digit) {
        continue;
      }
      auto remaining = digits;
      remaining.erase(remaining.begin() + std::distance(digits.begin(), it));
      std::string suffix = choose_hMm(*it, std::move(remaining));
      if (!suffix.empty()) {
        return std::to_string(*it) + suffix;
      }
    }
  }
  return "";
}

class Solution {
public:
    std::string largestTimeFromDigits(std::vector<int>& digits) {
       return choose_HhMm(std::move(digits));
    }
};
