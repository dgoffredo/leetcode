#include <cassert>
#include <cmath>
#include <vector>

std::vector<int> serve_queries(int number, const std::vector<std::vector<int>>& queries) {
  std::vector<int> answers;

  std::vector<int> exponents;
  for (int n = number, i = 0; n; n >>= 1, ++i) {
    if (n & 1) {
      exponents.push_back(i);
    }
  }

  for (const std::vector<int>& query : queries) {
    assert(query.size() == 2);
    const int low = query[0];
    const int high = query[1];
    int exponent = 0;
    for (int i = low; i <= high; ++i) {
      exponent += exponents[i];
    }
    // We want to append to `answers` the number 2**exponent mod (10**9 + 7).
    const int mod = 1'000'000'007;
    int answer = 1;
    for (int i = 0; i < exponent; ++i) {
      answer *= 2;
      while (answer >= mod) {
        answer -= mod;
      }
    }
    answers.push_back(answer);
  }

  return answers;
}

class Solution {
public:
    std::vector<int> productQueries(int n, std::vector<std::vector<int>>& queries) {
       return serve_queries(n, queries);
    }
};

#include <iostream>

int main() {
  int number;
  std::cin >> number;

  std::vector<std::vector<int>> queries;
  for (;;) {
    int low, high;
    std::cin >> low;
    if (!std::cin) {
      break;
    }
    std::cin >> high;
    if (!std::cin) {
      return 1;
    }
    queries.push_back({low, high});
  }

  const std::vector<int> answers = Solution().productQueries(number, queries);
  for (const int answer : answers) {
    std::cout << ' ' << answer;
  }
  std::cout << '\n';
}
