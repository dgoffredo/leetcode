
#include <unordered_map>
#include <utility>  // pair
#include <vector>

int num_zero_combinations(const std::vector<int>& john,
                          const std::vector<int>& paul, 
                          const std::vector<int>& george, 
                          const std::vector<int>& ringo);

class Solution {
public:
    int fourSumCount(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, std::vector<int>& D) {
        return num_zero_combinations(A, B, C, D);
    }
};


int num_zero_combinations(const std::vector<int>& john,
                          const std::vector<int>& paul, 
                          const std::vector<int>& george, 
                          const std::vector<int>& ringo) {
    const int N = john.size();

    // This N**2 solution caches the sum of all distinct pairs between george
    // and ringo, and then goes through all distinct pairs between john and
    // paul and looks for its negation in the cache.  This works because if
    //     j + p + g + r = 0
    // then
    //     j + p = -(g + r)
    // It costs N**2 to build the cache, and then an additional N**2 to check
    // all of the john/paul pairs.  It costs at most N**2 in memory for the
    // cache, and technically there's a worst-case additional factor of N**2
    // in time due to hash tables not being _really_ constant lookup, but I
    // ignore the possibility of larger issues due to hash collisions.

    // sum => num of george/ringo pairs having that sum
    std::unordered_map<int, int> cache;
    for (int g = 0; g < N; ++g) {
        for (int r = 0; r < N; ++r) {
            ++cache[george[g] + ringo[r]];
        }
    }

    int numZeros = 0;
    for (int j = 0; j < N; ++j) {
        for (int p = 0; p < N; ++p) {
            const auto found = cache.find(-(john[j] + paul[p]));
            if (found != cache.end()) {
                numZeros += found->second;
            }
        }
    }

    return numZeros;
}