
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

    // `a` is the distance between the beginning of nums and the first
    // subarray. `b` is the distance between the end of the first subarray and
    // the beginning of the second subarray. `c` is the distance from the end
    // of the second subarray to the beginning of the third subarray.
    int maxSum = 0;  // can't be less, since all numbers are positive.
    std::vector<int> maxStarts{0, 0, 0};
    for (int a = 0; a <= N - 3*k; ++a) {
        for (int b = 0; b <= N - a - 3*k; ++b) {
            for (int c = 0; c <= N - a - b - 3*k; ++c) {
                const std::vector<int>& sums = prefixSums;  // brevity
                
                const int aSum = sums[a + k] - sums[a];
                const int bSum = sums[a + k + b + k] - sums[a + k + b];
                const int cSum =
                    sums[a + k + b + k + c + k] - sums[a + k + b + k + c];

                const int sum = aSum + bSum + cSum;
                if (sum > maxSum) {
                    maxSum = sum;
                    maxStarts[0] = a;
                    maxStarts[1] = a + k + b;
                    maxStarts[2] = a + k + b + k + c;
                }
            }
        }
    }

    return maxStarts;
}
