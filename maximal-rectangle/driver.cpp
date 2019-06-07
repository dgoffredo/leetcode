#include "quadratic.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    using namespace std;

    vector<vector<char>> matrix;
    string               buffer;
    istringstream        line;
    while (getline(cin, buffer)) {
        line.clear();
        line.str(buffer);
        std::vector<char> row;
        char              cell;
        while (line >> cell) {
            row.push_back(cell);
        }
        matrix.push_back(move(row));
    }

    cout << Solution().maximalRectangle(matrix) << "\n";
}