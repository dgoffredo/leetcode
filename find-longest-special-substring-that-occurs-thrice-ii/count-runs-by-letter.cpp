#include <algorithm>
#include <string>
#include <unordered_map>

int length_of_longest_special_substring_that_occurs_at_least_thrice(const std::string& text) {
  // letter -> {run_length: frequency}
  std::unordered_map<int, int> table[26];
  auto begin_run = text.begin();
  do {
    const char letter = *begin_run;
    auto end_run = std::find_if(
      begin_run + 1,
      text.end(),
      [letter](char ch) { return ch != letter; });
    for (auto iter = end_run; iter != begin_run; --iter) {
      table[letter - 'a'][iter - begin_run] += (end_run - iter) + 1;
    }
    begin_run = end_run;
  } while (begin_run != text.end());

  // Ignore all runs that occur fewer than three times, and keep track of the
  // longest run.
  int longest_special_run = -1;
  for (const auto& map : table) {
    for (const auto& [length, frequency] : map) {
      if (frequency < 3) {
        continue;
      }
      if (length > longest_special_run) {
        longest_special_run = length;
      }
    }
  }

  return longest_special_run;
}

class Solution {
public:
    int maximumLength(std::string text) {
      return length_of_longest_special_substring_that_occurs_at_least_thrice(text);
    }
};
