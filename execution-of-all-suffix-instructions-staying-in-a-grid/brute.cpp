#include <string>
#include <vector>

int simulate(
    int n,
    int row,
    int col,
    std::string::const_iterator begin,
    std::string::const_iterator end) {
  int count = 0;
  for (auto it = begin; it != end; ++it, ++count) {
    switch (*it) {
    case 'U':
      if (--row == -1) {
        return count;
      }
      break;
    case 'D':
      if (++row == n) {
        return count;
      }
      break;
    case 'L':
      if (--col == -1) {
        return count;
      }
      break;
    case 'R':
      if (++col == n) {
        return count;
      }
      break;
    }
  }
  return count;
}

std::vector<int> num_moves_per_starting_position(
    int n,
    std::vector<int>& starting_position,
    const std::string& moves) {
  const int start_row = starting_position[0];
  const int start_col = starting_position[1];
  std::vector<int>& num_moves = starting_position;
  num_moves.resize(moves.size());
  for (int i = 0; i < int(moves.size()); ++i) {
    num_moves[i] = simulate(n, start_row, start_col, moves.begin() + i, moves.end());
  }
  return std::move(num_moves);
}

class Solution {
public:
    std::vector<int> executeInstructions(int n, std::vector<int>& startPos, std::string s) {
      return num_moves_per_starting_position(n, startPos, s);
    }
};
