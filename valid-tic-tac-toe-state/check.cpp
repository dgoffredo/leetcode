#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int x_count;
        int o_count;
        for (const string& row : board) {
          for (char square : row) {
            switch (square) {
            case 'X': ++x_count; break;
            case 'O': ++o_count; break;
            }
          }
        }
        const int diff = x_count - o_count;
        if (diff < 0 || diff > 1) {
          return false;
        }

        const bool x_win = win(board, 'X');
        const bool o_win = win(board, 'O');
        
        if (x_win && (diff != 1 || o_win)) {
          return false;
        }

        if (o_win && (diff != 0 || x_win)) {
          return false;
        }

        return true;
    }

    bool win(const vector<string>& board, char player) {
      const auto p = [&](int r, int c) { return board[r][c] == player; };
      return
            // rows
               (p(0, 0) && p(0, 1) && p(0, 2))
            || (p(1, 0) && p(1, 1) && p(1, 2))
            || (p(2, 0) && p(2, 1) && p(2, 2))
            // columns
            || (p(0, 0) && p(1, 0) && p(2, 0))
            || (p(0, 1) && p(1, 1) && p(2, 1))
            || (p(0, 2) && p(1, 2) && p(2, 2))
            // backslash diagonal
            || (p(0, 0) && p(1, 1) && p(2, 2))
            // forward slash diagonal
            || (p(2, 0) && p(1, 1) && p(0, 2));
    }
};
