#include <cassert>
#include <limits>
#include <string>

int number_of_copies(const std::string& text, const std::string& target) {
  int target_frequencies[26] = {};
  int text_frequencies[26] = {};

  for (char ch : target) {
    ++target_frequencies[ch - 'a'];
  }
  for (char ch : text) {
    ++text_frequencies[ch - 'a'];
  }

  int max_copies = std::numeric_limits<int>::max();
  for (char ch : target) {
    const int target_freq = target_frequencies[ch - 'a'];
    if (target_freq == 0) {
      continue;
    }
    const int text_freq = text_frequencies[ch - 'a'];
    const int quotient = text_freq / target_freq;
    if (quotient < max_copies) {
      max_copies = quotient;
    }
  }

  assert(max_copies != std::numeric_limits<int>::max());
  return max_copies;
}

class Solution {
public:
    int rearrangeCharacters(std::string s, std::string target) {
       return number_of_copies(s, target);
    }
};
