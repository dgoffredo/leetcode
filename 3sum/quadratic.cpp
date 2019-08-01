#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> threeSum(const std::vector<int>& numbers);

// leetcode.com boilerplate
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        return ::threeSum(nums);
    }
};

std::unordered_multimap<int, int> tabulate(const std::vector<int>& numbers) {
    std::unordered_multimap<int, int> result;

    for (int i = 0; i < int(numbers.size()); ++i) {
        result.emplace(numbers[i], i);
    }

    return result;
}

std::vector<std::vector<int>> threeSum(const std::vector<int>& numbers) {
    const std::unordered_multimap<int, int> indicesByValue = tabulate(numbers);

    std::set<std::vector<int>> solutions;

    const int n = numbers.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const auto [begin, end] = indicesByValue.equal_range(-numbers[i] - numbers[j]);
            if (begin == indicesByValue.end()) {
                continue;
            }

            for (auto iter = begin; iter != end; ++iter) {
                const int k = iter->second;
                if (k == i || k == j) {
                    continue;
                }

                std::vector<int> candidate{numbers[i],
                                           numbers[j],
                                           numbers[k]};
                std::sort(candidate.begin(), candidate.end());
                solutions.insert(candidate);
            }
        }
    }

    return std::vector<std::vector<int>>(solutions.begin(), solutions.end());
}