#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct edge {
  int from;
  int to;
  int weight;
  edge(int f, int t, int w) : from(f), to(t), weight(w) {}

  bool operator<(const edge &other) const { return weight < other.weight; }
};

class UnionFind {
private:
  vector<int> parent, rank;

public:
  UnionFind(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return false;
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
    return true;
  }
};

class KruskalMst {
private:
  vector<edge> edges;
  vector<edge> mst_edges;
  int num_vertices;
  int total_weight;

public:
  KruskalMst(int n) : num_vertices(n), total_weight(0) {}
  void addEdge(int from, int to, int weight) {
    edges.push_back(edge(from, to, weight));
  }

  void kruskal() {
    sort(edges.begin(), edges.end());
    UnionFind uf(num_vertices);

    for (const edge &e : edges) {
      if (uf.unite(e.from, e.to)) {
        mst_edges.push_back(e);
        total_weight += e.weight;
        if (mst_edges.size() == num_vertices - 1) {
          break;
        }
      }
    }
  }

  void printMST() {
    cout << "Minimum Spanning Tree constructed by Kruskal's algorithm:" << endl;
    for (const edge &e : mst_edges) {
      cout << "Edge " << e.from << " -> " << e.to << ", weight: " << e.weight
           << endl;
    }
    cout << "Total weight of MST: " << total_weight << endl;
  }

  int getTotalWeight() const { return total_weight; }
};

int main() {
  // Using the same example graph
  int num_vertices = 6;
  KruskalMst mst(num_vertices);

  // Add edges
  mst.addEdge(0, 1, 4);
  mst.addEdge(0, 2, 3);
  mst.addEdge(1, 2, 1);
  mst.addEdge(1, 3, 2);
  mst.addEdge(2, 3, 4);
  mst.addEdge(2, 4, 2);
  mst.addEdge(3, 4, 3);
  mst.addEdge(3, 5, 6);
  mst.addEdge(4, 5, 1);

  mst.kruskal();
  mst.printMST();

  return 0;
}