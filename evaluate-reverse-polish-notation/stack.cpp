#include <cassert>
#include <sstream>
#include <string>
#include <vector>

int evaluate(const std::vector<std::string>& tokens) {
  std::istringstream stream;
  std::vector<int> stack;
  int number;

  for (const std::string& token : tokens) {
    stream.clear();
    stream.str(token);
    if (stream >> number) {
      stack.push_back(number);
      continue;
    }

    const int right = stack.back();
    stack.pop_back();
    const int left = stack.back();
    stack.pop_back();
    assert(token.size() == 1);
    const char operation = token[0];
    switch (operation) {
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
      assert(operation == '/');
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
