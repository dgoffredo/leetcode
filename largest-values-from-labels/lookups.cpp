#include <algorithm>
#include <unordered_map>
#include <vector>

  int highest_value_basket(const std::vector<int>& values, const std::vector<int>& labels, int max_items, int max_dupes) {
    std::unordered_map<int, int> num_taken; // label -> count
    struct Item {
      int value;
      int *count;
    };
    std::vector<Item> items;
    const int n = values.size();
    for (int i = 0; i < n; ++i) {
      items.push_back(Item{.value = values[i], .count = &num_taken[labels[i]]});
    }
    struct ByValueDesc {
      bool operator()(const Item& left, const Item& right) const {
        return left.value > right.value;
      }
    };
    std::sort(items.begin(), items.end(), ByValueDesc{});

    int total_value = 0;
    int total_taken = 0;
    for (const Item& item : items) {
      if (total_taken == max_items) {
        break;
      }
      if (*item.count == max_dupes) {
        continue;
      }
      total_value += item.value;
      ++*item.count;
      ++total_taken;
    }

    return total_value;
  }

class Solution {
public:
    int largestValsFromLabels(std::vector<int>& values, std::vector<int>& labels, int numWanted, int useLimit) {
       return highest_value_basket(values, labels, numWanted, useLimit);
    }
};
