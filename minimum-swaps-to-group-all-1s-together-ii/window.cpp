#include <algorithm>
#include <vector>

int min_swaps(const std::vector<int>& v) {
  const int n = v.size();
  const int ones = std::count(v.begin(), v.end(), 1);
  if (ones < 2) {
    return 0;
  }
  int zeros = std::count(v.begin(), v.begin() + ones, 0);
  int min_zeros = zeros;
  const auto increment = [n](int& offset) {
    offset = (offset + 1) % n;
  };
  int first = 0;  // an offset
  int last = ones - 1;  // an offset
  int first_before;  // value
  for (;;) {
    first_before = v[first];
    increment(first);
    if (first == 0) {
      return min_zeros;
    }
    increment(last);
    // If the value changed on either end, we might need to increment or
    // decrement the number of zeros in the window. 
    zeros += (v[last] == 0) - (first_before == 0);
    if (zeros < min_zeros) {
      min_zeros = zeros;
    }
  }
}
