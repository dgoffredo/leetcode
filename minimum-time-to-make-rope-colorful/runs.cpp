#include <cassert>
#include <string>
#include <vector>

int sum_of_cheapest_way_to_remove_runs(const std::string& colors, const std::vector<int>& costs) {
  assert(colors.size() == costs.size());

  if (colors.size() < 2) {
    return 0;
  }

  int solution = 0; // We'll add to it in the loop below.
  int i = 0;
  char previous_color = colors[i];
  int run_sum = costs[i];
  int run_max = costs[i];

  for (++i; i < int(colors.size()); ++i) {
    if (colors[i] != previous_color) {
      solution += run_sum - run_max;
      run_sum = 0;
      run_max = 0;
      previous_color = colors[i];
    }
    run_sum += costs[i];
    if (costs[i] > run_max) {
      run_max = costs[i];
    }
  }

  // leftovers
  solution += run_sum - run_max;

  return solution;
}

class Solution {
public:
    int minCost(std::string colors, std::vector<int>& neededTime) {
       return sum_of_cheapest_way_to_remove_runs(colors, neededTime);
    }
};
