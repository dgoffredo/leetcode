#include <algorithm>
#include <vector>

using namespace std;

vector<bool> check_arithmetic_subarrays(const vector<int>& nums, const vector<int>& fronts, const vector<int>& backs);

class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
       return check_arithmetic_subarrays(nums, l, r); 
    }
};

bool is_arithmetic_subarray(const vector<int>& subarray) {
  switch (subarray.size()) {
  case 0: return false;
  case 1: return false;
  case 2: return true;
  }

  const int step = subarray[1] - subarray[0];
  for (size_t i = 1; i < subarray.size() - 1; ++i) {
    if (subarray[i + 1] - subarray[i] != step) {
      return false;
    }
  }

  return true;
}

vector<bool> check_arithmetic_subarrays(const vector<int>& nums, const vector<int>& fronts, const vector<int>& backs) {
  vector<bool> result;
  result.resize(fronts.size());

  vector<int> scratch;
  for (size_t i = 0; i < fronts.size(); ++i) {
    const int front = fronts[i];
    const int back = backs[i];
    scratch.resize(back - front + 1);
    copy(nums.begin() + front, nums.begin() + back + 1, scratch.begin());
    sort(scratch.begin(), scratch.end());
    result[i] = is_arithmetic_subarray(scratch);
  }

  return result;
}
