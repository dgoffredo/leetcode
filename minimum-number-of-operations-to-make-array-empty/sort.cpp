#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int operations = 0;

        sort(nums.begin(), nums.end());
        const auto end = nums.end();
        auto iter = nums.begin();
        do {
          auto after = upper_bound(iter, end, *iter);
          int count = after - iter;
          if (count == 1) {
            return -1;
          }
          if (count % 3 == 0) {
            operations += count / 3;
          } else {
            operations += count / 3 + 1;
          }
          iter = after;
        } while (iter != end);
        
        return operations;
    }
};
