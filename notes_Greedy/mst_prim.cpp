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

struct