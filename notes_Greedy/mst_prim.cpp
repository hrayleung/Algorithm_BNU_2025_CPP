#include <functional>
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

struct mst_edge {
  int to;
  int weight;
  int from;
  mst_edge(int t, int w, int f) : to(t), weight(w), from(f) {}
  bool operator>(const mst_edge &other) const { return weight > other.weight; }
};

class PrimMst {
private:
  vector<vector<edge>> graph;
  vector<bool> visited;
  vector<mst_edge> mst_edges;
  int num_vertices;
  int total_weight;

public:
  PrimMst(int n) : num_vertices(n), total_weight(0) {
    graph.resize(n);
    visited.resize(n, false);
  }

  void addEdge(int from, int to, int weight) {
    graph[from].push_back(edge(to, weight));
    graph[to].push_back(edge(from, weight));
  }

  void prim(int start = 0) {
    priority_queue<mst_edge, vector<mst_edge>, greater<mst_edge>> pq;

    visited[start] = true;

    for (const edge &e : graph[start]) {
      pq.push(mst_edge(e.to, e.weight, start));
    }

    while (!pq.empty() && mst_edges.size() < num_vertices - 1) {
      mst_edge current = pq.top();
      pq.pop();

      if (visited[current.to]) {
        continue;
      }

      mst_edges.push_back(current);
      total_weight = total_weight + current.weight;
      visited[current.to] = true;

      for (const edge &e : graph[current.to]) {
        if (!visited[e.to]) {
          pq.push(mst_edge(e.to, e.weight, current.to));
        }
      }
    }
  }

  void printMST() {
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (const mst_edge &e : mst_edges) {
      cout << "Edge " << e.from << " -> " << e.to << ", weight: " << e.weight
           << endl;
    }
    cout << "Total weight of MST: " << total_weight << endl;
  }

  int getTotalWeight() const { return total_weight; }
};

int main() {
  // Create example graph
  int num_vertices = 6;
  PrimMst mst(num_vertices);

  // Add edges (vertex numbers start from 0)
  mst.addEdge(0, 1, 4);
  mst.addEdge(0, 2, 3);
  mst.addEdge(1, 2, 1);
  mst.addEdge(1, 3, 2);
  mst.addEdge(2, 3, 4);
  mst.addEdge(2, 4, 2);
  mst.addEdge(3, 4, 3);
  mst.addEdge(3, 5, 6);
  mst.addEdge(4, 5, 1);

  cout << "Building Minimum Spanning Tree using Prim's Algorithm:" << endl;
  mst.prim(0); // Start from vertex 0
  mst.printMST();

  return 0;
}
