#include <algorithm>
#include <cassert>
#include <string>

int min_swaps(std::string from, const std::string& to) {
  int swaps = 0;
  auto iter = from.begin();
  for (;;) {
    // The `i` prefixes mean "iterator".
    const auto [ifrom, ito] = std::mismatch(iter, from.end(), to.begin() + (iter - from.begin()));
    if (ifrom == from.end()) {
      return swaps;
    }
    auto inew = std::find(ifrom + 1, from.end(), *ito);
    assert(inew != from.end());
    // `inew` points to the element in `from` that we need to swap into place.
    while (inew != ifrom) {
      std::iter_swap(inew - 1, inew);
      --inew;
      ++swaps;
    }
    iter = ifrom + 1;
  }
}

int min_swaps_to_kth_wonderful(std::string num, int k) {
  std::string wonderful = num;
  for (int i = 0; i < k; ++i) {
    std::next_permutation(wonderful.begin(), wonderful.end());
  }

  return min_swaps(std::move(num), wonderful);
} 

class Solution {
public:
    int getMinSwaps(std::string num, int k) {
       return min_swaps_to_kth_wonderful(std::move(num), k); 
    }
};
