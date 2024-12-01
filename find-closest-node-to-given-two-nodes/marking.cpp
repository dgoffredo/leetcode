#include <limits>
#include <vector>

int closest_common(const std::vector<int>& edges, int alice, int bob) {
  struct Distance {
    int from_alice = -1;
    int from_bob = -1;
  };
  std::vector<Distance> distances(edges.size());
  const auto fill = [&](int who, auto member) {
    int node = who;
    int distance = 0;
    for (;;) {
      if (distances[node].*member != -1) {
        break; // cycle
      }
      distances[node].*member = distance;
      node = edges[node];
      if (node == -1) {
        break; // no more successors
      }
      ++distance;
    }
  };

  fill(alice, &Distance::from_alice);
  fill(bob, &Distance::from_bob);

  int candidate = -1;
  int weight = std::numeric_limits<int>::max();
  for (int node = 0; node < distances.size(); ++node) {
    const auto& [from_alice, from_bob] = distances[node];
    if (from_alice != -1 && from_bob != -1 && std::max(from_alice, from_bob) < weight) {
      candidate = node;
      weight = std::max(from_alice, from_bob);
    }
  }

  return candidate;
}

class Solution {
public:
    int closestMeetingNode(std::vector<int>& edges, int node1, int node2) {
       return closest_common(edges, node1, node2);
    }
};
