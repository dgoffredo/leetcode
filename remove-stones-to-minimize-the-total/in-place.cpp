#include <queue>

using namespace std;

int min_stone_sum(vector<int>& piles, int k);

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
      return min_stone_sum(piles, k);        
    }
};

int min_stone_sum(vector<int>& piles, int k) {
  std::make_heap(piles.begin(), piles.end());
  int sum = 0;
  for (const int pile : piles) {
    sum += pile;
  }

  for (int i = 0; i < k; ++i) {
    int pile = piles.front();
    int removed = pile / 2;
    int new_pile = pile - removed;
    sum -= removed;
    std::pop_heap(piles.begin(), piles.end());
    piles.back() = new_pile;
    std::push_heap(piles.begin(), piles.end());
  }

  return sum;
}
