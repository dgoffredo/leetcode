#include <string>

bool balanced(const std::string& str) {
    int parens = 0;
    int braces = 0;
    int brackets = 0;
    for (const char ch : str) {
        switch (ch) {
        case '(': ++parens; break;
        case '{': ++braces; break;
        case '[': ++brackets; break;
        case ')':
            if (parens == 0) return false;
            --parens; break;
        case '}':
            if (braces == 0) return false;
            --braces; break;
        case ']':
            if (brackets == 0) return false;
            --brackets; break;
        }
    }

    return parens == 0 && braces == 0 && brackets == 0;
}

class Solution {
public:
    bool isValid(const std::string str) {
        return balanced(str);        
    }
};
