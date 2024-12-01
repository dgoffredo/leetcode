#include <initializer_list>
#include <vector>

int num_land_cells_garbage_collected(std::vector<std::vector<int>>& grid) {
  const int rows = grid.size();
  const int columns = grid.empty() ? 0 : grid[0].size();
  const auto is_land = [&](int r, int c) -> bool {
    return grid[r][c] & 1;
  };
  const auto is_marked = [&](int r, int c) -> bool {
    return grid[r][c] & 2;
  };
  const auto mark = [&](int r, int c) {
    grid[r][c] &= 2;
  };

  // Use a stack, because vectors are simple.
  std::vector<std::pair<int, int>> land;
  // Add any land in the top row, the bottom row, the first column, and the last column.
  // Top row and bottom row.
  for (int row : {0, rows - 1}) {
    for (int c = 0; c < columns; ++c) {
      if (!is_land(row, c) || is_marked(row, c)) {
        continue;
      }
      mark(row, c);
      land.emplace_back(row, c);
    }
  }
  // First and last column.
  for (int column : {0, columns - 1}) {
    for (int r = 0; r < rows; ++r) {
      if (!is_land(r, column) || is_marked(r, column)) {
        continue;
      }
      mark(r, column);
      land.emplace_back(r, column);
    }
  }

  // Mark all land accessible from `land`.
  while (!land.empty()) {
    const auto [r, c] = land.back();
    land.pop_back();
    // Check the four neighbors. For each, if it's land and hasn't been marked,
    // mark it and add it to the stack (`land`).
    // above
    if (r > 0 && is_land(r - 1, c) && !is_marked(r - 1, c)) {
      mark(r - 1, c);
      land.emplace_back(r - 1, c);
    }
    // below
    if (r < rows - 1 && is_land(r + 1, c) && !is_marked(r + 1, c)) {
      mark(r + 1, c);
      land.emplace_back(r + 1, c);
    }
    // left
    if (c > 0 && is_land(r, c - 1) && !is_marked(r, c - 1)) {
      mark(r, c - 1);
      land.emplace_back(r, c - 1);
    }
    // right
    if (c < columns - 1 && is_land(r, c + 1) && !is_marked(r, c + 1)) {
      mark(r, c + 1);
      land.emplace_back(r, c + 1);
    }
  }

  // Count the unmarked land.
  int enclaves = 0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < columns; ++c) {
      if (is_land(r, c) && !is_marked(r, c)) {
        ++enclaves;
      }
    }
  }

  return enclaves;
}

class Solution {
public:
    int numEnclaves(std::vector<std::vector<int>>& grid) {
       return num_land_cells_garbage_collected(grid);
    }
};
