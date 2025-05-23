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

class BucketQueue {
private:
  vector<queue<int>> buckets;
  int bucket_count;
  int min_bucket;
  int size;

public:
  BucketQueue(int max_weight) {
    bucket_count = max_weight + 1;
    buckets.resize(bucket_count);
    min_bucket = 0;
    size = 0;
  }

  void push(int vertex, int distance) {
    int bucket_idx = distance % bucket_count;
    buckets[bucket_idx].push(vertex);
    size++;
  }
  int pop() {
    while (min_bucket < bucket_count && buckets[min_bucket].empty()) {
      min_bucket++;
    }
    if (min_bucket >= bucket_count) {
      min_bucket = 0;
      while (min_bucket < bucket_count && buckets[min_bucket].empty()) {
        min_bucket++;
      }
    }
    int vertex = buckets[min_bucket].front();
    buckets[min_bucket].pop();
    size--;
    return vertex;
  }
  bool empty() { return size == 0; }
};

vector<int> dijkstra_bucket_queue(const vector<vector<edge>> &graph,
                                  int start_node, int num_vertices,
                                  int max_weight) {
  vector<int> distances(num_vertices, numeric_limits<int>::max());
  vector<bool> visited(num_vertices, false);
  BucketQueue pq(max_weight);
  distances[start_node] = 0;
  pq.push(start_node, 0);

  while (!pq.empty()) {
    int u = pq.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    for (const edge &e : graph[u]) {
      int v = e.to;
      int weight = e.weight;

      if (!visited[v] && distances[u] + weight < distances[v]) {
        distances[v] = distances[u] + weight;
        pq.push(v, distances[v]);
      }
    }
  }
  return distances;
}

int main() {
  int num_vertices = 6;
  int max_edge_weight = 10; // Assume max edge weight is 10

  vector<vector<edge>> graph(num_vertices);

  // Build test graph
  graph[0].push_back(edge(1, 2));
  graph[0].push_back(edge(2, 4));
  graph[1].push_back(edge(2, 1));
  graph[1].push_back(edge(3, 7));
  graph[2].push_back(edge(4, 3));
  graph[3].push_back(edge(4, 2));
  graph[3].push_back(edge(5, 1));
  graph[4].push_back(edge(5, 5));

  int start_node = 0;

  // Use bucket queue optimized Dijkstra
  cout << "=== Bucket Queue Optimized Dijkstra Results ===" << endl;
  vector<int> distances_bucket =
      dijkstra_bucket_queue(graph, start_node, num_vertices, max_edge_weight);

  for (int i = 0; i < num_vertices; i++) {
    if (distances_bucket[i] == numeric_limits<int>::max()) {
      cout << "Vertex " << i << ": Unreachable" << endl;
    } else {
      cout << "Vertex " << i << ": " << distances_bucket[i] << endl;
    }
  }

  return 0;
}