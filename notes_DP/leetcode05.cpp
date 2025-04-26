#include "iostream"
#include "vector"
#include "string"

using namespace std;

string longestPalindrome(string s) {
    int n = s.size();
    if (n < 2) return s;

    vector<vector<bool>> dp(n, vector(n, false));
    int start = 0;
    int maxLen = 1;

    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

    for (int l = 3; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (l > maxLen) {
                    start = i;
                    maxLen = l;
                }
            }
        }
    }
    return s.substr(start, maxLen);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << longestPalindrome(s) << endl;
}