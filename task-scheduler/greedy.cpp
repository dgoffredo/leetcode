#include <algorithm>
#include <iterator>
#include <vector>

int least_interval(const std::vector<char>& tasks, int n) {
  struct Entry {
    int remaining = 0;
    int previous = -1;
  } letters[26] = {};
  
  for (const char ch : tasks) {
    ++letters[ch - 'A'].remaining;
  }

  for (int count = 0;; ++count) {
    std::sort(std::begin(letters), std::end(letters), [](const Entry& left, const Entry& right) { return left.remaining > right.remaining; });
    if (letters[0].remaining == 0) {
      // no letters left to place
      return count;
    }

    for (auto& [remaining, previous] : letters) {
      if (remaining == 0) {
        // no need to look at subsequent letters
        break;
      }
      if (previous == -1 || count - previous >= n + 1) {
        // we can place this letter
        --remaining;
        previous = count;
        break;
      }
    }
  }
}

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
      return least_interval(tasks, n);      
    }
};
