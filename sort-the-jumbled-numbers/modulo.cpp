#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        const auto mapped = [&](int before) {
          int after = 0;
          int place = 1;
          do {
            int digit = before % 10;
            int digit_after = mapping[digit];
            after += digit_after * place;
            before /= 10;
            place *= 10;
          } while (before);
          return after;
        };

        const auto mapped_less = [&](int left, int right) {
          return mapped(left) < mapped(right);
        };

        stable_sort(nums.begin(), nums.end(), mapped_less);
        return move(nums);
    }
};
