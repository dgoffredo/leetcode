#include <vector>

using namespace std;

class Solution {
public:
    int maxSideLength(vector<vector<int>>& m, int threshold) {
      const int R = m.size(); // R is the number of rows.
      const int C = m[0].size(); // C is the number of columns.
      // L is the max side length of squares whose sum is <= threshold.
      int L = 0;
      // t[r][c] is the sum of the rectangle whose upper left corner is at
      // row=0 column=0 and whose bottom right corner is at row=r column=c.
      // We can reuse the storage of m because of the way we calculate t.
      vector<vector<int>>& t = m;

      // m_at is a wrapper around m that also might increase L from 0 to 1.
      // This allows us to cover the side-length-one case as we fill out t.
      const auto m_at = [&](int r, int c) {
        const int value = m[r][c];
        if (L == 0 && value <= threshold) {
          L = 1;
        }
        return value;
      };

      // Fill out the first column and row of t.
      for (int r = 0, sum = 0; r < R; ++r) {
        sum += m_at(r, 0);
        t[r][0] = sum;
      }
      for (int c = 0, sum = 0; c < C; ++c) {
        sum += m_at(0, c);
        t[0][c] = sum;
      }
      // Fill out the rest of t.
      for (int r = 1; r < R; ++r) {
        for (int c = 1; c < C; ++c) {
          t[r][c] = t[r-1][c] + t[r][c-1] + m_at(r, c) - t[r-1][c-1];
        }
      }

      if (L == 0) {
        // Every element of m is greater than threshold.
        return L;
      }

      // t_at is a wrapper around t that returns zero for negative coordinates.
      // This allows us to hide some branches when calculating rectangle sums.
      const auto t_at = [&](int r, int c) {
        if (r < 0 || c < 0) {
          return 0;
        }
        return t[r][c];
      };

      // square is the sum of a square whose top left corner is at row=r
      // column=c and whose side length is L.
      const auto square = [&](int r, int c, int L) {
        const int x = L - 1;
        return t_at(r+x, c+x) - t_at(r+x, c-1) - t_at(r-1, c+x) + t_at(r-1, c-1);
      };

      // See how big L can get. Move the top left corner of the square along
      // the grid, trying to increase the side length when possible.
      for (int r = 0; r + L - 1 < R; ++r) {
        for (int c = 0; c + L - 1 < C; ++c) {
          // TODO: Could be a binary search over possible increasing L, instead
          // of this incrementing loop.
          while (square(r, c, L) <= threshold && r+L < R && c+L < C && square(r, c, L+1) <= threshold) {
            ++L;
          }
        }
      }
      return L;
    }
};
