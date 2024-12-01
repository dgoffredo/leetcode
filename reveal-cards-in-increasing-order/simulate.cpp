#include <deque>
#include <queue>
#include <vector>

std::vector<int> stack_the_deck(const std::vector<int>& deck) {
  std::deque<int> input_order;
  for (int i = 0; i < int(deck.size()); ++i) {
    input_order.push_back(i);
  }

  std::vector<int> output_order;
  output_order.reserve(deck.size());
  for (;;) {
    output_order.push_back(input_order.front());
    input_order.pop_front();
    if (input_order.empty()) {
      break;
    }
    input_order.push_back(input_order.front());
    input_order.pop_front();
  }

  // We want a min-heap, but the default is a max-heap. So, use a comparator (a
  // "less than") function that returns "greater than."
  struct Reversed {
    bool operator()(int left, int right) const {
      return left > right;
    }
  };
  std::priority_queue<int, std::vector<int>, Reversed> values(deck.begin(), deck.end());
  std::vector<int> result(deck.size());
  for (const int i : output_order) {
    const int next_value = values.top();
    result[i] = next_value;
    values.pop();
  }

  return result;
}

class Solution {
public:
  std::vector<int> deckRevealedIncreasing(std::vector<int>& deck) {
    return stack_the_deck(deck);
  }
};
