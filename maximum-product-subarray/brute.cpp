#include <algorithm>
#include <vector>

int maxProduct(const std::vector<int>& numbers);

// leetcode.com boilerplate
class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        return ::maxProduct(nums);
    }
};

int maxProduct(const std::vector<int>& numbers) {
    const int n    = numbers.size();
    int       best = *std::max_element(numbers.begin(), numbers.end());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int product = 1;
            for (int k = i; k < j; ++k) {
                product *= numbers[k];
            }
            if (product > best) {
                best = product;
            }
        }
    }

    return best;           
}