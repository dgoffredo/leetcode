#include <limits>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

void update_upward(Matrix& upward, const Matrix& matrix) {
  const int M = matrix.size();
  const int N = matrix[0].size();
  for (int row = 0; row < M; ++row) {
    for (int col = 0; col < N; ++col) {
      if (matrix[row][col] == 0) {
        upward[row][col] = 0;
        continue;
      }
      int value = std::numeric_limits<int>::max();
      // above
      if (row > 0) {
        value = std::min(value, upward[row - 1][col]);
      }
      // left
      if (col > 0) {
        value = std::min(value, upward[row][col - 1]);
      }

      if (value == std::numeric_limits<int>::max()) {
        upward[row][col] = value;
      } else {
        upward[row][col] = value + 1;
      }
    }
  }
}

void update_downward(Matrix& downward, const Matrix& matrix) {
  const int M = matrix.size();
  const int N = matrix[0].size();
  for (int row = M - 1; row >= 0; --row) {
    for (int col = N - 1; col >= 0; --col) {
      if (matrix[row][col] == 0) {
        downward[row][col] = 0;
        continue;
      }
      int value = std::numeric_limits<int>::max();
      // below
      if (row < M - 1) {
        value = std::min(value, downward[row + 1][col]);
      }
      // right
      if (col < N - 1) {
        value = std::min(value, downward[row][col + 1]);
      }

      if (value == std::numeric_limits<int>::max()) {
        downward[row][col] = value;
      } else {
        downward[row][col] = value + 1;
      }
    }
  }
}

void update_matrix(const Matrix& upward, const Matrix& downward, Matrix& matrix) {
  // If an entry in `matrix` is zero, then the result is zero.
  //
  // Otherwise, each entry in `matrix` is one plus the minimum upward and
  // downward distances among its neighbors.
  const int M = matrix.size();
  const int N = matrix[0].size();
  for (int row = 0; row < M; ++row) {
    for (int col = 0; col < N; ++col) {
      if (matrix[row][col] == 0) {
        continue;
      }
      int value = std::numeric_limits<int>::max();
      // above
      if (row > 0) {
        value = std::min(value, upward[row - 1][col]);
        value = std::min(value, downward[row - 1][col]);
      }
      // left
      if (col > 0) {
        value = std::min(value, upward[row][col - 1]);
        value = std::min(value, downward[row][col - 1]);
      }
      // below
      if (row < M - 1) {
        value = std::min(value, upward[row + 1][col]);
        value = std::min(value, downward[row + 1][col]);
      }
      // right
      if (col < N - 1) {
        value = std::min(value, upward[row][col + 1]);
        value = std::min(value, downward[row][col + 1]);
      }

      matrix[row][col] = value + 1;
    }
  }
}

class Solution {
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& m) {
      std::vector<std::vector<int>> upward(m.size(), std::vector<int>(m[0].size()));
      update_upward(upward, m);
      std::vector<std::vector<int>> downward(m.size(), std::vector<int>(m[0].size()));
      update_downward(downward, m);

      update_matrix(upward, downward, m);
      return m;
    }
};
