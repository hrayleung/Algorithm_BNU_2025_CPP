#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
vector<vector<int>> distMat;
int bestAns;

// 计算节点集 S 上的 MST 权重，S 通过 inS[i]==true 标记
int mstLowerBound(const vector<bool> &inS) {
  // Prim 算法
  vector<int> minCost(n, INF);
  vector<bool> used(n, false);
  // 找一个起点：取第一个 inS 为 true 的节点
  int start = -1;
  for (int i = 0; i < n; i++) {
    if (inS[i]) {
      start = i;
      break;
    }
  }
  if (start < 0) {
    return 0; // 空集或错误
  }
  minCost[start] = 0;
  int total = 0, cnt = 0;
  for (int iter = 0; iter < n; iter++) {
    int u = -1, best = INF;
    // 在 S \ used 中选取 minCost 最小的节点
    for (int i = 0; i < n; i++) {
      if (inS[i] && !used[i] && minCost[i] < best) {
        best = minCost[i];
        u = i;
      }
    }
    if (u < 0) {
      break; // 剩余节点不可达
    }
    used[u] = true;
    total += minCost[u];
    cnt++;
    // 更新它的邻边
    for (int v = 0; v < n; v++) {
      if (inS[v] && !used[v] && distMat[u][v] >= 0) {
        minCost[v] = min(minCost[v], distMat[u][v]);
      }
    }
  }
  // 如果 cnt < |S|，说明不连通，返回一个大值
  int need = 0;
  for (int i = 0; i < n; i++) {
    if (inS[i]) {
      need++;
    }
  }
  return (cnt == need ? total : INF);
}

// DFS + 分支限界
void dfs(int u, int visitedMask, int g) {
  // g: 已走过的距离
  if (g >= bestAns) {
    return; // 已付出 ≥ 最优，剪枝
  }

  if (visitedMask == (1 << n) - 1) {
    // 全部城市访问完，不用返回起点
    bestAns = g;
    return;
  }

  // 构造下界节点集 S = { u } ∪ { i | 未访问 }
  vector<bool> inS(n, false);
  inS[u] = true;
  for (int i = 0; i < n; i++) {
    if (!(visitedMask & (1 << i))) {
      inS[i] = true;
    }
  }
  int mst_val = mstLowerBound(inS);

  // Handle potential overflow and INF values in pruning logic
  if (mst_val == INF) {
    // Path is infeasible or lower bound is infinite, prune immediately
    return;
  }

  // mst_val is finite
  if (bestAns != INF) {
    // bestAns is finite, check if g + mst_val >= bestAns safely
    // Use equivalent condition: g >= bestAns - mst_val to avoid overflow
    if (g >= bestAns - mst_val) {
      return; // 即使最乐观也 >= bestAns，剪枝
    }
  }
  // If bestAns == INF, no pruning needed as g + mst_val < INF

  // 枚举下一步要去的城市 v
  for (int v = 0; v < n; v++) {
    if (!(visitedMask & (1 << v)) && distMat[u][v] >= 0) {
      dfs(v, visitedMask | (1 << v), g + distMat[u][v]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  distMat.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> distMat[i][j];
    }
  }

  bestAns = INF;
  // 从城市 0（即题目中城市 1）出发，标记已访问城市 0，累计距离 0
  dfs(0, 1 << 0, 0);

  cout << bestAns << endl;
  return 0;
}