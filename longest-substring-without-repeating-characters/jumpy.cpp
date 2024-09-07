#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int length_of_longest_substring_without_repeating_characters(const std::string& text) {
  switch (text.size()) {
  case 0: return 0;
  case 1: return 1;
  }
  // ASCII
  int last_seen[127];
  std::fill(std::begin(last_seen), std::end(last_seen), -1);
  int max_length = 1;
  int bottom = 0;

  for (int i = 0; i < int(text.size()); ++i) {
    const char ch = text[i];
    // std::cout << '@' << i << '(' << ch << ")\n";
    int& before = last_seen[ch];
    if (before == -1) {
      // std::cout << "  never seen before\n";
      max_length = std::max(max_length, i + 1 - bottom);
      // std::cout << "  max_length is now " << max_length << '\n';
    } else {
      // std::cout << "  seen before @" << before << '\n';
      max_length = std::max(max_length, i - before);
      // std::cout << "  max_length is now " << max_length << '\n';
      bottom = before + 1;
      // std::cout << "  bottom is now " << bottom << '\n';
      for (int& where : last_seen) {
        if (where < bottom) {
          where = -1;
        }
      }
    }
    before = i;
  }

  return max_length;
}

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
      return length_of_longest_substring_without_repeating_characters(s);
    }
};

int main() {
  std::string text;
  std::getline(std::cin, text);
  // std::cout << Solution().lengthOfLongestSubstring(text) << '\n';
}
