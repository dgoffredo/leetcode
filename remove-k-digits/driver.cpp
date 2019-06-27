#include <linear.cpp>

#include <cassert>
#include <iostream>
#include <string>

int main()
{
    std::string number;
    std::cin >> number;
    assert(std::cin);

    int k;
    std::cin >> k;
    assert(std::cin);

    std::cout << Solution().removeKdigits(number, k) << '\n';
}