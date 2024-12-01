#include <algorithm>
#include <vector>


using Iter = std::vector<int>::const_iterator;

Iter peak(Iter beg, Iter end) {
  const auto len = end - beg;
  if (len <= 3)  {
    return std::max_element(beg, end);
  }
  const auto middle = beg + len / 2;
  const auto left = peak(beg, middle);
  const auto right = peak(middle, end);
  auto max = middle;
  if (*left > *max) {
    max = left;
  }
  if (*right > *max) {
    max = right;
  }
  return max;
}


class Solution {
public:
    int peakIndexInMountainArray(std::vector<int>& arr) {
      return peak(arr.begin(), arr.end()) - arr.begin();
    }
};
