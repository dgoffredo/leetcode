#include <cassert>
#include <iterator>
#include <vector>

template <typename Iter>
Iter remove_runs_longer_than(Iter begin, Iter end, int k) {
    assert(k >= 1);

    if (std::distance(begin, end) < 2) {
        return end;
    }

    auto previous = *begin;
    auto write = std::next(begin);
    auto read = write;
    int run = 1;
    do {
        const auto& current = *read;
        assert(current >= previous);

        if (current != previous) {
            previous = current;
            run = 1;
        } else {
            ++run;
        }
        *write = current;
        if (run <= k) {
            ++write;
        }
        ++read;
    } while (read != end);

    return write;
}

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        const auto begin = nums.begin();
        const auto end = nums.end();
        return std::distance(begin, remove_runs_longer_than(begin, end, 2));
    }
};
