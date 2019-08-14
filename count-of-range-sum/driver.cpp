#include "linearithmic.cpp"

#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
    int lower;
    int upper;
    std::cin >> lower >> upper;

    std::vector<int> numbers;
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(numbers));

    std::cout << Solution().countRangeSum(numbers, lower, upper) << "\n";
}
