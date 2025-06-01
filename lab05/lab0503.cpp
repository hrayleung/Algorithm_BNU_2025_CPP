#include <iostream>
#include <vector>
using namespace std;

int n;
int cnt = 0;
void backtrack(int row, vector<bool> &cols, vector<bool> &diag1,
               vector<bool> &diag2, vector<vector<int>> &solutions,
               vector<int> path) {
  if (row == n) {
    cnt++;
    if (solutions.size() < 3) {
      solutions.push_back(path);
    }
    return;
  }
  for (int col = 0; col < n; col++) {
    if (!cols[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
      path.push_back(col + 1);
      cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;
      backtrack(row + 1, cols, diag1, diag2, solutions, path);
      cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
      path.pop_back();
    }
  }
}

int main() {
  cin >> n;
  vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
  vector<vector<int>> solutions;
  vector<int> path;
  backtrack(0, cols, diag1, diag2, solutions, path);
  for (int i = 0; i < solutions.size(); i++) {
    for (int j = 0; j < n; j++) {
      cout << solutions[i][j] << " ";
    }
    cout << endl;
  }
  cout << cnt;
}