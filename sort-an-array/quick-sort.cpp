#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Iter, typename Predicate>
Iter partition_by(Iter begin, Iter end, Predicate pred) {
  Iter center = std::find_if_not(begin, end, pred);
  if (center == end) {
    return center;
  }
  for (Iter it = center + 1; it != end; ++it) {
    // std::cout << "[center@" << std::distance(begin, center) << " it@" << std::distance(begin, it) << "]\n";
    if (!pred(*it)) {
      continue;
    }
    using std::iter_swap;
    iter_swap(center, it);
    ++center;
  }

  std::cout << "    center@" << std::distance(begin, center) << " partitioned:";
  for (auto it = begin; it != end; ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << '\n';
  return center;
}

template <typename Iter>
void quick_sort(Iter begin, Iter end) {
  const auto n = std::distance(begin, end);
  std::cout << "quick_sort [";
  for (Iter it = begin; it != end; ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << " ]\n";
  if (n < 2) {
    return;
  }
  const auto pivot = *(begin + (end - begin) / 2);
  std::cout << "pivot = " << pivot << '\n';
  auto end_first_half = partition_by(begin, end, [&](const auto& element) {
    return element < pivot;
  });
  auto begin_second_half = partition_by(end_first_half, end, [&](const auto& element) {
    return !(pivot < element);
  });
  std::cout << "    After partitioning: ";
  for (Iter it = begin; it != end; ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << '\n';

  std::cout << "Sorting first half:\n";
  quick_sort(begin, end_first_half);
  std::cout << "Sorting second half:\n";
  quick_sort(begin_second_half, end);
}

class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
      quick_sort(nums.begin(), nums.end());
      return std::move(nums);
    }
};

int main() {
  std::vector<int> numbers;
  int number;
  while (std::cin >> number) {
    numbers.push_back(number);
  }

  std::cout << "input:";
  for (int number : numbers) {
    std::cout << ' ' << number;
  }
  std::cout << '\n';

  numbers = Solution().sortArray(numbers);

  std::cout << "output:";
  for (int number : numbers) {
    std::cout << ' ' << number;
  }
  std::cout << '\n';
}
