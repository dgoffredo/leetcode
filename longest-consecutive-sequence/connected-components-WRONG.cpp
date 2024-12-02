#include <algorithm>
#include <unordered_map>
#include <vector>

int length_of_longest_consecutive_subset(const std::vector<int>& numbers) {
    std::unordered_map<int, int> lengths;
    for (const int number : numbers) {
        lengths[number] = 1;
    }

    int max = 0;
    for (auto& [number, length] : lengths) {
        const auto found = lengths.find(number - 1);
        if (found != lengths.end()) {
            length = found->second = length + found->second;
        }
        max = std::max(max, length);
    }

    return max;
}

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
       return length_of_longest_consecutive_subset(nums); 
    }
};
