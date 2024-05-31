#include <algorithm>
#include <numeric>
#include <vector>

int count_them(const std::vector<int>& nums) {
  const int max = std::accumulate(nums.begin(), nums.end(), 0, std::bit_or<>{});
  
  // Now iterate over all subsets, counting if the bitwise-or is equal to
  // `max`.
  const int N = nums.size();
  int count = 0;
  for (int i = 1; i < (1 << N); ++i) {
    // The bits of `i` tell us whether to include each corresponding element of
    // `nums` in the `subset_or`.
    int subset_or = 0;
    for (int j = 0; j < N; ++j) {
      if (i & (1 << j)) {
        subset_or |= nums[j];
      }
    }
    if (subset_or == max) {
      ++count;
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

// --------------------------------------------------------

#include <iostream>

int main() {
  std::vector<int> nums;
  int num;
  while (std::cin >> num) {
    nums.push_back(num);
  }

  std::cout << count_them(nums)  << '\n';
}
