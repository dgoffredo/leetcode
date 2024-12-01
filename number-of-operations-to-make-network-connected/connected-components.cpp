#include <algorithm>
#include <cassert>
#include <vector>

int num_steps_to_connect(int num_vertices, const std::vector<std::vector<int>>& edges) {
  struct Component {
    int num_edges;
    int num_vertices;

    bool is_alias() const {
      return num_vertices == 0;
    }

    int alias() const {
      assert(is_alias());
      return num_edges;
    }

    void set_alias(int other) {
      num_vertices = 0;
      num_edges = other;
    }
  };

  std::vector<int> vertex2component;
  std::vector<Component> components;
  for (int i = 0; i < num_vertices; ++i) {
    components.push_back(Component{.num_edges = 0, .num_vertices = 1});
    vertex2component.push_back(components.size() - 1);
  }

  for (const std::vector<int>& edge : edges) {
    assert(edge.size() == 2);
    const int left = edge[0], right = edge[1];

    int left_component = vertex2component[left], right_component = vertex2component[right];
    // Resolve both components to their most recent value.
    while (components[left_component].is_alias()) {
      left_component = components[left_component].alias();
    }
    while (components[right_component].is_alias()) {
      right_component = components[right_component].alias();
    }
    if (left_component == right_component) {
      components[left_component].num_edges += 1;
    } else {
      // They're different. Merge the later into the earlier.
      const int to_keep = std::min(left_component, right_component);
      const int to_merge = std::max(left_component, right_component);
      components[to_keep].num_edges += components[to_merge].num_edges + 1;
      components[to_keep].num_vertices += components[to_merge].num_vertices;
      // Mark the component as an alias for the other.
      components[to_merge].set_alias(to_keep);
    }
  }

  // Loop through `components`, counting the number of components and the
  // number of extra edges that could be used to connect the components.
  int num_components = 0;
  int num_extra_edges = 0;
  for (const Component& component : components) {
    if (component.is_alias()) {
      continue;
    }
    ++num_components;
    num_extra_edges += component.num_edges - (component.num_vertices - 1);
  }

  if (num_extra_edges < num_components - 1) {
    return -1;
  }

  return num_components - 1;
}

class Solution {
public:
    int makeConnected(int n, std::vector<std::vector<int>>& connections) {
      return num_steps_to_connect(n, connections);
    }
};
