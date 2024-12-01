#include <algorithm>
#include <string>

int distance(const std::string& subject, const std::string& pattern) {
  using Iter = std::string::const_iterator;
  Iter s_iter = subject.begin();
  Iter p_iter = pattern.begin();
  while (p_iter != pattern.end()) {
    s_iter = std::find(s_iter, subject.end(), *p_iter);
    if (s_iter == subject.end()) {
      break;
    }
    ++s_iter;
    ++p_iter;
  }
  return pattern.end() - p_iter;
}

class Solution {
public:
    int appendCharacters(std::string s, std::string t) {
       return distance(s, t);
    }
};
