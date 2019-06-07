
#include <algorithm>
#include <cassert>
#include <vector>

int maxDisjointSum(const std::vector<int>& numbers,
                   int                     leftWidth,
                   int                     rightWidth);

// leetcode.com boilerplate
class Solution {
public:
    int maxSumTwoNoOverlap(const std::vector<int>& A, int L, int M) {
        return std::max(maxDisjointSum(A, L, M), maxDisjointSum(A, M, L));
    }
};

int maxDisjointSum(const std::vector<int>& numbers,
                   int                     leftWidth,
                   int                     rightWidth)
{
    // prefixSums[i+1] is the sum of numbers[0] to numbers[i].
    assert(!numbers.empty());
    std::vector<int> prefixSums(numbers.size() + 1);
    for (int i = 1; i < int(prefixSums.size()); ++i)
    {
        prefixSums[i] = prefixSums[i - 1] + numbers[i - 1];
    }

    const int N = numbers.size();
    int       currentMax = 0;
    for (int i = 0; i < N - (leftWidth + rightWidth) + 1; ++i)
    {
        for (int j = i + leftWidth; j < N - rightWidth + 1; ++j)
        {
            const int total = (prefixSums[i + leftWidth] - prefixSums[i]) +
                              (prefixSums[j + rightWidth] - prefixSums[j]);

            if (total > currentMax) {
                currentMax = total;
            }
        }
    }

    return currentMax;
}
