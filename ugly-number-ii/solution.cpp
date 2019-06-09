#include <set>
#include <limits>

int nthUglyNumber(int n);

// leetcode.com boilerplate
class Solution {
public:
    int nthUglyNumber(int n) {
        return ::nthUglyNumber(n);
    }
};

int nthUglyNumber(int n)
{
    std::set<int> numbers;
    numbers.insert(1);

    while (--n) {
        const int intMax = std::numeric_limits<int>::max();
        const int smallest = *numbers.begin();
        
        if (intMax / 2 >= smallest)
            numbers.insert(smallest * 2);
        if (intMax / 3 >= smallest)
            numbers.insert(smallest * 3);
        if (intMax / 5 >= smallest)
            numbers.insert(smallest * 5);
        
        numbers.erase(numbers.begin());
    }

    return *numbers.begin();
}