#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int r;
    cin >> r;

    if (r == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> triangle(r);

    for (int i = 0; i < r; i++) {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }

    vector<vector<long long>> dp(r, vector<long long>(r, 0));
    dp[0][0] = triangle[0][0];

    for (int i = 1; i < r; i++) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        for (int j = 1; j < i; j++) {
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }

    long long max = 0;
    if (r > 0) {
        max = dp[r - 1][0];
        for (int i = 1; i < r; i++) {
            if (max < dp[r - 1][i]) {
                max = dp[r - 1][i];
            }
        }
    }

    cout << max << endl;
}