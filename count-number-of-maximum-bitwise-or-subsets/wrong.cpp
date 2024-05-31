#include <algorithm>
#include <iostream>
#include <vector>

int count_them(const std::vector<int>& nums) {
  int count = 1;

  // Numbers are no greater than 100,000
  // So, the highest set bit is no greater than 2**17.
  for (int which_bit = 0; which_bit < 18; ++which_bit) {
    const int mask = 1 << which_bit;
    const int how_many = std::count_if(
      nums.begin(), nums.end(), [=](int num) { return (num & mask) != 0; });
    std::cout << "Looking at bit offset " << which_bit << " there are " << how_many << " matches\n";
    if (how_many != 0) {
      count *= how_many;
    }
  }

  return count;
}

class Solution {
public:
    int countMaxOrSubsets(std::vector<int>& nums) {
       return count_them(nums); 
    }
};

int main() {
  std::vector<int> nums;
  int num;
  while (std::cin >> num) {
    nums.push_back(num);
  }

  std::cout << count_them(nums)  << '\n';
}
