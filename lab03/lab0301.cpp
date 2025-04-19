#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int main() {
    fastIO();
    int n;
    long long Wm;
    cin >> n >> Wm;
    vector<int> W(n), V(n);
    long long sumW = 0;
    for (int i = 0; i < n; i++) {
        cin >> W[i];
        sumW += W[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> V[i];
    }
    int effective_W = min((long long) Wm, sumW);
    vector<int> dp(effective_W + 1);
    for (int i = 0; i < n; i++) {
        int current_item_weight = W[i];
        int current_item_value = V[i];

        for (int j = effective_W; j >= W[i]; j--) {
            dp[j] = max(dp[j], dp[j - current_item_weight] + current_item_value);
        }
    }
    cout << dp[effective_W] << endl;
    return 0;
}