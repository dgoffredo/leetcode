#include <algorithm>
#include <string>
#include <utility>
#include <vector>

long long number_of_ways(const std::string& buildings) {
  if (buildings.empty()) {
    return 0;
  }

  std::vector<std::pair<char, int>> runs;
  auto begin = buildings.begin();
  decltype(begin) end;
  do {
    end = std::find_if(begin, buildings.end(), [&](char ch) { return ch != *begin; });
    runs.emplace_back(*begin, end - begin);
    begin = end;
  } while (begin != buildings.end());
  
  const int n = runs.size();
  long long ways = 0;
  for (int first = 0; first < n; ++first) {
    for (int second = first + 1; second < n; ++second) {
      if (runs[second].first == runs[first].first) {
        continue;
      }
      for (int third = second + 1; third < n; ++third) {
        if (runs[third].first == runs[second].first) {
          continue;
        }
        long long product = runs[first].second * runs[second].second * runs[third].second;
        ways += product;
      }
    }
  }

  return ways;
}

#include <iostream>

int main(int /*argc*/, char *argv[]) {
  std::cout << number_of_ways(argv[1]) << '\n';
}
