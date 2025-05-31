#include <ios>
#include <iostream>
#include <vector>
using namespace std;

void backtrack(const vector<int> &weight, const vector<int> &value, int i,
               int currentWeight, int currentValue, int capacity, int &maxValue,
               int remainingValue) {
  if (currentValue + remainingValue <= maxValue) {
    return;
  }

  if (i == weight.size()) {
    if (currentValue > maxValue) {
      maxValue = currentValue;
    }
    return;
  }

  backtrack(weight, value, i + 1, currentWeight, currentValue, capacity,
            maxValue, remainingValue - value[i]);

  if (currentWeight + weight[i] <= capacity) {
    backtrack(weight, value, i + 1, currentWeight + weight[i],
              currentValue + value[i], capacity, maxValue,
              remainingValue - value[i]);
  }
}

int knapsack(const vector<int> &weight, const vector<int> &value,
             int capacity) {
  int maxValue = 0;
  int totalValue = 0;
  for (int v : value) {
    totalValue += v;
  }
  backtrack(weight, value, 0, 0, 0, capacity, maxValue, totalValue);
  return maxValue;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  int capacity;
  cin >> capacity;
  vector<int> value(n);
  vector<int> weight(n);
  for (int i = 0; i < n; i++) {
    cin >> weight[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> value[i];
  }
  cout << knapsack(weight, value, capacity) << endl;
}
