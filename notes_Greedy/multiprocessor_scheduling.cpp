#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<vector<int>> multiprocessorScheduling(vector<int> &tasks, int m) {
  sort(tasks.begin(), tasks.end(), greater<int>());
  priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>,
                 greater<pair<int, vector<int>>>>
      machines;

  for (int i = 0; i < m; i++) {
    machines.push({0, vector<int>()});
  }

  for (int task : tasks) {
    auto [load, assigned_tasks] = machines.top();
    machines.pop();

    assigned_tasks.push_back(task);

    machines.push({load + task, assigned_tasks});
  }

  vector<vector<int>> res;
  while (!machines.empty()) {
    res.push_back(machines.top().second);
    machines.pop();
  }
  return res;
}

int main() {

  int n, m;
  cout << "Enter the number of tasks: ";
  cin >> n;
  cout << "Enter the number of machines: ";
  cin >> m;

  vector<int> tasks(n);
  cout << "Enter the execution time for each task: ";
  for (int i = 0; i < n; i++) {
    cin >> tasks[i];
  }

  vector<vector<int>> schedule = multiprocessorScheduling(tasks, m);

  // Output results
  cout << "Scheduling results:" << endl;
  int makespan = 0;
  for (int i = 0; i < schedule.size(); i++) {
    int machine_load = 0;
    cout << "Machine " << i << ": ";
    for (int task : schedule[i]) {
      cout << task << " ";
      machine_load += task;
    }
    cout << "Total load: " << machine_load << endl;
    makespan = max(makespan, machine_load);
  }
  cout << "Total time to complete all tasks: " << makespan << endl;

  return 0;
}