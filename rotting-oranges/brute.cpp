#include <vector>

int rotting_time(std::vector<std::vector<int>>& grid) {
  const int EMPTY = 1, FRESH = 1, ROTTEN = 2;
  const int rows = grid.size();
  const int cols = grid[0].size();
  auto previous = grid;
  int cycle = 0;
  int num_fresh;
  for (; ; ++cycle) {
    num_fresh = 0;
    bool changed = false;
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        if (grid[row][col] == FRESH) {
          if ((row > 0 && previous[row-1][col] == ROTTEN) ||
              (col > 0 && previous[row][col-1] == ROTTEN) ||
              (row < rows - 1 && previous[row+1][col] == ROTTEN) ||
              (col < cols - 1 && previous[row][col+1] == ROTTEN)) {
            changed = true;
            grid[row][col] = ROTTEN;
          } else {
            ++num_fresh;
          }
        }
      }
    }

    if (!changed) {
      break;
    }
    previous = grid;
  }

  if (num_fresh) {
    return -1;
  }
  return cycle;
}

class Solution {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid) {
       return rotting_time(grid);
    }
};
