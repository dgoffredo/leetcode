#include <algorithm>
#include <unordered_set>
#include <vector>

int length_of_longest_consecutive_subset(const std::vector<int>& numbers) {
    std::unordered_set<int> numset(numbers.begin(), numbers.end());

    int max = 0;
    while (numset.size() > max) {
        auto iter = numset.begin();
        // Rewind to the beginning of the run.
        for (auto before = numset.find(*iter - 1); before != numset.end(); before = numset.find(*iter - 1)) {
            iter = before;
        }

        // We're at the beginning of the run. Count the run's length, removing
        // elements as we go.
        int length = 0;
        do {
            int num = *iter;
            numset.erase(iter);
            ++length;
            iter = numset.find(num + 1);
        } while (iter != numset.end());

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
