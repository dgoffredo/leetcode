#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <vector>

template <std::random_access_iterator Iter1, std::random_access_iterator Iter2>
int length_of_longest_common_subsequence(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) {
  // To use less memory, store calculations in a vector as long as the
  // _shorter_ of the two ranges.
  const auto len1 = std::distance(begin1, end1);
  const auto len2 = std::distance(begin2, end2);
  const auto [shortlen, longlen] = std::minmax(len1, len2);

  assert(shortlen > 0);

  const auto equal = [&](int i_shorter, int i_longer) {
    if (len1 == shortlen) {
      return *std::next(begin1, i_shorter) == *std::next(begin2, i_longer);
    }
    return *std::next(begin1, i_longer) == *std::next(begin2, i_shorter);
  };

  std::vector<int> scratch(shortlen + 1);

  for (int i_longer = longlen - 1; i_longer >= 0; --i_longer) {
    int southeast = 0;
    for (int i_shorter = shortlen - 1; i_shorter >= 0; --i_shorter) {
      int next_southeast = scratch[i_shorter];
      if (equal(i_shorter, i_longer)) {
        scratch[i_shorter] = 1 + southeast;
      } else {
        scratch[i_shorter] = std::max(scratch[i_shorter + 1], scratch[i_shorter]);
      }
      southeast = next_southeast;
    }
  }

  return scratch[0];
}

int length_of_longest_palindromic_subsequence(const std::string& text) {
  return length_of_longest_common_subsequence(
      text.begin(), text.end(),
      text.rbegin(), text.rend());
}

class Solution {
 public:
  int longestPalindromeSubseq(const std::string& text) {
      return length_of_longest_palindromic_subsequence(text);
  }
};

