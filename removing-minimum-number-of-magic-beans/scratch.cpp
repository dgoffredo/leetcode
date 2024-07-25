#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

int main(int, char *argv[]) {
  std::vector<int> nums(std::istream_iterator<int>{std::cin},
                        std::istream_iterator<int>{});
  std::sort(nums.begin(), nums.end(), std::greater<>());

  const int of_what = std::atoi(argv[1]);
  std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n'
      << std::distance(nums.begin(), std::upper_bound(nums.begin(), nums.end(), of_what, std::greater<>()))
      << '\n';
}
