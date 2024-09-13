#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

int num_steps_to_connect(int num_vertices, std::vector<std::vector<int>>& edges) {
  std::vector<int> vertex2component(num_vertices, -1);
  struct Component {
    int num_vertices;
    int num_edges;
  };
  std::vector<Component> components;

  // Sort by the (min, max) vertex mentioned in either edge, lexicographically.
  // This way we never have to merge components.
  std::sort(edges.begin(), edges.end(), [](const std::vector<int>& left, const std::vector<int>& right) {
    const int left_sorted[] = {std::min(left[0], left[1]), std::max(left[0], left[1])};
    const int right_sorted[] = {std::min(right[0], right[1]), std::max(right[0], right[1])};
    return std::lexicographical_compare(std::begin(left_sorted), std::end(left_sorted), std::begin(right_sorted), std::end(right_sorted));
  });

  for (const std::vector<int>& edge : edges) {
    const int from = edge[0];
    const int to = edge[1];
    if (vertex2component[from] == -1 && vertex2component[to] == -1) {
      components.push_back(Component{.num_vertices = 2, .num_edges = 1});
      vertex2component[from] = vertex2component[to] = components.size() - 1;
    } else if (vertex2component[from] == -1 || vertex2component[to] == -1) {
      const int component = vertex2component[from] = vertex2component[to] = std::max(vertex2component[from], vertex2component[to]);
      components[component].num_edges += 1;
      components[component].num_vertices += 1;
    } else {
      // We wouldn't have different components, because due to the edge sorting
      // we would have seen the connecting edge before any edges to
      // yet unencountered nodes.
      assert(vertex2component[from] == vertex2component[to]);
      components[vertex2component[from]].num_edges += 1;
    }
  }

  for (int &component : vertex2component) {
    if (component != -1) {
      continue;
    }
    // Isolated vertex. It's in its own component.
    components.push_back(Component{.num_vertices = 1, .num_edges = 0});
    component = components.size() - 1;
  }

  // Make a max-heap of components on `num_edges - num_vertices`. If `num_edges
  // - num_vertices` is greater than -1, then we can combine the component with
  // the next.  If the difference is less than or equal to -1, then there's no
  // edge we can use to connect the component to another without breaking up
  // the component, so we return that a solution is impossible (`return -1`).

  // We could use `std::make_heap` on `components` to save memory, but the
  // interface of `std::priority_queue` is nicer, so I'll copy all of the data
  // instead.
  struct ByEdgeVertexDifference {
    bool operator()(const Component& left, const Component& right) const {
      return (left.num_edges - left.num_vertices) < (right.num_edges - right.num_vertices);
    }
  };
  std::priority_queue<Component, std::vector<Component>, ByEdgeVertexDifference> heap;
  for (const Component& component : components) {
    heap.push(component);
  }

  int num_moves = 0;
  for (; heap.size() > 1; ++num_moves) {
    const Component donor = heap.top();
    heap.pop();
    const Component receiver = heap.top();
    heap.pop();
    if (donor.num_edges - donor.num_vertices <= -1) {
      // Not enough edges to donate.
      return -1;
    }

    heap.push(Component{
      .num_vertices = donor.num_vertices + receiver.num_vertices,
      .num_edges = donor.num_edges + receiver.num_edges
    });
  }

  return num_moves;
}

class Solution {
public:
    int makeConnected(int n, std::vector<std::vector<int>>& connections) {
      return num_steps_to_connect(n, connections);
    }
};
