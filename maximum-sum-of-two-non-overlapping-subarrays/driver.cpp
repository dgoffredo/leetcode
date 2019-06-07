#include "quadratic.cpp"

#include <iostream>
#include <vector>

int main()
{
    int L, M;

    std::cin >> L >> M;

    std::vector<int> numbers;
    int              number;
    while (std::cin >> number) {
        numbers.push_back(number);
    }

    std::cout << Solution().maxSumTwoNoOverlap(numbers, L, M) << "\n";
}