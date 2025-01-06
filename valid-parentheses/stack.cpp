#include <string>
#include <vector>

bool balanced(const std::string& str) {
    std::vector<char> stack;
    for (const char ch : str) {
        switch (ch) {
        case '(':
        case '{':
        case '[':
            stack.push_back(ch);
            break;
        case ')':
            if (stack.empty() || stack.back() != '(') {
                return false;
            }
            stack.pop_back();
            break;
        case '}':
            if (stack.empty() || stack.back() != '{') {
                return false;
            }
            stack.pop_back();
            break;
        case ']':
            if (stack.empty() || stack.back() != '[') {
                return false;
            }
            stack.pop_back();
        }
    }
    return stack.empty();
}

class Solution {
public:
    bool isValid(const std::string str) {
        return balanced(str);        
    }
};

