#include <memory>
#include <vector>

int num_steps_to_connect(int num_vertices, std::vector<std::vector<int>>& edges) {
  struct Component {
    int num_vertices;
    int num_edges;
    Component *parent;
  };
  std::vector<std::unique_ptr<Component>> components;
  std::vector<Component*> vertex2component(num_vertices);

  for (const std::vector<int>& edge : edges) {
    const int from = edge[0];
    const int to = edge[1];
    if (!vertex2component[from] && !vertex2component[to]) {
      components.emplace_back(new Component{.num_vertices = 2, .num_edges = 1, .parent = nullptr});
      vertex2component[from] = vertex2component[to] = components.back().get();
    } else if (!vertex2component[from] || !vertex2component[to]) {
      Component *component = vertex2component[from] = vertex2component[to] = std::max(vertex2component[from], vertex2component[to]);
      component->num_edges += 1;
      component->num_vertices += 1;
    } else {
      Component *from_root = vertex2component[from];
      while (from_root->parent) {
        from_root = from_root->parent;
      }
      Component *to_root = vertex2component[to];
      while (to_root->parent) {
        to_root = to_root->parent;
      }

      if (from_root == to_root) {
        from_root->num_edges += 1;
      } else {
        // Combine them.
        components.emplace_back(new Component{
          .num_vertices = from_root->num_vertices + to_root->num_vertices,
          .num_edges = from_root->num_edges + to_root->num_edges + 1,
          .parent = nullptr
        });
        vertex2component[from] = vertex2component[to] = from_root->parent = to_root->parent = components.back().get();
      }
    }
  }

  // If I have read the problem correctly, then there is exactly one
  // connected component in `components`.
  //
  // This means that we can take any component from `components`, find its
  // root, and then take that to be the one component.
  //
  // Then consider the `n - num_vertices` extra vertices. We need one edge per
  // one of those to totally connect the graph. The connected component needs
  // at least `num_vertices - 1` edges to remain connected, so the answer is:
  //
  // - `-1` ("impossible") if `num_edges - (n - num_vertices) < num_vertices - 1`
  // - `n - num_vertices` (the number of edges to move, one for each extra vertex) otherwise
  //
  // Here's a simplification of the "impossible" condition:
  //
  // `num_edges - (n - num_vertices) < num_vertices - 1`
  // `num_edges - n + num_vertices < num_vertices - 1`
  // `num_edges - n < -1`
  // `num_edges < n + 1`.
  if (components.empty()) {
    return -1;
  }
  Component *root = components[0].get();
  while (root->parent) {
    root = root->parent;
  }
  if (root->num_edges < num_vertices + 1) {
    return -1;
  }
  return num_vertices - root->num_vertices;
}

class Solution {
public:
    int makeConnected(int n, std::vector<std::vector<int>>& connections) {
      return num_steps_to_connect(n, connections);
    }
};
