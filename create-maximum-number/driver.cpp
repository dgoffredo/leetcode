
#include <quadratic.cpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
class Solution {
public:
    std::vector<int> maxNumber(std::vector<int>& nums1,
                               std::vector<int>& nums2,
                               int k);
}
*/

int main()
{
    std::string buffer;
    std::getline(std::cin, buffer);
    
    std::istringstream line(buffer);
    
    int number;
    std::vector<int> left;
    while (line >> number)
        left.push_back(number);

    std::getline(std::cin, buffer);
    line.clear();
    line.str(buffer);

    std::vector<int> right;
    while (line >> number)
        right.push_back(number);

    std::cin >> number;

    const std::vector<int> result = Solution().maxNumber(left, right, number);
    std::cout << "result:";
    for (const int digit : result)
        std::cout << ' ' << digit;

    std::cout << '\n';
}