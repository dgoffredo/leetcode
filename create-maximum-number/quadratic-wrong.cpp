#include <iostream>  // debugging only
#include <vector>

std::vector<int> maxMerger(std::vector<int>& left, std::vector<int>& right);

class Solution {
public:
    std::vector<int> maxNumber(std::vector<int>& nums1,
                               std::vector<int>& nums2,
                               int k) {
        std::vector<int> result = maxMerger(nums1, nums2);
        if (int(result.size()) > k) {
            // This solution calculates the total max number, so if
            // `k < nums1.size() + nums2.size()`, we have to truncate the
            // result.
            result.resize(k);
        }

        return result;
    }
};


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

    return result;
}
