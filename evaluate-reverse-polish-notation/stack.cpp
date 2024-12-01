#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

int evaluate(const std::vector<std::string>& tokens) {
  std::vector<int> stack;

  for (const std::string& token : tokens) {
    const char first = token[0];
    if ((first >= '0' && first <= '9') || token.size() > 1) {
      stack.push_back(std::atoi(token.c_str()));
      continue;
    }

    // It's an operation.
    const int right = stack.back();
    stack.pop_back();
    const int left = stack.back();
    stack.pop_back();
    assert(token.size() == 1);
    int number;
    switch (first) {
    case '+':
      number = left + right;
      break;
    case '-':
      number = left - right;
      break;
    case '*':
      number = left * right;
      break;
    default:
      assert(first == '/');
      number = left / right;
      break;
    }
    stack.push_back(number);
  }

  return stack.back();
}

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
      return evaluate(tokens);
    }
};
