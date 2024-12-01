#include <algorithm>
#include <cassert>
#include <vector>


using Iter = std::vector<int>::const_iterator;

Iter peak(Iter beg, Iter end) {
  const auto len = end - beg;
  if (len <= 3)  {
    return std::max_element(beg, end);
  }
  const auto middle = beg + len / 2;
  const auto δleft = *middle - *(middle - 1);
  const auto δright = *(middle + 1) - *middle;
  if (δleft < 0 && δright < 0) {
    return peak(beg, middle);
  }
  if (δleft > 0 && δright > 0) {
    return peak(middle, end);
  }
  assert(δleft >0 && δright < 0);
  return middle;
}


class Solution {
public:
    int peakIndexInMountainArray(std::vector<int>& arr) {
      return peak(arr.begin(), arr.end()) - arr.begin();
    }
};

#include <iostream>

int main() {
  std::vector<int> heights;
  int height;
  while (std::cin >> height) {
    heights.push_back(height);
  }
  const int i = Solution().peakIndexInMountainArray(heights);
  std::cout << heights[i] << " (@" << i << ")\n";
}
