#include <cmath>
#include <string>

bool adjacent(char left, char right) {
  return std::abs(left - right) <= 1;
}

int minimum_number_of_replacements_to_eliminate_adjacent_adjacent_letters(const std::string& word) {
  if (word.size() < 2) {
    return 0;
  }

  int num_replacements = 0;
  for (int i = 0; i < int(word.size() - 1);) {
    if (adjacent(word[i], word[i + 1])) {
      ++num_replacements;
      i += 2;
    } else {
      ++i;
    }
  }

  return num_replacements;
}

class Solution {
public:
    int removeAlmostEqualCharacters(std::string word) {
       return minimum_number_of_replacements_to_eliminate_adjacent_adjacent_letters(word);
    }
};
