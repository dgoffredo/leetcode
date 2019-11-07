#include <algorithm>
#include <limits>
#include <vector>

#ifdef TEST
#include <iostream>
#include <iterator>
#endif

void radixSort(std::vector<int>& numbers);

std::vector<int> singleNumbers(const std::vector<int>& numbers);

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
        #ifdef TEST
        std::cout << "before sort:\n";
        for (int number : nums) {
            std::cout << number << "\n";
        }
        #endif

        radixSort(nums);

        #ifdef TEST
        std::cout << "after sort:\n";
        for (int number : nums) {
            std::cout << number << "\n";
        }
        #endif

        return singleNumbers(nums);
    }
};

template <typename Iter>
auto partitionByBit(Iter begin, Iter end, int bit) {
    return std::stable_partition(begin,
                                 end,
                                 [bit](const auto& number) {
                                     return ((1 << bit) & number) >> bit;
                                 });
}

template <typename Iter>
void negateElements(Iter begin, Iter end) {
    for (Iter it = begin; it != end; ++it) {
        *it *= -1;
    }
}

void radixSort(std::vector<int>& numbers) {
    const auto nonnegatives =
        std::stable_partition(numbers.begin(),
                              numbers.end(),
                              [](const auto& number) { return number < 0; });

    #ifdef TEST
    std::cout << "there are " << std::distance(numbers.begin(), nonnegatives)
              << " negative numbers in the input.\n";
    #endif

    // Go all positive.  Don't forget to reverse them and flip the sign again
    // before the end.
    negateElements(numbers.begin(), nonnegatives);

    #ifdef TEST
    std::cout << "after negating the negative numbers:\n";
        for (int number : numbers) {
            std::cout << number << "\n";
        }
    #endif

    // Sort in buckets by bit, except for the sign bit.  Do this separately for
    // the negatives and nonnegatives.
    for (int bit = 0; bit < std::numeric_limits<int>::digits; ++bit) {
        partitionByBit(numbers.begin(), nonnegatives, bit);
        partitionByBit(nonnegatives, numbers.end(), bit);
    }

    // Put the negatives back.
    negateElements(numbers.begin(), nonnegatives);

    // TODO: horrible.  Everything is backwards.  Reverse it all.
    // TODO: not really necessary, since the next algo works backwards, but
    //       might as well...
    std::reverse(nonnegatives, numbers.end());
}

std::vector<int> singleNumbers(const std::vector<int>& numbers) {
    std::vector<int> result;
    const int        size = numbers.size();

    for (int i = 0; i < size; ++i) {
        const bool leftDifferent =
            i == 0 || numbers[i] != numbers[i - 1];
        const bool rightDifferent =
            i == size - 1 || numbers[i] != numbers[i + 1];

        if (leftDifferent && rightDifferent) {
            result.push_back(numbers[i]);
        }
    }

    return result;
}

#ifdef TEST

int main() {
    // std::vector<int> input{1,2,1,3,2,5};
    std::vector<int> input{-1,-2,-1,3,-2,5};
    const auto answer = Solution().singleNumber(input);
    std::cout << answer[0] << " " << answer[1] << "\n";
}

#endif
