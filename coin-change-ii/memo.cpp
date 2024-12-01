#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <vector>

int num_ways_to_make_amount(int amount, const std::vector<int>& denominations) {
  // memo :: (which coin index, amount) -> answer
  std::unordered_map<std::int64_t, int> memo;

  const auto count = [&memo, &denominations](int coin_index, int amount, auto &&recur) -> int {
    if (coin_index < 0 || amount < 0) {
      return 0;
    }
    if (amount == 0) {
      return 1;
    }
    const auto key = (std::int64_t(coin_index) << 31) | amount;
    const auto found = memo.find(key);
    if (found != memo.end()) {
      return found->second;
    }

    return memo[key] = recur(coin_index, amount - denominations[coin_index], recur) + recur(coin_index - 1, amount, recur);
  };

  return count(denominations.size() - 1, amount, count);
}

class Solution {
public:
    int change(int amount, std::vector<int>& coins) {
      std::sort(coins.begin(), coins.end());
      return num_ways_to_make_amount(amount, coins);
    }
};

#include <iostream>

int main() {
  int amount;
  std::vector<int> coins;
  std::cin >> amount;
  int coin;
  while (std::cin >> coin) {
    coins.push_back(coin);
  }
  std::cout << Solution().change(amount, coins) << '\n';
}
