#include <limits>
#include <vector>

int visit(int i, int j, std::vector<std::vector<int>>& m) {
  // Use negative numbers for distance, except for zero.
  
  if (m[i][j] <= 0) {
    // already been visited
    return m[i][j];
  }

  int max_neighbor = std::numeric_limits<int>::min();

  // above
  if (i > 0) {
    max_neighbor = std::max(max_neighbor, visit(i - 1, j, m));
  }
  // below
  if (i < int(m.size() - 1)) {
    max_neighbor = std::max(max_neighbor, visit(i + 1, j, m));
  }
  // leftward
  if (j > 0) {
    max_neighbor = std::max(max_neighbor,  visit(i, j - 1, m));
  }
  // rightward
  if (j < int(m[i].size() - 1)) {
    max_neighbor = std::max(max_neighbor, visit(i, j + 1, m));
  }

  // TODO: uh oh, the idea is wrong
  return m[i][j] = max_neighbor - 1;
}

void update_matrix(std::vector<std::vector<int>>& m) {
  visit(0, 0, m);

  // Negate the minus signs.
  for (int i = 0; i < int(m.size()); ++i) {
    for (int j = 0; j < int(m[0].size()); ++i) {
      m[i][j] *= -1;
    }
  }
}

class Solution {
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
       update_matrix(mat);
       return mat;
    }
};