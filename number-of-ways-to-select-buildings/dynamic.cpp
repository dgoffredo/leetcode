#include <algorithm>
#include <cassert>
#include <string>

long long number_of_ways(const std::string& buildings) {
  const int n = buildings.size();
  if (n < 3) {
    return 0;
  }

  long long total_ways = 0;
  const int total_1s = std::count(buildings.begin(), buildings.end(), '1');
  int left_1s = buildings[0] == '1';
  for (int i = 1; i < n - 1; ++i) {
    if (buildings[i] == '0') {
      const int right_1s = total_1s - left_1s;
      total_ways += left_1s * right_1s; 
    } else {
      assert(buildings[i] == '1');
      const int left_0s = i - left_1s;
      const int total_0s = n - total_1s;
      const int right_0s = total_0s - left_0s;
      total_ways += left_0s * right_0s;
      ++left_1s;  // for the next iteration
    }
  }

  return total_ways;
}

#include <iostream>

int main(int /*argc*/, char *argv[]) {
  std::cout << number_of_ways(argv[1]) << '\n';
}

