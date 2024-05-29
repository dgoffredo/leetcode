#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <vector>

// Each "command" (the problem statement says "query") is a `vector<int>` of
// length 3:
//
//     [type, index, value]
//
// `type` is 0 or 1. 0 means "row", and 1 means "column".
// `index` is the zero-based index of the row or column.
// `value` is the value to which cells in the row or column are to be set.
long long matrix_sum_queries(int n,
                             const std::vector<std::vector<int>> &commands) {
  std::vector<int> row_cmd_order; // command index
  std::vector<int> col_cmd_order; // command index

  {
    // `row_cmds` and `col_cmds` are used to keep track of the _last_ (final)
    // command for each mentioned row/column index.  They are used to construct
    // `row_cmd_order` and `col_cmd_order`, and then discarded.
    std::unordered_set<int> row_cmds; // row index
    std::unordered_set<int> col_cmds; // column index
    for (int i = commands.size() - 1; i >= 0; --i) {
      const auto &command = commands[i];
      const int type = command[0];
      const int index = command[1];
      const int value = command[2];
      auto &table = type ? col_cmds : row_cmds;
      auto &list = type ? col_cmd_order : row_cmd_order;
      if (table.find(index) != table.end()) {
        continue; // this row/column was overwritten by a subsequent command.
      }
      table.insert(index);
      list.push_back(i);
    }
  }
  // We traversed `commands` in reverse order, so the `*_order` vectors are in
  // descending order.  When we later do lookups into these vectors, we'll want
  // them in ascending order instead.
  std::reverse(row_cmd_order.begin(), row_cmd_order.end());
  std::reverse(col_cmd_order.begin(), col_cmd_order.end());

  long long sum = 0;

  // Each final row command contributes at most `value * n` to the sum, but
  // later column commands might overwrite some cells in the row.
  for (const int row_cmd_index : row_cmd_order) {
    const int row_value = commands[row_cmd_index][2];
    const int num_overlapping_cols =
        std::distance(std::upper_bound(col_cmd_order.begin(),
                                       col_cmd_order.end(), row_cmd_index),
                      col_cmd_order.end());
    sum += row_value * (n - num_overlapping_cols);
  }

  // Each final column command contributes at most `value * n` to the sum, but
  // later row commands might overwrite some cells in the column.
  for (const int col_cmd_index : col_cmd_order) {
    const int col_value = commands[col_cmd_index][2];
    const int num_overlapping_rows =
        std::distance(std::upper_bound(row_cmd_order.begin(),
                                       row_cmd_order.end(), col_cmd_index),
                      row_cmd_order.end());
    sum += col_value * (n - num_overlapping_rows);
  }

  return sum;
}

class Solution {
public:
  long long matrixSumQueries(int n, std::vector<std::vector<int>> &queries) {
    return matrix_sum_queries(n, queries);
  }
};
