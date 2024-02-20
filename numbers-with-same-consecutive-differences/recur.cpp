#include <vector>

using namespace std;

void f(int n, int k, int number, int digit, vector<int>& solutions);

class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
       vector<int> solutions;
       for (int number = 1; number < 10; ++number) {
        f(n, k, number, number, solutions);
       }
       return solutions;
    }
};

void f(int n, int k, int number, int digit, vector<int>& solutions) {
  if (n == 1) {
    solutions.push_back(number);
    return;
  }

  const int digit_plus = digit + k;
  if (digit_plus < 10) {
    f(n - 1, k, number * 10 + digit_plus, digit_plus, solutions);
  }

  const int digit_minus = digit - k;
  if (digit_minus >= 0 && digit_minus != digit_plus) {
    f(n - 1, k, number * 10 + digit_minus, digit_minus, solutions);
  }
}
