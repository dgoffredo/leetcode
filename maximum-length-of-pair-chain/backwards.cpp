#include <algorithm>
#include <vector>

int length_of_longest_chain(const std::vector<std::vector<int>>& pairs) {
  if (pairs.size() == 1) {
    return 1;
  }

  struct Segment {
    int begin;
    int end;
    int max_length_at_or_after;
  };

  std::vector<Segment> segments;
  segments.reserve(pairs.size());
  for (const auto& pair : pairs) {
    segments.push_back(Segment{.begin = pair[0], .end = pair[1], .max_length_at_or_after = 0});
  }

  struct ByBegin {
    bool operator()(const Segment& left, const Segment& right) const {
      return left.begin < right.begin;
    }
  };

  std::sort(segments.begin(), segments.end(), ByBegin{});

  const auto begin_is = [](int end) {
    // Dummy value for finding the next segment in a chain.
    return Segment{.begin = end, .end = 0, .max_length_at_or_after = 0};
  };

  segments.back().max_length_at_or_after = 1;

  for (int i = segments.size() - 2; i >= 0; --i) {
    int max = 1;
    Segment& current = segments[i];
    // See if there's another link in the chain starting at `current`.
    const auto next = std::upper_bound(segments.begin() + i + 1, segments.end(), begin_is(current.end), ByBegin{});
    if (next != segments.end()) {
      max = next->max_length_at_or_after + 1;
    }
    // If the link ends at `current`, then whoever was looking at us could have
    // gone to the next link instead, so consider that length as well.
    max = std::max(max, segments[i + 1].max_length_at_or_after);
    current.max_length_at_or_after = max;
  }

  return segments[0].max_length_at_or_after;
}

class Solution {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
       return length_of_longest_chain(pairs);
    }
};
