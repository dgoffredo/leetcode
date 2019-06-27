#include <cassert>
#include <list>
#include <string>

std::string least_after_removing(const std::string& number,
                                 int                howManyToRemove);

class Solution {
public:
    std::string removeKdigits(std::string num, int k) {
        return least_after_removing(num, k);
    }
};

std::string least_after_removing(const std::string& number,
                                 int                howManyToRemove)
{
    // The plan is to convert `number` into a linked list, and then
    // successively remove (starting from the front) any digit that is followed
    // by a lesser digit (thus reducing the resulting integer value).
    
    assert(howManyToRemove <= int(number.size()));

    std::list<char> digits(number.begin(), number.end());
    auto prev = digits.begin();
    auto next = prev;
    if (next != digits.end()) {
        ++next;
    }

    while (howManyToRemove) {
        if (next == digits.end()) {
            // got to the end, so remove from the end
            next = digits.erase(prev);
            --howManyToRemove;
            prev = digits.end();
            if (!digits.empty()) {
                --prev;
            }
        }
        else if (*next < *prev) {
            // next character is smaller, so we benefit from removing previous
            next = digits.erase(prev);
            --howManyToRemove;
            prev = next;
            if (next == digits.begin()) {
                ++next;
            }
            else {
                --prev;
            }
        }
        else {
            ++prev;
            ++next;
        }
    }

    if (digits.empty()) {
        digits.push_back('0');
    }

    // remove leading zeroes, but never emptying the list
    while (int(digits.size()) > 1 && digits.front() == '0') {
        digits.pop_front();
    }

    return std::string(digits.begin(), digits.end());
}
