#include "iostream"
#include "vector"

using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> gas(n), cost(n);
    for (int i = 0; i < n; i++)
    {
        cin >> gas[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }
    cout << canCompleteCircuit(gas, cost) << endl;
}

int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int size = gas.size();
    int start = 0;
    int total = 0;
    int curr = 0;
    for (int i = 0; i < size; i++)
    {
        int diff = gas[i] - cost[i];
        total += diff;
        curr += diff;
        if (curr < 0)
        {
            start = i + 1;
            curr = 0;
        }
    }
    return total >= 0 ? start : -1;
}