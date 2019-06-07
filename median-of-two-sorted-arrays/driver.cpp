#include "solution.cpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    using namespace std;

    istringstream line;
    string        buffer;
    int           number;
    vector<int>   left;
    vector<int>   right;

    getline(cin, buffer);
    line.str(buffer);
    while (line >> number)
        left.push_back(number);

    line.clear();

    getline(cin, buffer);
    line.str(buffer);
    while (line >> number)
        right.push_back(number);

    assert(is_sorted(left.begin(), left.end()));
    assert(is_sorted(right.begin(), right.end()));

    cout << Solution().findMedianSortedArrays(left, right) << '\n';
}