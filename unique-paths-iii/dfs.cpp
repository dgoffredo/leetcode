#include <vector>

int numCompletePaths(std::vector<std::vector<int>>& grid);

// leetcode.com boilerplate
class Solution {
public:
    int uniquePathsIII(std::vector<std::vector<int>>& grid) {
        return numCompletePaths(grid);
    }
};

int numCompletePaths(std::vector<std::vector<int>>& grid) {
    const int START = 1,
              EXIT  = 2,
              FLOOR = 0,
              WALL  = -1;

    const int m = grid.size(),
              n = grid[0].size();

    const auto mark = [&](int i, int j) {
        grid[i][j] += 4;
    };

    const auto unmark = [&](int i, int j) {
        grid[i][j] -= 4;
    };

    const auto marked = [&](int i, int j) {
        return grid[i][j] > EXIT;
    };

    const auto viable = [&](int i, int j) {
        return i >= 0
            && i < m
            && j >= 0
            && j < n
            && !marked(i, j)
            && grid[i][j] != WALL;
    };

    // Find the number of blank squares (do I count start? yes) and the
    // starting position.
    int floorSpace = 0;
    int iStart, jStart;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == START) {
                iStart = i, jStart = j;
                ++floorSpace;
            }
            else if (grid[i][j] == FLOOR) {
                ++floorSpace;
            }
        }
    }

    int numPaths = 0;

    const auto visit = [&](int i, int j) {
        int numMarked = 0;

        // trick for defining a recursive lambda
        const auto visitImpl = [&](int i, int j, const auto& recur) {
            if (grid[i][j] == EXIT) {
                if (numMarked == floorSpace) {
                    ++numPaths;
                }
                return;
            }

            ++numMarked;
            mark(i, j);
            
            if (viable(i + 1, j)) {
                recur(i + 1, j, recur);
            }
            if (viable(i, j + 1)) {
                recur(i, j + 1, recur);
            }
            if (viable(i - 1, j)) {
                recur(i - 1, j, recur);
            }
            if (viable(i, j - 1)) {
                recur(i, j - 1, recur);
            }

            unmark(i, j);
            --numMarked;
        };

        return visitImpl(i, j, visitImpl);
    };

    visit(iStart, jStart);

    return numPaths;
}
