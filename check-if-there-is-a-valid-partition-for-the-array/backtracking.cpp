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

#include <cassert>
#include <cstddef>
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

bool is_valid_partition(const vector<int>& nums) {
  struct Piece {
    size_t index; // into `nums`
    int criterion; // 1, 2, or 3; corresponding to the cases from the problem
                   // or 0 for "haven't tried it yet."
  };

  vector<Piece> pieces;
  size_t i = 0; // offset into `nums`
  pieces.push_back(Piece{i, 0});
  while (i < nums.size()) {
    DEBUG << "i: " << i << "  pieces.size(): " << pieces.size();
    switch (pieces.back().criterion) {
    case 0: {
      // Try case 1: Subarray consists of two equal elements.
      if (i + 2 <= nums.size() && nums[i] == nums[i + 1]) {
        DEBUG << "    matched case 1";
        pieces.back().criterion = 1;
        i += 2;
        pieces.push_back(Piece{i, 0});
        continue;
      }
    }
    // fall through
    case 1: {
      // Try case 2: Subarray consists of three equal elements.
      if (i + 3 <= nums.size() && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2]) {
        DEBUG << "    matched case 2";
        pieces.back().criterion = 2;
        i += 3;
        pieces.push_back(Piece{i, 0});
        continue;
      }
    }
    // fall through
    case 2: {
      // Try case 3: Subarray consists of a length three plus-one-each-time.
      if (i + 3 <= nums.size() && nums[i + 1] == nums[i] + 1 && nums[i + 2] == nums[i + 1] + 1) {
        DEBUG << "    matched case 2";
        pieces.back().criterion = 3;
        i += 3;
        pieces.push_back(Piece{i, 0});
        continue;
      }
    }
    } // switch (pieces.back().criterion)
  
    DEBUG << "    didn't match any cases";
    // We've tried everything for the current position. Try to backtrack,
    // and try the next possible match in the previous piece.
    do {
      pieces.pop_back();
      if (pieces.empty()) {
        // We've tried everything from the start. There's no match.
        return false;
      }
    } while (pieces.back().criterion == 3);
    i = pieces.back().index;
    DEBUG << "    after rewind, i: " << i << "  pieces.size(): " << pieces.size() << "  pieces.back().criterion: " << pieces.back().criterion;
  } // while (i < nums.size())
  
  assert(i == nums.size());
  // We found a match.
  return true;
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
