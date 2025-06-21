#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
vector<vector<int>> dist;
int minCost;

// 计算节点集合的最小生成树权重
int calculateMST(const vector<bool> &inSet) {
  vector<int> key(n, INF);
  vector<bool> used(n, false);

  // 找到集合中的起始节点
  int start = -1;
  for (int i = 0; i < n; i++) {
    if (inSet[i]) {
      start = i;
      break;
    }
  }
  if (start == -1) {
    return 0;
  }

  key[start] = 0;
  int totalWeight = 0;
  int nodeCount = 0;

  for (int iter = 0; iter < n; iter++) {
    int u = -1;
    int minKey = INF;

    // 在集合中找到未使用且key值最小的节点
    for (int i = 0; i < n; i++) {
      if (inSet[i] && !used[i] && key[i] < minKey) {
        minKey = key[i];
        u = i;
      }
    }

    if (u == -1) {
      break;
    }

    used[u] = true;
    totalWeight += key[u];
    nodeCount++;

    // 更新相邻节点的key值
    for (int v = 0; v < n; v++) {
      if (inSet[v] && !used[v] && dist[u][v] >= 0) {
        key[v] = min(key[v], dist[u][v]);
      }
    }
  }

  // 检查是否所有节点都连通
  int requiredNodes = 0;
  for (int i = 0; i < n; i++) {
    if (inSet[i]) {
      requiredNodes++;
    }
  }

  return (nodeCount == requiredNodes) ? totalWeight : INF;
}

// 深度优先搜索 + 分支限界
void dfs(int currentCity, int visitedMask, int currentCost) {
  // 剪枝：当前成本已超过最优解
  if (currentCost >= minCost) {
    return;
  }

  // 检查是否访问完所有城市
  if (visitedMask == (1 << n) - 1) {
    minCost = currentCost;
    return;
  }

  // 构造剩余节点集合
  vector<bool> remainingSet(n, false);
  remainingSet[currentCity] = true;
  for (int i = 0; i < n; i++) {
    if (!(visitedMask & (1 << i))) {
      remainingSet[i] = true;
    }
  }

  int mstCost = calculateMST(remainingSet);

  // 处理MST下界的剪枝逻辑
  if (mstCost == INF) {
    return; // 路径不可行
  }

  if (minCost != INF) {
    // 使用安全的比较避免整数溢出
    if (currentCost >= minCost - mstCost) {
      return; // 下界剪枝
    }
  }

  // 尝试访问下一个城市
  for (int nextCity = 0; nextCity < n; nextCity++) {
    if (!(visitedMask & (1 << nextCity)) && dist[currentCity][nextCity] >= 0) {
      dfs(nextCity, visitedMask | (1 << nextCity),
          currentCost + dist[currentCity][nextCity]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  dist.assign(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> dist[i][j];
    }
  }

  minCost = INF;
  // 从城市0开始，标记已访问，初始成本为0
  dfs(0, 1 << 0, 0);

  cout << minCost << endl;
  return 0;
}