#include <dynamic.cpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

/*
class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        return subarrayIndiciesForMaxSum(nums, k);
    }
};
*/

int main() {
    int k;
    std::cin >> k;

    std::vector<int> nums;
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(nums));

    const std::vector<int> answer = Solution().maxSumOfThreeSubarrays(nums, k);
    std::copy(answer.begin(),
              answer.end(),
              std::ostream_iterator<int>(std::cout, " "));
}