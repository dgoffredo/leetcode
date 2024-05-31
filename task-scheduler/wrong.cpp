#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

int least_interval(const std::vector<char>& tasks, int n) {
  // `A` for "alphabet size"
  constexpr int A = 26;
  int total_remaining = tasks.size();
  int remaining[A] = {};
  for (const char ch : tasks) {
    ++remaining[ch - 'A'];
  }

  int previous[A];
  // `-1` means "hasn't been placed yet.
  std::fill(std::begin(previous), std::end(previous), -1);

  int count = 0;
  while (total_remaining) {
next:
    // First handle a "cooled down" letter, if possible.
    for (int ch = 0; ch < A; ++ch) {
      if (remaining[ch] == 0) {
        continue;
      }
      if (previous[ch] == -1) {
        continue;
      }
      if (count - previous[ch] >= n + 1) {
        previous[ch] = count;
        ++count;
        --remaining[ch];
        --total_remaining;
        goto next;
      }
    }

    // Otherwise, handle a never-placed-before letter, if possible.
    for (int ch = 0; ch < A; ++ch) {
      if (remaining[ch] == 0) {
        continue;
      }
      if (previous[ch] != -1) {
        continue;
      }
      previous[ch] = count;
      ++count;
      --remaining[ch];
      --total_remaining;
      goto next;
    }

    // Otherwise, leave this slot blank.
    ++count;
  }

  return count;
}

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
      return least_interval(tasks, n);      
    }
};
