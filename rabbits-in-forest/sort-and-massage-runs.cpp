#include <algorithm>
#include <cassert>
#include <cstdlib>
// #include <iostream>
#include <vector>

int minimum_number_of_rabbits(std::vector<int>& interviews) {
  std::sort(interviews.begin(), interviews.end());
  /*std::cout << "sorted input:";
  for (const int value : interviews) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';*/
  assert(!interviews.empty());
  int min_rabbits = 0;
  auto begin_run = interviews.begin();
  do {
    const int run_value = *begin_run;
    const auto end_run = std::find_if(
      begin_run + 1,
      interviews.end(),
      [run_value](int value) { return value != run_value; });
    const int run_length = end_run - begin_run;
    // This run contributes `ceil(len / (val + 1)) * (val + 1)` to the minimum count.
    std::div_t division = std::div(run_length, run_value + 1);
    /*std::cout << "Run of " << run_length << ' ' << run_value
        << "\n    quot=" << division.quot << " rem=" << division.rem << '\n';*/
    if (division.rem) {
      ++division.quot;
    }
    /*std::cout << "    adding " << (division.quot * (run_value + 1)) << " to the count\n";*/
    min_rabbits += division.quot * (run_value + 1);
    begin_run = end_run;
  } while (begin_run != interviews.end());

  return min_rabbits;
}

class Solution {
public:
    int numRabbits(std::vector<int>& interviews) {
       return minimum_number_of_rabbits(interviews);
    }
};

/*int main() {
  std::vector<int> interviews;
  int value;
  while (std::cin >> value) {
    interviews.push_back(value);
  }
  std::cout << Solution().numRabbits(interviews) << '\n';
}*/
