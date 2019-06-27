#include <algorithm>
#include <cassert>
#include <iostream>  // debugging only
#include <iterator>
#include <list>
#include <utility>
#include <vector>

// Here's the plan.  There exists some `i` with `0 <= i <= k` such that the
// answer has `i` numbers from `left` and `k - i` numbers from `right`.
//
// The trick is to recognize that if the result takes `i` numbers from `left`
// and `k - i` numbers from `right`, then in particular it takes the maximal
// subsequence of length `i` from `left` and the maximal subsequence of length
// `k - i` from `right`, and then merges them such that the result is maximal.
//
// So, for each `i` from `0` to `k`:
//
// - Find the maximal `i`-length subsequence from `left`.              O(m + k)
// - Find the maximal `k - i`-length subsequence from `right`.         O(n + k)
// - Compute the maximal merger of the two subsequences.               O(m * n)
// - Compare this with the largest merger so far computed.             O(m + n)
//
// The resulting maximum, after all `k` possiblities have been examined, is the
// answer.
//
// The overall runtime complexity is O((2m + 2n + 2k + m * n) * k), which is
// O(m*k + n*k + m*n*k + k^2).  This could be improved by computing the
// "maximal merger" operation in linear time using suffix arrays, but that's
// hard so I'll avoid it if I can.

std::vector<int> maxMerger(const std::vector<int>& left,
                           const std::vector<int>& right);

std::vector<int> maxSubsequence(const std::vector<int>& sequence, int length);

std::vector<int> maxMergedSubsequences(std::vector<int>& left,
                                       std::vector<int>& right,
                                       int               length);

class Solution {
public:
    std::vector<int> maxNumber(std::vector<int>& nums1,
                               std::vector<int>& nums2,
                               int k) {
        return maxMergedSubsequences(nums1, nums2, k);
    }
};

std::vector<int> maxMerger(const std::vector<int>& left,
                           const std::vector<int>& right)
{
    std::vector<int> result;

    auto i = left.begin();
    auto j = right.begin();
    for (;;) {
        if (i == left.end()) {
            result.insert(result.end(), j, right.end());
            break;
        }
        if (j == right.end()) {
            result.insert(result.end(), i, left.end());
            break;
        }

        if (*i > *j) {
            result.push_back(*i);
            ++i;
        }
        else if (*j > *i) {
            result.push_back(*j);
            ++j;
        }
        else {
            // here's the part that makes it quadratic
            const bool leftIsLess =
                std::lexicographical_compare(i, left.end(), j, right.end());

            if (leftIsLess) {
                result.push_back(*j);
                ++j;
            }
            else {
                result.push_back(*i);
                ++i;
            }
        }
    }

    return result;
}

// Turns out that the following commented out implementation is incorrect.
/*
std::vector<int> maxMerger(std::vector<int>& left, std::vector<int>& right)
{
    // first some corner cases
    if (left.empty()) {
        return right;
    }

    if (right.empty()) {
        return left;
    }

    // the general solution
    const int L = left.size();
    const int R = right.size();

    // This makes some corner cases below easier. We've preserved the "real"
    // lengths in `L` and `R`.
    left.push_back(-1);
    right.push_back(-1);

    class Table {
        const int         columns;
        std::vector<char> data;
      public:
        Table(int rows, int columns)
        : columns(columns)
        , data(rows * columns)
        {}

        char& operator()(int row, int column) {
            return data[row * columns + column];
        }
    } table(L + 1, R + 1);

    // 'L' means "take from `left`," and 'R' means "take from `right`."
    //
    for (int i = 0; i < L; ++i) {
        table(i, R) = 'L';
    }

    for (int j = 0; j < R; ++j) {
        table(L, j) = 'R';
    }

    // Proceed from the bottom right, upwards in strips.
    for (int j = R - 1; j >= 0; --j) {
        for (int i = L - 1; i >= 0; --i) {
            if (left[i] > right[j]) {
                table(i, j) = 'L';
            }
            else if (right[j] > left[i]) {
                table(i, j) = 'R';
            }
            else if (left[i + 1] > right[j + 1]) {
                table(i, j) = 'L';
            }
            else if (right[j + 1] > left[i + 1]) {
                table(i, j) = 'R';
            }
            else {
                // arbitrary tie breaker
                table(i, j) = 'L';
            }
        }
    }

    std::vector<int> result;
    result.reserve(L + R);
    // The table has been populated.  Now we walk through it, appending to
    // `result` a digit from whichever of `left` or `right` the currently entry
    // in the table indicates.
    int i = 0;
    int j = 0;
    while (i != L || j != R) {
        switch (table(i, j)) {
          case 'L':
              std::cout << "L says to take " << left[i] << " from left\n";
              result.push_back(left[i]);
              ++i;
              break;
          case 'R':
              std::cout << "R says to take " << right[j] << " from right\n";
              result.push_back(right[j]);
              ++j;
              break;
        }
    }

    // put them back
    left.pop_back();
    right.pop_back();

    return result;
}
*/

std::vector<int> maxSubsequence(const std::vector<int>& sequence, int length)
{
    // std::cout << "maxSubsequence called on: ";
    // std::copy(sequence.begin(), sequence.end(),
    //           std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\ndesired length is " << length << '\n';

    assert(int(sequence.size()) >= length);

    if (length ==  0) {
        return std::vector<int>();
    }
    if (int(sequence.size()) == length) {
        return sequence;
    }

    std::list<int> numbers(sequence.begin(), sequence.end());
    std::list<int>::iterator prev = numbers.begin();
    std::list<int>::iterator next = prev;
    ++next;
        
    while (int(numbers.size()) > length)
    {
        if (next == numbers.end()) {
            // std::cout << "reached the end, so removing the last\n";
            // std::cout << "... before I do this, the length is currently " << numbers.size() << '\n';
            next = numbers.erase(prev);  // and thus `next == numbers.end()`
            prev = numbers.end();
            if (!numbers.empty()) {
                --prev;
            }
        }
        else if (*next > *prev) {
            // std::cout << *next << " > " << *prev << ", so removing " << *prev << '\n';
            // std::cout << "... before I do this, the length is currently " << numbers.size() << '\n';
            // std::cout << "... prev is " << std::distance(numbers.begin(), prev) << " from the beginning.\n";
            next = numbers.erase(prev);  // Ah, what if we removed the first element?
            prev = next;
            if (prev == numbers.begin()) {
                ++next;
            }
            else {
                --prev;
            }
        }
        else {
            // std::cout << *prev << "->" << *next << " is fine, so moving on\n";
            ++prev;
            ++next;
        }
    }

    return std::vector<int>(numbers.begin(), numbers.end());
}

std::vector<int> maxMergedSubsequences(std::vector<int>& left,
                                       std::vector<int>& right,
                                       int               length)
{
    const int L = left.size();
    const int R = right.size();

    std::vector<int> maxSoFar;

    for (int i = 0; i <= length; ++i) {
        if (i > L || length - i > R) {
            // there has to be enough to take from each
            continue;
        }

        std::vector<int> leftSub = maxSubsequence(left, i);
        std::vector<int> rightSub = maxSubsequence(right, length - i);
        std::vector<int> merged = maxMerger(leftSub, rightSub);

        if (merged > maxSoFar) {
            maxSoFar = std::move(merged);
        }
    }

    assert(int(maxSoFar.size()) == length);
    return maxSoFar;
}
