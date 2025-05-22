#include <iostream>
#include <limits>
#include <vector>
using namespace std;

struct edge {
  int from;
  int to;
  int weight;

  edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

bool bellmanford(const vector<edge> &edges, int start_node, int num_vertices,
                 vector<int> &distances) {
  distances.assign(num_vertices, numeric_limits<int>::max());
  distances[start_node] = 0;

  for (int i = 0; i < num_vertices - 1; i++) {
    bool relaxed_in_this_iteration = false;
    for (const edge &e : edges) {
      int u = e.from;
      int v = e.to;
      int weight = e.weight;

      if (distances[u] != numeric_limits<int>::max()) {
        if (distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
          relaxed_in_this_iteration = true;
        }
      }
    }

    if (!relaxed_in_this_iteration) {
      break;
    }
  }

  for (const edge &e : edges) {
    int u = e.from;
    int v = e.to;
    int weight = e.weight;

    if (distances[u] != numeric_limits<int>::max()) {
      if (distances[u] + weight < distances[v]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int num_vertices = 5;

  // Example 1: No negative weight cycle
  vector<edge> edges1;
  edges1.push_back(edge(0, 1, 6));
  edges1.push_back(edge(0, 2, 7));
  edges1.push_back(edge(1, 2, 5));
  edges1.push_back(edge(1, 3, -4));
  edges1.push_back(edge(2, 3, -3));
  edges1.push_back(edge(2, 4, 9));
  edges1.push_back(edge(3, 4, 2));

  int start_node1 = 0;
  vector<int> distances1;
  cout << "Example 1: No negative weight cycle" << endl;
  if (bellmanford(edges1, start_node1, num_vertices, distances1)) {
    cout << "Shortest distances from source " << start_node1
         << " to other vertices:" << endl;
    for (int i = 0; i < num_vertices; ++i) {
      if (distances1[i] == numeric_limits<int>::max()) {
        cout << "To vertex " << i << ": Unreachable" << endl;
      } else {
        cout << "To vertex " << i << ": " << distances1[i] << endl;
      }
    }
  } else {
    cout << "Graph contains a negative weight cycle!" << endl;
  }
  cout << endl;

  // Example 2: With negative weight cycle
  vector<edge> edges2;
  edges2.push_back(edge(0, 1, 1));
  edges2.push_back(edge(1, 2, -2));
  edges2.push_back(edge(2, 0, 1)); // Negative weight cycle
  edges2.push_back(edge(2, 3, 3));

  int start_node2 = 0;
  vector<int> distances2;

  cout << "Example 2: With negative weight cycle" << endl;
  if (bellmanford(edges2, start_node2, num_vertices, distances2)) {
    cout << "Shortest distances from source " << start_node2
         << " to other vertices:" << endl;
    for (int i = 0; i < num_vertices; ++i) {
      if (distances2[i] == numeric_limits<int>::max()) {
        cout << "To vertex " << i << ": Unreachable" << endl;
      } else {
        cout << "To vertex " << i << ": " << distances2[i] << endl;
      }
    }
  } else {
    cout << "Graph contains a negative weight cycle!" << endl;
  }

  return 0;
}