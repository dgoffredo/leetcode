#include <cassert>
#include <queue>
#include <unordered_set>

struct Entry {
  int x;
  int ops;
};

void append_entries(int x, int ops, std::queue<Entry>& queue, const std::unordered_set<int>& seen) {
  const auto already_seen = [&](int n) {
    return seen.find(n) != seen.end();
  };

  if (x % 5 == 0 && !already_seen(x / 5)) {
    queue.push(Entry{x / 5, ops + 1});
  }
  if (x % 11 == 0 && !already_seen(x / 11)) {
    queue.push(Entry{x / 11, ops + 1});
  }
  if (!already_seen(x - 1)) {
    queue.push(Entry{x - 1, ops + 1});
  }
  if (!already_seen(x + 1)) {
    queue.push(Entry{x + 1, ops + 1});
  }
}

int min_ops(int x, int y) {
  std::queue<Entry> queue;
  queue.push(Entry{x, 0});
  std::unordered_set<int> seen;
  for (;;) {
    assert(!queue.empty());
    const auto [x, ops] = queue.front();
    queue.pop();
    if (x == y) {
      return ops;
    }
    seen.insert(x);
    append_entries(x, ops, queue, seen);
  }
}

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
      return min_ops(x, y);
    }
};
