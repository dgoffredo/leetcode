
#include <algorithm>
#include <iostream>  // debugging
#include <iterator>
#include <ostream>  // debugging
#include <vector>

#define DEBUG(...) do {} while (false)
// #define DEBUG(...) do { std::cout << __VA_ARGS__; } while (false)

int numReversePairs(std::vector<int>& numbers) {
    // We proceed by solving the problem first for the last two `numbers`, then
    // for the last three, etc.  We keep track of the number of "reverse pairs"
    // encountered.  When processing the next element (backwards) we need only
    // add to the current count how many `numbers` in the current suffix are
    // less than half the current number.  We can make this operation cheaper
    // by gradually sorting the suffix as we go along.
    // As far as I can see, this is worst case `O(n^2)`, which means there
    // exists inputs in the problem domain that would take too long to process.
    // However, someone in the discussion section claimed that this works, so
    // let's try it.

    int result = 0;
    if (numbers.size() < 2) {
        return result;
    }

    const auto begin = numbers.begin();
    const auto end = numbers.end();

    auto prev = end;
    --prev;
    auto iter = prev;

    for (--iter; iter >= begin; prev = iter--) {
        DEBUG("Looking at index " << std::distance(begin, iter) << "\n");
        // Determine how many numbers in `[prev, end)` form a "reverse pair"
        // with `iter`.
        const int cutoff = (*iter + 1LL) / 2LL;
        const auto found = std::lower_bound(prev, end, cutoff);
        DEBUG("Lower bound of value " << cutoff << "  returned index "
              << std::distance(begin, found) << "\n");
        DEBUG("Adding " << std::distance(prev, found) << " to result.\n");
        result += std::distance(prev, found);

        // Merge the current number into the suffix.
        std::inplace_merge(iter, prev, end);
    }

    return result;
}

// leetcode.com boilerplate
class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        return numReversePairs(nums);
    }
};