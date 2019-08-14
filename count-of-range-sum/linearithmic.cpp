
#include <algorithm>
#include <iostream>  // debugging
#include <iterator>
#include <ostream>  // debugging
#include <sstream>  // debugging
#include <string>  // debugging
#include <vector>

#ifndef NDEBUG
    #define DEBUG(...) do { std::cout << __VA_ARGS__ << "\n"; } while (false)
#else
    #define DEBUG(...) do {} while (false)
#endif

std::string print(const std::vector<long long>& numbers) {
    std::ostringstream stream;
    stream << "[";

    auto iter = numbers.begin();
    if (iter != numbers.end()) {
        stream << *iter;
        for (++iter; iter != numbers.end(); ++iter) {
            stream << ", " << *iter;
        }
    }

    stream << "]";
    return stream.str();
}

int numRangeSumsInBounds(std::vector<long long>& prefixSums,
                         const std::vector<int>& numbers,
                         int                     lower,
                         int                     upper,
                         int                     i,
                         int                     j) {
    DEBUG("examining (" << i << ", " << j << ")");

    const int length = j - i;

    if (length == 0) {
        DEBUG("i == j == " << i << " -> 0");
        return 0;
    }

    if (length == 1) {
        // A subarray of length one has only one sum: itself.  So, that counts
        // as one if the number is in `[lower, upper]`.  Otherwise it counts
        // as zero.
        DEBUG("length 1 @" << i << " -> "
              << (numbers[i] >= lower && numbers[i] <= upper));
        return numbers[i] >= lower && numbers[i] <= upper;
    }

    // `recur` is defined for brevity.  It binds references to `prefixSums`,
    // `numbers`, `lower`, and `upper`, since those always refer to the same
    // objects across incovations.
    const auto recur = [&](int iNew, int jNew) {
        return numRangeSumsInBounds(
                                prefixSums, numbers, lower, upper, iNew, jNew);
    };

    // Otherwise, we divide and conquer.
    const int midIndex = i + length / 2;
    DEBUG("midIndex = " << midIndex);

    int count = recur(midIndex, j);

    // `[midIndex, j)` in `prefixSums` now has the sorted prefix sums of the
    // corresponding subarray `[midIndex, j)` in `numbers`.  We've already
    // counted all the relevant subarrays in the right half; now we can count
    // all relevant subarrays that span both halves.  Then we can recur on the
    // first half to get that count, and finally adjust and merge the prefix
    // sums.
    const auto mid = std::next(prefixSums.begin(), midIndex);
    const auto end = std::next(prefixSums.begin(), j);
    long long sum = 0;
    for (int index = midIndex - 1; index >= i; --index) {
        sum += numbers[index];
        DEBUG("current sum is " << sum);

        const auto least = std::lower_bound(mid, end, lower - sum);
        const auto most  = std::upper_bound(mid, end, upper - sum);

        DEBUG("    offset of least is "
              << std::distance(prefixSums.begin(), least));
        DEBUG("    offset of most is "
              << std::distance(prefixSums.begin(), most));
        
        DEBUG("    index " << index << " looking rightward found "
              << std::distance(least, most) << " matches.");

        count += std::distance(least, most);
    }

    count += recur(i, midIndex);

    const long long leftSum = prefixSums[midIndex - 1];
    for (int index = midIndex; index != j; ++index) {
        prefixSums[index] += leftSum;
    }

    DEBUG("Before merge, prefixSums is " << print(prefixSums));

    const auto beg = std::next(prefixSums.begin(), i);
    std::inplace_merge(beg, mid, end);

    DEBUG("After merge, prefixSums is " << print(prefixSums));

    return count;
}

// leetcode.com boilerplate
class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        std::vector<long long> prefixSums(nums.begin(), nums.end());
        return numRangeSumsInBounds(prefixSums,
                                    nums,
                                    lower,
                                    upper, 
                                    0, 
                                    nums.size());
    }
};