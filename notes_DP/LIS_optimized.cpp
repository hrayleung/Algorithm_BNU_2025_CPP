#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int LIS_optimized(vector<int>);

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << LIS_optimized(arr) << endl;
}

int LIS_optimized(vector<int> arr)
{
    int n = arr.size();
    vector<int> tails;
    tails.reserve(n);
    vector<int> tail_idx(n);
    vector<int> prev_idx(n, -1);

    for (int i = 0; i < n; i++)
    {
        int x = arr[i];
        auto it = lower_bound(tails.begin(), tails.end(), x);
        int j = it - tails.begin();

        if (it == tails.end())
        {
            tails.push_back(x);
        }
        else
        {
            *it = x;
        }

        if (j > 0)
        {
            prev_idx[i] = tail_idx[j - 1];
        }

        tail_idx[j] = i;
    }

    vector<int> lis;
    int k = tail_idx[tails.size() - 1];
    while (k != -1)
    {
        lis.push_back(arr[k]);
        k = prev_idx[k];
    }
    std::reverse(lis.begin(), lis.end());
    return lis.size();
}