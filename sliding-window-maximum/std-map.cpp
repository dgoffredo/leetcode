#include <functional>
#include <map>
#include <vector>

std::vector<int> max_in_each_window(const std::vector<int>& numbers, int window_size) {
    std::vector<int> maxes;
    maxes.reserve(numbers.size() - window_size + 1);
    
    std::map<int, int, std::greater<int>> counts;
    auto window_begin = numbers.begin();
    auto window_end = window_begin + window_size;
    for (auto iter = window_begin; iter != window_end; ++iter) {
        ++counts[*iter];
    }
    maxes.push_back(counts.begin()->first); // largest


    for (auto last = window_end; last != numbers.end(); ++last) {
        const auto found = counts.find(*window_begin);
        if (--found->second == 0) {
            counts.erase(found);
        }
        ++window_begin;
        ++counts[*last];
        maxes.push_back(counts.begin()->first); // largest
    }

    return maxes;
}

class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
       return max_in_each_window(nums, k); 
    }
};
