#include <ios>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> perm(vector<int> seq) {
  int n = seq.size();
  vector<vector<int>> res;

  if (n == 1) {
    res.push_back(seq);
    return res;
  } else {
    for (int i = 0; i < n; i++) {
      int val = seq[i];
      vector<int> tmp = seq;
      tmp.erase(tmp.begin() + i);
      vector<vector<int>> perms = perm(tmp);

      for (auto &p : perms) {
        p.insert(p.begin(), val);
        res.push_back(p);
      }
    }
    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> seq(n);
  for (int i = 0; i < n; i++) {
    cin >> seq[i];
  }
  vector<vector<int>> res = perm(seq);
  for (int i = 0; i < res.size(); i++) {
    for (int j = 0; j < res[i].size(); j++) {
      cout << res[i][j] << " ";
    }
    cout << endl;
  }
}