#include <bit>

class Solution {
public:
    int kthGrammar(int n, int k) {
      return std::popcount(unsigned(k) - 1) % 2;        
    }
};
