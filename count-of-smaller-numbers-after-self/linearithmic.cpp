
#include <algorithm>
#include <iterator>
#include <vector>

void lesserSuffixCounts(std::vector<int>& counts,
                        std::vector<int>& numbers,
                        int i,
                        int j) {
    const int length = j - i;
    if (length < 2) {
        return;
    }

    const int midIndex = i + length / 2;
    lesserSuffixCounts(counts, numbers, midIndex, j);

    const auto end = std::next(numbers.begin(), j);
    const auto mid = std::next(numbers.begin(), midIndex);

    for (int index = i; index != midIndex; ++index) {
        const int value = numbers[index];
        counts[index] += std::distance(mid, std::lower_bound(mid, end, value));
    }

    lesserSuffixCounts(counts, numbers, i, midIndex);

    const auto beg = std::next(numbers.begin(), i);
    std::inplace_merge(beg, mid, end);
}

// leetcode.com boilerplate
class Solution {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        std::vector<int> counts(nums.size());
        lesserSuffixCounts(counts, nums, 0, nums.size());
        return counts;
    }
};
