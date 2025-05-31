#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool isPrim(int x) {
  if (x < 2) {
    return false;
  }
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}
void backtrack(int n, int k, int start, vector<int> &path,
               vector<vector<int>> &res) {
  if (path.size() == k) {
    res.push_back(path);
    return;
  }
  for (int i = start; i <= n - (k - path.size()); i++) {
    path.push_back(i);
    backtrack(n, k, i + 1, path, res);
    path.pop_back();
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> num(n);
  int k;
  cin >> k;
  for (int i = 0; i < n; i++) {
    cin >> num[i];
  }

  vector<int> path;
  vector<vector<int>> res;
  int count = 0;
  backtrack(n, k, 0, path, res);
  for (int i = 0; i < res.size(); i++) {
    int sum = 0;
    for (int j = 0; j < k; j++) {
      sum += num[res[i][j]];
    }
    if (isPrim(sum)) {
      count++;
    }
  }
  cout << count << endl;
}