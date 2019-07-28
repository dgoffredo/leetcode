#include <algorithm>
#include <utility>
#include <vector>

int maxProduct(const std::vector<int>& numbers);

// leetcode.com boilerplate
class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        return ::maxProduct(nums);
    }
};

typedef std::vector<int>::const_iterator Iter;

struct Identity {
    template <typename T>
    const T& operator()(const T& thing) const {
        return thing;
    }
};

std::pair<Iter, Iter> nextIsland(const std::vector<int>& numbers,
                                 Iter                    start) {
    Iter i = std::find_if(start, numbers.end(), Identity());  // find nonzero
    Iter j = std::find(i, numbers.end(), 0);                  // find zero

    return std::make_pair(i, j);
}

int maxProduct(const std::vector<int>& numbers) {
    const int n    = numbers.size();
    int       best = *std::max_element(numbers.begin(), numbers.end());

    // for each island
    for (std::pair<Iter, Iter> range = nextIsland(numbers, numbers.begin());
         range.first != numbers.end();
         range = nextIsland(numbers, range.second) {
         // const int product = std::accumulate(range.first, range.second, 
         // TODO: multiplies
    }
         

    return best;           
}
