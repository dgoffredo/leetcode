
#include <algorithm>
#include <cassert>
// #include <iostream>  // debugging only
#include <vector>

std::vector<int> subarrayIndiciesForMaxSum(const std::vector<int>&, int);

class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        return subarrayIndiciesForMaxSum(nums, k);
    }
};


std::vector<int> subarrayIndiciesForMaxSum(const std::vector<int>& nums, int k)
{
    // First calculate prefix sums, so that calculating array sums is constant
    // time subsequently.
    const int N = nums.size();

    std::vector<int> prefixSums;
    prefixSums.reserve(N + 1);
    prefixSums.push_back(0);
    for (int i = 1; i < N + 1; ++i) {
        prefixSums[i] = prefixSums[i - 1] + nums[i - 1];
    }

    // The secret sauce here is to keep track of, for each possible position of
    // the first subarray, at which index at _or_ _before_ it gives the
    // greatest sum. Then we can also do this for the third subarray, but
    // backwards from the end, and then the solution is a matter of trying all
    // possible positions of the middle subarray, and for each we'll know the
    // best places for the first and last subarrays, because we'll have already
    // stored that information earlier.

    // First find the best positions for the first subarray.
    std::vector<int> leftBestIndex;  // leftBestIndex[i] is the index <= i at
    leftBestIndex.reserve(N - 2*k);  // which beginning the first subarray
    leftBestIndex.push_back(0);      // gives the largest sum (considering that
                                     // subarray only).
    for (int i = 1; i <= N - 2*k; ++i) {
        const int sum = prefixSums[i + k] - prefixSums[i];
        const int prior = leftBestIndex[i - 1];
        const int priorSum = prefixSums[prior + k] - prefixSums[prior];
        if (sum > priorSum) {
            leftBestIndex.push_back(i);
        }
        else {
            leftBestIndex.push_back(prior);
        }
    }

    // Now find the best positions for the third (last) subarray. This one is
    // a bit trickier because we're going backwards.
    // You know what? Screw it, I'm just going to allocate extra storage. I
    // can't deal with all the offsets and off-by-ones.
    std::vector<int> rightBestIndex(N);
    rightBestIndex[N - k] = N - k;
    for (int i = N - k - 1; i >= 2*k; --i) {
        const int sum = prefixSums[i + k] - prefixSums[i];
        const int prior = rightBestIndex[i + 1];
        const int priorSum = prefixSums[prior + k] - prefixSums[prior];
        // Note the use of `>=` here rather than `>`.  This is because, in the
        // end, we want to have the lexicographically smallest solution.  Here,
        // going right to left, we'd ignore all solutions left of the first
        // encountered, which would ignore possibly lexicographically smaller
        // solutions.  By using `>=`, we prefer to preserve the more leftward
        // numbers, and so avoid that issue.
        if (sum >= priorSum) {
            rightBestIndex[i] = i;
        }
        else {
            rightBestIndex[i] = prior;
        }
    }

    int maxSum = 0;  // >0, since all numbers are positive.
    std::vector<std::vector<int>> maxStarts;  // TODO: could affect complexity

    // Finally, try all possible positions of the middle subarray, and for
    // each, calculate the sum for the middle subarray in that position, the
    // left subarray in the best position that fits, and the right subarray in
    // the best position that fits (these latter two pieces of information are
    // derived from `leftBestIndex` and `rightBestIndex`.
    for (int i = k; i <= N - 2*k; ++i) {
        const int sum = prefixSums[i + k] - prefixSums[i];

        const int bestLeft = leftBestIndex[i - k];
        const int leftSum = prefixSums[bestLeft + k] - prefixSums[bestLeft];

        const int bestRight = rightBestIndex[i + k];
        const int rightSum = prefixSums[bestRight + k] - prefixSums[bestRight];

        const int total = sum + leftSum + rightSum;

        /*std::cout << "at i=" << i << ", the best position for the first is at "
                  << bestLeft << " and the best position for the last is at "
                  << bestRight << " for sums of left=" << leftSum << " right="
                  << rightSum << " middle=" << sum << " total=" << total
                  << "\n";*/

        if (total > maxSum) {
            maxSum = total;
            maxStarts.clear();
            maxStarts.push_back({bestLeft, i, bestRight});
            /*std::cout << "Found a new max of " << total << " at ("
                      << bestLeft << ", " << i << ", " << bestRight << ")\n";*/
        }
        else if (total == maxSum) {
            maxStarts.push_back({bestLeft, i, bestRight});
            /*std::cout << "Found a duplicate solution for  " << total << " at ("
                      << bestLeft << ", " << i << ", " << bestRight << ")\n";*/
        }
    }

    assert(!maxStarts.empty());

    return *std::min_element(maxStarts.begin(), maxStarts.end());
}
