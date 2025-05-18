#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> gas(n), cost(n);
}

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int size = gas.size();
    int start = 0;
    vector<int> tank(size);
    for (int i = 0; i < size; i++) {
        tank[i] = gas[i] - cost[i];
        if (tank[i] < 0) {
            start = start + i + 1;
        }

    }
}