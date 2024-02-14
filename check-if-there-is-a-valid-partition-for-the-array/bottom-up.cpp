// #define DEBUGGING

#ifdef DEBUGGING
#include <iostream>
#define DEBUG for (bool XyZ = true; XyZ; std::cout << std::endl, XyZ = false) std::cout
#else
struct Ignore {};
template <typename T>
Ignore operator<<(const Ignore&, T&&) { return Ignore{}; }
#define DEBUG if (false) Ignore{}
#endif

#include <vector>

// for use by main() only...
#include <iostream>

using namespace std;

bool is_valid_partition(const vector<int>& nums);

class Solution {
public:
    bool validPartition(vector<int>& nums) {
       return is_valid_partition(nums); 
    }
};

bool matches_2(vector<int>::const_iterator beg) {
  return *beg == *(beg + 1);
}

bool matches_3(vector<int>::const_iterator beg) {
  const int a = *beg, b = *(beg + 1), c = *(beg + 2);
  return (a == b && a == c) || (b == a + 1 && c == a + 2);
}

bool matches(vector<int>::const_iterator beg, const bool (&table)[4], int j) {
  return (matches_2(beg) && table[(j + 2) % 4]) || (matches_3(beg) && table[(j + 3) % 4]);
}

bool is_valid_partition(const vector<int>& nums) {
  // Edge cases for the whole problem.
  switch (nums.size()) {
  case 0: return false;
  case 1: return false;
  case 2: return matches_2(nums.begin());
  case 3: return matches_3(nums.begin());
  }

  bool table[4];
  // Edge cases for the dynamic programming table.
  table[3] = false;
  auto iter = nums.begin() + (nums.size() - 2);
  table[2] = matches_2(iter);
  --iter;
  table[1] = matches_3(iter);
  int j = 0;
  --iter;

  // The rest of the entries in the dynamic programming table.
  for (;;) {
    table[j] = matches(iter, table, j);
    if (iter == nums.begin()) {
      return table[j];
    }
    --iter;
    j = (j + 3) % 4;
  }
}

// test
int main() {
  // DEBUG << "Input: {4, 4, 4, 5, 6}";
  // return is_valid_partition({4, 4, 4, 5, 6});
  // DEBUG << "Input: {1, 1, 1, 2}";
  // return is_valid_partition({1, 1, 1, 2});
  // DEBUG << "Input: {1, 1, 1, 1, 2, 3}";
  // return is_valid_partition({1, 1, 1, 1, 2, 3});
  std::vector<int> input;
  int value;
  while (std::cin >> value) {
    input.push_back(value);
  }
  return is_valid_partition(input);
}
