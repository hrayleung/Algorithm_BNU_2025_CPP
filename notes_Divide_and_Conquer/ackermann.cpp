#include <ios>
#include <iostream>
using namespace std;

int ackermann(int m, int n);
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int m, n;
  cin >> m >> n;
  cout << ackermann(m, n);
}

int ackermann(int m, int n) {
  if (m == 0) {
    return n + 1;
  } else if (m > 0 && n == 0) {
    return ackermann(m - 1, 1);
  } else {
    return ackermann(m - 1, ackermann(m, n - 1));
  }
}
