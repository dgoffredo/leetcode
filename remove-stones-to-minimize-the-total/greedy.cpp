#include <queue>

using namespace std;

int min_stone_sum(const vector<int>& piles, int k);

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
      return min_stone_sum(piles, k);        
    }
};

int min_stone_sum(const vector<int>& piles, int k) {
  std::priority_queue<int> heap;
  // heap.reserve(piles.size());
  int sum = 0;
  for (const int pile : piles) {
    heap.push(pile);
    sum += pile;
  }

  for (int i = 0; i < k; ++i) {
    int pile = heap.top();
    int removed = pile / 2;
    int new_pile = pile - removed;
    sum -= removed;
    heap.pop();
    heap.push(new_pile);
  }

  return sum;
}
