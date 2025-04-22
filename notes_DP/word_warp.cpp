#include "limits"
#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using namespace std;

const long long inf = numeric_limits<long long>::max();

void word_warp(int m, vector<string>);

int main() {
    int n;
    int m;
    cin >> n;
    cin >> m;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    word_warp(m, words);
}

void word_warp(int m, vector<string> w) {
    int n = w.size();
    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        l[i] = w[i].length();
    }

    vector<int> s(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + l[i - 1];
    }

    vector<vector<long long>> cost(n + 1, vector<long long>(n + 1, inf));
    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int l = s[j] - s[i - 1] + j - i;
            int e = m - l;
            if (e < 0) {
                cost[i][j] = inf;
            } else if (j == n) {
                cost[i][j] = 0;
            } else {
                cost[i][j] = 1LL * e * e * e;
            }
        }
    }
    vector<long long> dp(n + 1, inf);
    vector<int> p(n + 1, 0);
    dp[0] = 0;
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= j; i++) {
            if (dp[i - 1] != inf && dp[i - 1] + cost[i][j] < dp[j]) {
                dp[j] = dp[i - 1] + cost[i][j];
                p[j] = i;
            }
        }
    }

}