#include <vector>

using Iter = std::vector<int>::const_iterator;

Iter find_h(const Iter begin, const Iter end, const Iter papers_end) {
  if (begin == end) {
    return papers_end;
  }

  const Iter it = begin + (end - begin) / 2;
  const int citations = *it;
  const int papers = papers_end - it;
  const bool is_candidate = papers >= citations;

  if (is_candidate) {
    // Move right to try for more citations.
    const auto right = find_h(it + 1, end, papers_end);
    if (right == papers_end) {
      return it;  // overshot: use our candidate value
    }
    return right;  
  }

  // Move left to allow for more papers.
  return find_h(begin, it, papers_end);
}

Iter find_h(const Iter begin, const Iter end) {
  return find_h(begin, end, end);
}

class Solution {
public:
    int hIndex(const std::vector<int>& citations) {
       return *find_h(citations.begin(), citations.end()); 
    }
};
