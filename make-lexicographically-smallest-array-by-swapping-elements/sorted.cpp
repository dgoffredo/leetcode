// #include <iostream>
#include <set>
#include <tuple>
#include <vector>

void massage(std::vector<int>& numbers, int limit) {
  std::set<std::tuple<int, std::size_t>> values;
  for (std::size_t i = 0; i < numbers.size(); ++i) {
    // std::cout << "Inserting " << numbers[i] << '@' << i << '\n';
    values.emplace(numbers[i], i);
  }

  for (std::size_t i = 0; i < numbers.size() - 1;) {
    /*std::cout << "values: ";
    for (const auto& [value, index] : values) {
      std::cout << ' ' << value << '@' << index;
    }
    std::cout << '\n';
    std::cout << "Looking at " << numbers[i] << '@' << i << '\n';*/
    auto iter = values.lower_bound(std::make_tuple(numbers[i] - limit, 0));
    auto me = std::make_tuple(numbers[i], i);
    if (iter == values.end() || std::get<0>(*iter) >= numbers[i]) {
      // We went as low as we can @i.
      // std::cout << "  " << numbers[i] << " is as low as we can go @" << i << '\n';
      values.erase(me);
      ++i;
      continue;
    }

    // We found a replacement. Swap the numbers, update `values`, and go around
    // the loop again to see if we can do better.
    const auto [new_value, j] = *iter;
    // std::cout << "  found candidate " << new_value << '@' << j << '\n';
    values.erase(iter);
    values.erase(me);
    values.insert(std::make_pair(new_value, i));
    values.insert(std::make_pair(numbers[i], j));
    std::swap(numbers[i], numbers[j]);
  }
}

class Solution {
public:
    std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums, int limit) {
      massage(nums, limit);
      return std::move(nums);
    }
};

int main() {
  int limit;
  std::cin >> limit;
  if (!std::cin) {
    return 1;
  }
  std::vector<int> numbers;
  int number;
  while (std::cin >> number) {
    numbers.push_back(number);
  }
  numbers = Solution().lexicographicallySmallestArray(numbers, limit);
  for (const int value : numbers) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';
}
