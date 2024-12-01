#include <algorithm>
// #include <iostream>
#include <vector>


std::vector<int> limited_sort(std::vector<int>& nums, int limit) {
  using Iter = std::vector<int>::iterator;

  std::vector<int> result = nums; // for later
  std::sort(nums.begin(), nums.end());
  /*std::cout << "sorted: [";
  for (int i : nums) {
    std::cout << ' ' << i;
  }
  std::cout << " ]\n";*/

  struct Component {
    Iter begin;
    Iter current;
  };
  std::vector<Component> components;
  components.push_back({.begin = nums.begin(), .current = nums.begin()});

  auto iter = nums.begin();
  for (++iter; iter != nums.end(); ++iter) {
    if (*iter - *(iter - 1) > limit) {
      // new component
      components.push_back({.begin = iter, .current = iter});
    }
  }
  /*std::cout << "components: [";
  for (const auto& component : components) {
    std::cout << " @" << (component.begin - nums.begin());
  }
  std::cout << " ]\n";*/

  struct ByBegin {
    bool operator()(const Component& left, const Component& right) const {
      return left.begin < right.begin;
    }
  };

  for (Iter iter = result.begin(); iter != result.end(); ++iter) {
    /*std::cout << '[';
    for (Iter i = result.begin(); i != result.end(); ++i) {
      if (i == iter) {
        std::cout << " (" << *i << ')';
      } else {
        std::cout << ' ' << *i;
      }
    }
    std::cout << "]\n";*/

    Iter where = std::lower_bound(nums.begin(), nums.end(), *iter);
    // std::cout << "looking at " << *iter << '@' << (where - nums.begin()) << '\n';
    auto component = std::upper_bound(components.begin(), components.end(), Component{.begin = where, .current = where}, ByBegin{}) - 1;
    // std::cout << "  it's in the component starting @" << (component->begin - nums.begin()) << '\n';
    *iter = *component->current++;
  }

  return result;
}

class Solution {
public:
    std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums, int limit) {
      return limited_sort(nums, limit);
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
