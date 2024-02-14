#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

bool is_valid_partition(const vector<int>& nums);

class Solution {
public:
    bool validPartition(vector<int>& nums) {
       return is_valid_partition(nums); 
    }
};

bool is_valid_partition(const vector<int>& nums) {
  // Each `int` in `pieces` is one of (1, 2, 3), corresponding to which way
  // the piece of the partition matched from the problem statement.
  // The special value zero means "haven't tried any of the cases yet."
  // The width of each piece can be deduced from the match {1: 2, 2: 3, 3: 3}. 
  vector<int> pieces;
  size_t i = 0; // offset into `nums`
  pieces.push_back(0);
  while (i < nums.size()) {
    std::cout << "nums.size(): " << nums.size() << "  i: " << i << "  pieces.size(): " << pieces.size() << "  pieces.back(): " << pieces.back() << std::endl;
    switch (pieces.back()) {
    case 0: {
      // Try case 1: Subarray consists of two equal elements.
      if (i + 2 <= nums.size() && nums[i] == nums[i + 1]) {
        std::cout << "    matched case 1" << std::endl;
        pieces.back() = 1;
        i += 2;
        pieces.push_back(0);
        continue;
      }
    }
    // fall through
    case 1: {
      // Try case 2: Subarray consists of three equal elements.
      if (i + 3 <= nums.size() && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2]) {
        std::cout << "    matched case 2" << std::endl;
        pieces.back() = 2;
        i += 3;
        pieces.push_back(0);
        continue;
      }
    }
    // fall through
    case 2: {
      // Try case 3: Subarray consists of a length three plus-one-each-time.
      if (i + 3 <= nums.size() && nums[i + 1] == nums[i] + 1 && nums[i + 2] == nums[i + 1] + 1) {
        std::cout << "    matched case 3" << std::endl;
        pieces.back() = 3;
        i += 3;
        pieces.push_back(0);
        continue;
      }
    }
    } // switch (pieces.back())
  
    // We've tried everything for the current position. Try to backtrack,
    // and try the next possible match in the previous piece.
    pieces.pop_back();
    if (pieces.empty()) {
      // We've tried everything from the start. There's no match.
      return false;
    }

    for (;;) {
      std::cout << "    i: " << i << "   pieces.size(): " << pieces.size() << "   pieces.back(): " << pieces.back() << std::endl;
      if (pieces.back() == 1) {
        i -= 2;
        ++pieces.back();
        break;
      } else if (pieces.back() == 2) {
        i -= 3;
        ++pieces.back();
        break;
      } else {
        assert(pieces.back() == 3);
        // Tried everything for this piece. Backtrack more.
        i -= 3;
        pieces.pop_back();
        if (pieces.empty()) {
          // We've tried everything from the start. There's no match.
          return false;
        }
      }
    }
  } // while (i < nums.size())
  
  // We found a match.
  return true;
}

// test
int main() {
  // std::cout << "Input: {4, 4, 4, 5, 6}" << std::endl;
  // return is_valid_partition({4, 4, 4, 5, 6});
  // std::cout << "Input: {1, 1, 1, 2}" << std::endl;
  // return is_valid_partition({1, 1, 1, 2});
  std::cout << "Input: {1, 1, 1, 1, 2, 3}" << std::endl;
  return is_valid_partition({1, 1, 1, 1, 2, 3});
}
