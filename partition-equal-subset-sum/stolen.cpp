#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
      const int sum = accumulate(nums.begin(), nums.end(), 0);
      if (sum % 2) {
        return false;
      }
      
      vector<bool> table(sum/2 + 1);
      table[0] = true;
      for (const int num : nums) {
        for (int sigma = sum/2; sigma >= num; --sigma) {
          if (table[sigma - num]) {
            table[sigma] = true;
          }
        }
      }

      return table[sum/2];
    }
};

