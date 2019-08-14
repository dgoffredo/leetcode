#ifdef QUADRATIC
#include "quadratic.cpp"
#elif defined(LINEARITHMIC)
#include "linearithmic.cpp"
#else
#error Define either QUADRATIC or LINEARITHMIC
#endif

#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> numbers;
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(numbers));
    std::cout << Solution().reversePairs(numbers) << "\n";
}
