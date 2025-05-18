#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

int maxProfit(vector<int> &price);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    cout << maxProfit(price) << endl;
}

int maxProfit(vector<int> &price) {
    int maxProfit = 0;
    for (int i = 0; i < price.size() - 1; i++) {
        if (price[i] < price[i + 1]) {
            maxProfit = maxProfit + price[i + 1] - price[i];
        }
    }
    return maxProfit;
}