#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

int differences(const std::string& left, const std::string& right) {
  assert(left.size() == 8);
  assert(right.size() == left.size());
  int count = 0;
  for (int i = 0; i < 8; ++i) {
    if (left[i] != right[i]) {
      ++count;
    }
  }
  return count;
}

int length_of_shortest_path(
    const std::string& begin,
    const std::string& end,
    std::vector<std::string>& bank) {
  std::unordered_map<std::string, std::vector<std::string>> adjacents;
  bank.push_back(begin);
  std::sort(bank.begin(), bank.end());
  bank.erase(std::unique(bank.begin(), bank.end()), bank.end());
  for (const std::string& gene : bank) {
    for (const std::string& other : bank) {
      if (differences(gene, other) == 1) {
        adjacents[gene].push_back(other);
        adjacents[other].push_back(gene);
      }
    }
  }

  if (const auto found = adjacents.find(end); found == adjacents.end()) {
    // The end isn't in the bank.
    return -1;
  }

  using Vertex = decltype(adjacents.begin());

  struct Entry {
    Vertex vertex;
    int distance;
  };
  std::queue<Entry> queue;
  queue.push(Entry{.vertex = adjacents.find(begin), .distance = 0});
  do {
    const Entry entry = queue.front();
    queue.pop();

    if (entry.vertex->first == end) {
      return entry.distance;
    }

    for (const std::string& neighbor : entry.vertex->second) {
      queue.push(Entry{.vertex = adjacents.find(neighbor), .distance = entry.distance + 1});
    }
    // Mark the vertex as visited by removing its outward edges.
    entry.vertex->second.clear();
  } while (!queue.empty());

  return -1;
}

class Solution {
public:
    int minMutation(std::string startGene, std::string endGene, std::vector<std::string>& bank) {
      return length_of_shortest_path(startGene, endGene, bank);
    }
};
