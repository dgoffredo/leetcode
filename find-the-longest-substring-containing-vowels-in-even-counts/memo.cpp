#include <algorithm>
#include <bitset>
#include <string>
#include <unordered_map>

int length_of_longest_substring_having_even_number_of_each_vowel(const std::string& text) {
  int max = 0; // this will be the return value

  // memo :: (bitset) -> (index of last character in prefix)
  std::unordered_map<unsigned long, int> memo;
  std::bitset<5> parities;

  for (int i = 0; i < int(text.size()); ++i) {
    // a, e, i, o, u (forget y)
    switch (text[i]) {
    case 'a': parities ^= (1 << 0); break;
    case 'e': parities ^= (1 << 1); break;
    case 'i': parities ^= (1 << 2); break;
    case 'o': parities ^= (1 << 3); break;
    case 'u': parities ^= (1 << 4); break;
    }
    if (parities == 0) {
      max = std::max(max, i + 1);
    } else if (auto found = memo.find(parities.to_ulong()); found != memo.end()) {
      // One or more vowel has an odd count, but we've seen this pattern
      // before, so if we go from the previous place to here, the odd vowels
      // will cancel out.
      max = std::max(max, i + 1 - found->second);
    } else {
      memo[parities.to_ulong()] = i + 1;
    }
  }

  return max;
}

class Solution {
public:
    int findTheLongestSubstring(std::string s) {
       return length_of_longest_substring_having_even_number_of_each_vowel(s);
    }
};
