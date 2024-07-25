#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

long long minimum_removal(std::vector<int>& beans) {
  if (beans.size() < 2) {
    return 0;
  }

  std::sort(beans.begin(), beans.end(), std::greater<>{});

  long long removed = 0;
  int beans_per = beans[0];
  int num_bags = 0;

  for (auto iter = beans.begin(); iter != beans.end(); ++iter) {
    if (*iter == 0) {
      return removed;
    }
    auto next = std::upper_bound(iter, beans.end(), beans_per, std::greater<>{});
    if (next == beans.end()) {
      return removed;
    }
    num_bags += std::distance(iter, next); // TODO: is this off by one?
    if (num_bags * (beans_per - *next) > *next) {
      // Just drain "next" to zero and move on.
      removed += *next;
      continue;
    }
    // Take beans from each of the `num_bags` bags.
    removed += num_bags * (beans_per - *next);
    beans_per = *next;
    iter = next;
  }

  return removed;
}

class Solution {
public:
    long long minimumRemoval(std::vector<int>& beans) {
      return minimum_removal(beans);      
    }
};
