
#include <algorithm>
#include <iostream>  // debugging
#include <iterator>
#include <ostream>  // debugging
#include <vector>

// #define DEBUG(...) do {} while (false)
#define DEBUG(...) do { std::cout << __VA_ARGS__; } while (false)

typedef std::vector<int>::iterator Iter;

int numReversePairs(Iter beg, Iter end) {
    const int length = std::distance(beg, end);
    if (length < 2) {
        return 0;
    }

    const Iter mid = beg + length / 2;
    int count = numReversePairs(mid, end);
    for (Iter iter = beg; iter != mid; ++iter) {
        const double cutoff = *iter / 2.0;
        count += std::distance(mid, std::lower_bound(mid, end, cutoff));
    }

    count += numReversePairs(beg, mid);

    std::inplace_merge(beg, mid, end);

    return count;
}

// leetcode.com boilerplate
class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        return numReversePairs(nums.begin(), nums.end());
    }
};