#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int candy(vector<int> &ratings);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> rating(n);
    for (int i = 0; i < n; i++)
    {
        cin >> rating[i];
    }
    cout << candy(rating) << endl;
}

int candy(vector<int> &ratings)
{
    int size = ratings.size();
    vector<int> candies(size, 1);
    for (int i = 1; i < size; i++)
    {
        if (ratings[i] > ratings[i - 1])
        {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for (int i = size - 2; i >= 0; i--)
    {
        if (ratings[i] > ratings[i + 1])
        {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    int total = 0;
    for (int c : candies)
        total += c;
    return total;
}