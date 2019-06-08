
#include <cassert>
#include <vector>

int largestFullRectangle(const std::vector<std::vector<char>>& matrix);

// leetcode.com boilerplate
class Solution {
public:
    int maximalRectangle(const std::vector<std::vector<char>>& matrix) {
        return largestFullRectangle(matrix);
    }
};

template <typename Cell>
class Grid {
    std::vector<Cell> data;

  public:
    const int rows;
    const int columns;

    Grid(int rows, int columns)
    : data(rows * columns)
    , rows(rows)
    , columns(columns)
    {}

    Cell& operator()(int row, int column) {
        // Column-major order, because of the way we'll be iterating through.
        // Kind of doesn't matter, though, because we'll need to read a
        // neighbor in the previous column, too.
        return data[rows * column + row];
    }

    const Cell& operator()(int row, int column) const {
        return data[rows * column + row];
    }
};

int rectangleSum(const Grid<int>& sums,
                 int              iTopLeft,
                 int              jTopLeft,
                 int              iBottomRight,
                 int              jBottomRight)
{
    const auto inBounds = [&sums](int i, int j) {
        return i >= 0
            && j >= 0
            && i < sums.rows
            && j < sums.columns;
    };

    const auto maybeAt = [&inBounds, &sums](int i, int j) {
        return inBounds(i, j) ? sums(i, j) : 0;
    };

    assert(inBounds(iTopLeft, jTopLeft));
    assert(inBounds(iBottomRight, jBottomRight));

    return sums(iBottomRight, jBottomRight)
         - maybeAt(iTopLeft - 1, jBottomRight)
         - maybeAt(iBottomRight, jTopLeft - 1)
         + maybeAt(iTopLeft - 1, jTopLeft - 1);
}

int largestFullRectangle(const std::vector<std::vector<char>>& matrix)
{
    // The plan is to build up a matrix whose cells contain the count of ones
    // contained within the rectangle beginning at (0, 0) (top left) and ending
    // at (and including) (i, j) (bottom right).
    //
    // While building up this matrix, we can check rectangles starting at each
    // (i', j') less than (i, j) for whether it contains all ones, which is the
    // same as its value being the same as its area. The main optimization is
    // that you can calculate the sum of a rectangle from (i', j') to (i, j)
    // in constant time using some geometry:
    //
    //  origin
    //     O-----------
    //     |          |
    //     |          |
    //     |    X-----A
    //     |    |     |
    //     -----B-----Y
    //
    // The sum of the rectangle starting at X and going to Y is the following
    // expression, where S is the "sums matrix" described above:
    //
    //     S[Y] - S[A] - S[B] + S[X]
    //
    // You can see how it works: S[Y] contains the region we want but also the
    // L-shaped stuff above A and left of B. So, we subtract those, but then we
    // substracted the region diagonally above X twice, so we add it once to
    // have only removed it once in total.
    //
    // As we go through the input building up 'S', we keep track of the area of
    // the largest rectangle whose area is equal to its value (count). This is
    // the answer once we've reached the end of the input.
    //
    // Actually, I think I'll go through it once to build up 'S', and then
    // another time to find the max; just to make things easier to read.

    // Some silly edge cases: if it's empty in either dimension, then the
    // answer is zero.
    if (matrix.empty() || matrix[0].empty()) {
        return 0;
    }

    // Let's consider the input to be column-major order, too, since the
    // rotation doesn't affect the answer.
    const int numRows    = matrix[0].size();
    const int numColumns = matrix.size();

    const auto isOccupied = [&matrix](int row, int column) {
        return matrix[column][row] == '1';
    };

    Grid<int> sums(numRows, numColumns);

    // Now we know that there is at least one row and one column. It's
    // convenient to fill the first row and first column separately, since the
    // rule for how to build up the sum is special in those cases.
    sums(0, 0) = isOccupied(0, 0);

    for (int i = 1; i < numRows; ++i) {
        sums(i, 0) = sums(i - 1, 0) + isOccupied(i, 0);
    }

    for (int j = 1; j < numColumns; ++j) {
        sums(0, j) = sums(0, j - 1) + isOccupied(0, j);
    }

    // For the rest of the sums, the sum at a point (i, j) is the left neighbor
    // plus the top neighbor minus the top-left diagonal neighbor. It's a
    // similar reasoning to the geometric trick described at the beginning of
    // this function.
    for (int j = 1; j < numColumns; ++j) {
        for (int i = 1; i < numRows; ++i) {
            sums(i, j) =   sums(i - 1, j)
                         + sums(i, j - 1)
                         - sums(i - 1, j - 1)
                         + isOccupied(i, j);
        }
    }

    // Now that we have the sums, we can find the largest rectangle having all
    // ones inside. Remember that a rectangle has all ones inside if its sum
    // is equal to its area.
    int maxArea = 0;

    for (int jTopLeft = 0; jTopLeft < numColumns; ++jTopLeft) {
        for (int iTopLeft = 0; iTopLeft < numRows; ++iTopLeft) {
            if (!isOccupied(iTopLeft, jTopLeft)) {
                // If the top left is a zero, then no such rectangle will help.
                continue;
            }
            
            int jBottomEnd = numColumns;
            int iBottomEnd = numRows;
            for (int jBottomRight = jTopLeft;
                 jBottomRight < jBottomEnd;
                 ++jBottomRight) {
                for (int iBottomRight = iTopLeft;
                     iBottomRight < iBottomEnd;
                     ++iBottomRight) {
                    if (!isOccupied(iBottomRight, jBottomRight)) {
                        // If the bottom right is a zero, then no such
                        // rectangle will help. In addition, nor will any that
                        // contains this cell.
                        iBottomEnd = iBottomRight;
                        continue;
                    }

                    const int width  = jBottomRight - jTopLeft + 1;
                    const int height = iBottomRight - iTopLeft + 1;
                    const int area   = width * height;
                    const int sum    = rectangleSum(sums,
                                                    iTopLeft, 
                                                    jTopLeft, 
                                                    iBottomRight, 
                                                    jBottomRight);
                    if (area == sum && area > maxArea) {
                        maxArea = area;
                    }
                }
            }
        }
    }

    return maxArea;
}