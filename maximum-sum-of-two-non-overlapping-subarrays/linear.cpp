
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
    const int N = numbers.size();

    // prefixSums[i+1] is the sum of numbers[0] to numbers[i].
    assert(!numbers.empty());
    std::vector<int> prefixSums(N + 1);
    for (int i = 1; i < int(prefixSums.size()); ++i)
    {
        prefixSums[i] = prefixSums[i - 1] + numbers[i - 1];
    }

    // The trick is to find, for each possible position `i` of the first
    // subarray, the position `j <= i` that yields the maximal sum for that
    // subarray.  Once we've calculated that, we can go through all possible
    // starting positions of the second array and know the corresponding best
    // position for the first array.  This way, we turn quadratic runtime and
    // constant space into linear runtime and linear space.
    std::vector<int> bestLeft(N - rightWidth - leftWidth + 1);
    bestLeft[0] = 0;
    for (int i = 1; i < int(bestLeft.size()); ++i) {
        const int sum = prefixSums[i + leftWidth] - prefixSums[i];
        const int prior = bestLeft[i - 1];
        const int priorSum = prefixSums[prior + leftWidth] - prefixSums[prior];
        if (sum > priorSum) {
            bestLeft[i] = i;
        }
        else {
            bestLeft[i] = prior;
        }
    }

    int currentMax = 0;
    for (int i = leftWidth; i < N - rightWidth + 1; ++i)
    {
        const int sum = prefixSums[i + rightWidth] - prefixSums[i];
        const int j = bestLeft[i - leftWidth];
        const int leftSum = prefixSums[j + leftWidth] - prefixSums[j];
        const int total = sum + leftSum;
        if (total > currentMax) {
            currentMax = total;
        }
    }

    return currentMax;
}
