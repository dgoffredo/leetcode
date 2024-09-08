#include <cmath>
#include <vector>

struct FactorPair {
  int lesser;
  int greater;
  int abs_diff() const {
    return greater - lesser;
  }
};

FactorPair closest_factors(int n) {
  FactorPair result{.lesser = 1, .greater = n};
  const int sqrt = std::sqrt(n);
  for (int i = 2; i <= sqrt; ++i) {
    if (n % i) {
      continue;
    }
    FactorPair pair{.lesser = i, .greater = n / i};
    if (pair.abs_diff() < result.abs_diff()) {
      result = pair;
    }
  }
  return result;
}

FactorPair closest_divisors(int n) {
  const FactorPair n_plus_1 = closest_factors(n + 1);
  const FactorPair n_plus_2 = closest_factors(n + 2);
  return n_plus_1.abs_diff() < n_plus_2.abs_diff() ? n_plus_1 : n_plus_2;
}

class Solution {
public:
    std::vector<int> closestDivisors(int num) {
       auto divisors = closest_divisors(num);
       return {divisors.lesser, divisors.greater};
    }
};
