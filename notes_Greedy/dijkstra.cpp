#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

struct edge {
  int to;
  int weight;
  edge(int t, int w) : to(t), weight(w) {}
};

struct state {
  int distance;
  int vertex;
  state(int d, int v) : distance(d), vertex(v) {}
  bool operator>(const state &other) const { return distance > other.distance; }
};

vector<int> dijkstra(const vector<vector<edge>> &graph, int start_node,
                     int num_vertices) {
  vector<int> distances(num_vertices, numeric_limits<int>::max());
  priority_queue<state, vector<state>, greater<state>> pq;
  distances[start_node] = 0;
  pq.push(state(0, start_node));

  while (!pq.empty()) {
    state current = pq.top();
    pq.pop();

    int u = current.vertex;
    int d_u = current.distance;

    if (d_u > distances[u]) {
      continue;
    }

    for (const edge &e : graph[u]) {
      int v = e.to;
      int weight = e.weight;

      if (distances[u] + weight < distances[v]) {
        distances[v] = distances[u] + weight;
        pq.push(state(distances[v], v));
      }
    }
  }
  return distances;
}

int main() {
  int num_vertices = 5;
  vector<vector<edge>> graph(num_vertices);

  graph[0].push_back(edge(1, 10));
  graph[0].push_back(edge(2, 3));
  graph[1].push_back(edge(2, 2));
  graph[1].push_back(edge(3, 5));
  graph[2].push_back(edge(1, 4));
  graph[2].push_back(edge(3, 8));
  graph[2].push_back(edge(4, 2));
  graph[3].push_back(edge(4, 6));

  int start_node = 0;

  vector<int> shortest_distance = dijkstra(graph, start_node, num_vertices);

  cout << "start from " << start_node << " shortest path to " << endl;
  for (int i = 0; i < num_vertices; i++) {
    if (shortest_distance[i] == numeric_limits<int>::max()) {
      cout << "can not reach " << i << endl;
    } else {
      cout << "the shortest distance to " << i << ": " << shortest_distance[i]
           << endl;
    }
  }
  return 0;
}